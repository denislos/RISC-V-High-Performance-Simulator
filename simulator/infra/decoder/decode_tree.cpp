#include <memory/memory.h>
#include <infra/config/config.h>
#include <infra/decoder/decode_tree.h>

namespace config {
    ConfigOption<std::string> yaml("yaml", "Rules for decoder", "risc-v/risc-v.yaml");
} // namespace config

std::bitset<BITMASK_LEN>
DecodeTree::generate_bitmask(int msb, int lsb)
{
    int length = msb - lsb + 1;
    int lbound = lsb;
    int ubound = BITMASK_LEN - lsb - length;
    std::bitset<BITMASK_LEN> new_bitmask(base_bitmask.replace(base_bitmask.begin() + ubound,
                                                     base_bitmask.end() - lbound,
                                                     length, '0'));
    return ~new_bitmask;
}

Instruction
DecodeTree::decode(uint32 instr_to_decode)
{
    auto subtree = decode_tree;
    uint32 node_key = instr_to_decode;
    while (subtree["range"].size() != 0) {
        int lsb = subtree["range"]["lsb"].as<int>();
        int msb = subtree["range"]["msb"].as<int>();
        node_key = node_key & generate_bitmask(msb, lsb).to_ulong();
        subtree  = subtree["nodes"][std::to_string(node_key)];
    }
    if (subtree.size() == 0) {
        std::cerr << "Error while decoding instruction " << std::hex << instr_to_decode;
    }
}

DecodeTree::DecodeTree(std::string)
{
    decode_tree = YAML::LoadFile(config::yaml)["decoder_tree"];
}
