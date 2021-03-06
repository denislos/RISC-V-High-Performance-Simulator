/**
 * decode_tree.h - Implementation of DecodeTree class
 */

#ifndef INFRA_DECODE_TREE
#define INFRA_DECODE_TREE

#include <string>
#include <bitset>
#include <memory>
#include <unordered_map>

#include <yaml-cpp/yaml.h>
#include <top/base_instruction.h>
#include <top/instruction_enum.h>


#define BITMASK_LEN 32

class DecodeTree
{
    public:
        explicit DecodeTree(const std::string& yaml_file);

        DecodeTree() = delete;
        virtual ~DecodeTree() = default;
        DecodeTree(const DecodeTree&) = delete;
        DecodeTree(DecodeTree&&) = delete;
        DecodeTree& operator=(const DecodeTree&) = delete;
        DecodeTree& operator=(DecodeTree&&) = delete;
        
        uint32 get_field_value(uint32 instr, uint32 field_mask, int lsb);
        
        std::shared_ptr<Instruction> decode(uint32 instr_to_decode);
        
        uint32 generate_key(uint32 mask, int lsb);
        std::bitset<BITMASK_LEN> generate_bitmask(int msb, int lsb);
        
        YAML::Node get_tree() const { return tree; }
        
        void set_instr_fields(Instruction& instruction, YAML::Node fields, uint32 instr_to_decode);
        void set_field(Instruction& instruction, const std::string& field_name, int32 field_value);
    
    private:
        YAML::Node tree;

        static const std::unordered_map<std::string, InstrType> instr_mnemonics_map;
};


#endif // INFRA_DECODE_TREE
