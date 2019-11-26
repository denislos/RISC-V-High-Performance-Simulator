#include <memory/memory.h>
#include <infra/config/config.h>
#include <infra/decoder/decode_tree.h>
#include <risc-v/register/riscv_register.h>

namespace config {
    ConfigOption<std::string> yaml("yaml", "Rules for decoder", "risc-v/risc-v.yaml");
} // namespace config


const std::unordered_map<std::string, InstrType> DecodeTree::instr_mnemonics_map = {
    #define DEFINSTR(name, mnemonic) \
        { mnemonic, Instr_Type_##name },

    #include <risc-v/risc-v-instructions.def>
        
        { "dummy", Instr_Type_MAX }

    #undef DEFINSTR
};

std::shared_ptr<Instruction>
DecodeTree::decode(uint32 instr_to_decode)
{
    auto decodertree = tree["decodertree"];
    uint32 node_key = instr_to_decode;
    
    // Find needed node
    while (decodertree["range"].size() != 0) {
        int lsb = decodertree["range"]["lsb"].as<int>();
        int msb = decodertree["range"]["msb"].as<int>();
        node_key = generate_key(node_key & generate_bitmask(msb, lsb).to_ulong(), lsb);
        decodertree  = decodertree["nodes"][std::to_string(node_key)];
    }
    
    // Should be something 
    if (decodertree.size() == 0) {
        std::cerr << "Error while decoding instruction " << std::hex << instr_to_decode;
    }
    // Generate instruction
    const auto mnemonic = decodertree["mnemonic"].as<std::string>();
    const auto type = instr_mnemonics_map.at(mnemonic);

    auto instruction = std::make_unique<Instruction>(mnemonic, type);
    set_instr_fields(*instruction, decodertree["fields"], instr_to_decode);
    // Set needed fields
    return instruction;
}

void
DecodeTree::set_instr_fields(Instruction& instruction, YAML::Node fields, uint32 instr_to_decode)
{
    auto existing_fields = tree["fields"];
    for (size_t i = 0; i < fields.size(); i++) {
        std::string field_name = fields[i].as<std::string>();
        auto curr_field = existing_fields[field_name]["location"];
        int lsb = curr_field["bits"][0]["lsb"].as<int>();
        uint32 field_mask = curr_field["mask"].as<uint32>();
        int32 field_value = get_field_value(instr_to_decode, field_mask, lsb); 
     
        // Set field
        set_field(instruction, field_name, field_value);
    }
}

void 
DecodeTree::set_field(Instruction& instruction, const std::string& field_name, int32 field_value)
{
    if (field_name ==  "rd") {
        instruction.set_rd(static_cast<uint32>(field_value));
        insrtuction.set_dst(RISCVRegister(field_value));
        return;
    }
    if (field_name ==  "rs1") {
        instruction.set_rs1(static_cast<uint32>(field_value));
        instruction.set_src1(Register(field_value));
        return;
    }
    if (field_name ==  "rs2") {
        instruction.set_rs2(static_cast<uint32>(field_value));
        instruction.set_src2(Register(field_value));
        return;
    }
    if (field_name ==  "rs3") {
        instruction.set_rs3(static_cast<uint32>(field_value));
        instruction.set_src3(Register(field_value));
        return;
    }
    if (field_name ==  "rm") {
        instruction.set_rm(static_cast<uint32>(field_value));
        instruction.set_mask_value(field_value);
        return;
    }
    if (field_name ==  "imm12") {
        instruction.set_imm12(field_value);
        instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "imm20") {
        instruction.set_imm20(field_value);
        instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "jimm20") {
        instruction.set_jimm20(field_value);
        instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "storeimm") {
        instruction.set_storeimm(field_value);
        instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "bimm") {
        instruction.set_bimm(field_value);
        instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "aqrl") {
        instruction.set_aqrl(field_value);
        //instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "shamt") {
        instruction.set_shamt(field_value);
        //instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "shamtw") {
        instruction.set_shamtw(field_value);
        //instruction.set_imm_value(field_value);
        return;
    }
    if (field_name ==  "pred") {
        instruction.set_pred(field_value);
        return;
    }
    if (field_name ==  "succ") {
        instruction.set_imm12(field_value);
        return;
    }
    if (field_name ==  "fm") {
        instruction.set_imm12(field_value);
        return;
    }
    assert(0);
}


std::bitset<BITMASK_LEN>
DecodeTree::generate_bitmask(int msb, int lsb)
{
    std::string base_bitmask = "11111111111111111111111111111111";
    int length = msb - lsb + 1;
    int lbound = lsb;
    int ubound = BITMASK_LEN - lsb - length;
    std::bitset<BITMASK_LEN> new_bitmask(base_bitmask.replace(base_bitmask.begin() + ubound,
                                                     base_bitmask.end() - lbound,
                                                     length, '0'));
    return ~new_bitmask;
}

uint32
DecodeTree::generate_key(uint32 mask, int lsb)
{
    return mask >> lsb;
}

uint32
DecodeTree::get_field_value(uint32 instr, uint32 field_mask, int lsb)
{
    return (instr & field_mask) >> lsb;
}

DecodeTree::DecodeTree(std::string)
{
    tree = YAML::LoadFile(config::yaml);
}
