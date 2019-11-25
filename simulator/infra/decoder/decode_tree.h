/**
 * decode_tree.h - Implementation of DecodeTree class
 */

#ifndef INFRA_DECODE_TREE
#define INFRA_DECODE_TREE

#include <string>
#include <bitset>
#include <yaml-cpp/yaml.h>
#include <top/base_instruction.h>

#define BITMASK_LEN 32

class DecodeTree
{
    public:
        static void init();
        explicit DecodeTree(std::string);
        DecodeTree() = delete;
        virtual ~DecodeTree() = default;
        DecodeTree(const DecodeTree&) = delete;
        DecodeTree(DecodeTree&&) = delete;
        DecodeTree& operator=(const DecodeTree&) = delete;
        DecodeTree& operator=(DecodeTree&&) = delete;
        Instruction decode(uint32 instr_to_decode);
    private:
        YAML::Node decode_tree;
        std::string base_bitmask = "11111111111111111111111111111111";
        std::bitset<BITMASK_LEN> generate_bitmask(int msb, int lsb);

};


#endif // INFRA_DECODE_TREE
