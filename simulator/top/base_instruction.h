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
        //Instruction(const Instruction&) = delete;
        //Instruction(Instruction&&) = delete;
        //Instruction& operator=(const Instruction&) = delete;
        //Instruction& operator=(Instruction&&) = delete;

        void set_rd(uint32 value)  { rd  = value; }
        void set_rs1(uint32 value) { rs1 = value; }
        void set_rs2(uint32 value) { rs2 = value; }
        void set_rs3(uint32 value) { rs3 = value; }
        void set_rm(uint32 value)  { rm  = value; }

        void set_imm12(int32 value)    { imm12    = value; }
        void set_imm20(int32 value)    { imm20    = value; }
        void set_jimm20(int32 value)   { jimm20   = value; }
        void set_storeimm(int32 value) { storeimm = value; }
        void set_bimm(int32 value)     { bimm     = value; }
        void set_aqrl(int32 value)     { aqrl     = value; }
        void set_shamt(int32 value)    { shamt    = value; }
        void set_shamtw(int32 value)   { shamtw   = value; }
        void set_pred(int32 value)     { pred     = value; }
        void set_succ(int32 value)     { succ     = value; }
        void set_fm(int32 value)       { fm       = value; }
        
        uint32 get_rd()  const { return rd;  }
        uint32 get_rs1() const { return rs1; }
        uint32 get_rs2() const { return rs2; }
        uint32 get_rs3() const { return rs3; }
        uint32 get_rm()  const { return rm;  }

        int32 get_imm12()    const { return imm12;    }
        int32 get_imm20()    const { return imm20;    }
        int32 get_jimm20()   const { return jimm20;   }
        int32 get_storeimm() const { return storeimm; }
        int32 get_bimm()     const { return bimm;     }
        int32 get_aqrl()     const { return aqrl;     }
        int32 get_shamt()    const { return shamt;    } 
        int32 get_shamtw()   const { return shamtw;   }
        int32 get_pred()     const { return pred;     }
        int32 get_succ()     const { return succ;     }
        int32 get_fm()       const { return fm;       }

        std::string get_name() const { return name; }
        std::string get_type() const { return type; }

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
