#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <infra/types.h>

class Instruction 
{
    public:
        explicit Instruction(std::string name, std::string type,
                             uint32 rd  = NO_VAL32,
                             uint32 rs1 = NO_VAL32,
                             uint32 rs2 = NO_VAL32,
                             uint32 rs3 = NO_VAL32,
                             uint32 rm  = NO_VAL32,
                             int32 imm12    = NO_VAL32,
                             int32 imm20    = NO_VAL32,
                             int32 jimm20   = NO_VAL32,
                             int32 storeimm = NO_VAL32,
                             int32 bimm     = NO_VAL32,
                             int32 aqrl     = NO_VAL32,
                             int32 shamt    = NO_VAL32,
                             int32 shamtw   = NO_VAL32,
                             int32 pred     = NO_VAL32,
                             int32 succ     = NO_VAL32,
                             int32 fm       = NO_VAL32);

        Instruction() = delete;
        virtual ~Instruction() = default;
        Instruction(const Instruction&) = delete;
        Instruction(Instruction&&) = delete;
        Instruction& operator=(const Instruction&) = delete;
        Instruction& operator=(Instruction&&) = delete;

    private:
        std::string name = "";
        std::string type = "";

        uint32 rd  = NO_VAL32;
        uint32 rs1 = NO_VAL32;
        uint32 rs2 = NO_VAL32;
        uint32 rs3 = NO_VAL32;
        uint32 rm  = NO_VAL32;

        int32 imm12    = NO_VAL32;
        int32 imm20    = NO_VAL32;
        int32 jimm20   = NO_VAL32;
        int32 storeimm = NO_VAL32;
        int32 bimm     = NO_VAL32;
        int32 aqrl     = NO_VAL32;
        int32 shamt    = NO_VAL32;
        int32 shamtw   = NO_VAL32;
        int32 pred     = NO_VAL32;
        int32 succ     = NO_VAL32;
        int32 fm       = NO_VAL32;

        Addr mem_addr  = INVALID_ADDR;
        
        bool is_complete = false;
        bool is_taken    = false;
};

#endif // INSTUC
