#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>


#include <top/instruction_enum.h>
#include <infra/types.h>
#include <executor/executor.h>
#include <risc-v/register/riscv_register.h>


class Instruction 
{
    public:
        using Register = RISCVRegister;

        explicit Instruction(const std::string& name, InstrType type,
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

        void set_rd(uint32 value)  noexcept { rd  = value; }
        void set_rs1(uint32 value) noexcept { rs1 = value; }
        void set_rs2(uint32 value) noexcept { rs2 = value; }
        void set_rs3(uint32 value) noexcept { rs3 = value; }
        void set_rm(uint32 value)  noexcept { rm  = value; }

        void set_imm12(int32 value)    noexcept { imm12    = value; }
        void set_imm20(int32 value)    noexcept { imm20    = value; }
        void set_jimm20(int32 value)   noexcept { jimm20   = value; }
        void set_storeimm(int32 value) noexcept { storeimm = value; }
        void set_bimm(int32 value)     noexcept { bimm     = value; }
        void set_aqrl(int32 value)     noexcept { aqrl     = value; }
        void set_shamt(int32 value)    noexcept { shamt    = value; }
        void set_shamtw(int32 value)   noexcept { shamtw   = value; }
        void set_pred(int32 value)     noexcept { pred     = value; }
        void set_succ(int32 value)     noexcept { succ     = value; }
        void set_fm(int32 value)       noexcept { fm       = value; }
       
        void execute();
        void set_executor(Executor::Callback callback) { executor = callback; }

        uint32 get_rd()  const noexcept { return rd;  }
        uint32 get_rs1() const noexcept { return rs1; }
        uint32 get_rs2() const noexcept { return rs2; }
        uint32 get_rs3() const noexcept { return rs3; }
        uint32 get_rm()  const noexcept { return rm;  }

        int32 get_imm12()    const noexcept { return imm12;    }
        int32 get_imm20()    const noexcept { return imm20;    }
        int32 get_jimm20()   const noexcept { return jimm20;   }
        int32 get_storeimm() const noexcept { return storeimm; }
        int32 get_bimm()     const noexcept { return bimm;     }
        int32 get_aqrl()     const noexcept { return aqrl;     }
        int32 get_shamt()    const noexcept { return shamt;    }
        int32 get_shamtw()   const noexcept { return shamtw;   }
        int32 get_pred()     const noexcept { return pred;     }
        int32 get_succ()     const noexcept { return succ;     }
        int32 get_fm()       const noexcept { return fm;       }

        std::string get_name() const noexcept { return name; }
        InstrType get_type() const noexcept { return type; }


        Register get_src(uint8 index) const noexcept
        {
            return (index == 0) ? src1 : ((index == 1) ? src2 : src3);
        }
        Register get_dst() const noexcept { return dst; }


        int32 get_src_value(uint8 index) const noexcept
        {
            return (index == 0) ? v_src1 : ((index == 1) ? v_src2 : v_src3);
        }
        int32 get_imm_value() const noexcept { return v_imm; }
        int32 get_dst_value() const noexcept { return v_dst; }


        void set_src1(Register reg) noexcept { src1 = reg; }
        void set_src2(Register reg) noexcept { src2 = reg; }
        void set_src3(Register reg) noexcept { src3 = reg; }
        void set_dst(Register reg) noexcept { dst = reg; }

        void set_src1_value(int32 value) noexcept { v_src1 = value; }
        void set_src2_value(int32 value) noexcept { v_src2 = value; }
        void set_src3_value(int32 value) noexcept { v_src3 = value; }
        
        void set_imm_value(int32 value) noexcept { v_imm = value; }
        void set_mask_value(int32 mask) noexcept { v_mask = mask; }

        void set_dst_value(int32 value) noexcept { v_dst = value; }

        bool is_branch_taken() const noexcept { return is_taken; }

        void set_PC(Addr pc) noexcept { PC = pc; }

        Addr get_PC() const noexcept { return PC; }
        Addr get_newPC() const noexcept { return new_PC; }
        Addr get_target() const noexcept { return target; }

        bool reads_memory() const noexcept { return is_memory_read; }
        bool writes_memory() const noexcept { return is_memory_write; }

        uint64 get_mem_access_size() const noexcept { return mem_access_size; }
        Addr get_mem_addr() const noexcept { return mem_addr; }

        int32 transform_load_data(int32 data) const noexcept { return data; }
        int32 get_store_value() const noexcept { return store_data; }

        std::string get_disasm_string() const noexcept;

    private:
        std::string name = "";
        
        InstrType type = Instr_Type_MAX;

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

        bool is_memory_read = false;
        bool is_memory_write = false;
        Addr mem_addr  = INVALID_ADDR;
        uint64 mem_access_size = 0;

        int32 store_data = NO_VAL32;

        Addr PC = INVALID_ADDR;
        Addr new_PC = INVALID_ADDR;
        Addr target = INVALID_ADDR;
        
        bool is_complete = false;
        bool is_taken    = false;

        Executor::Callback executor;

        Register src1;
        Register src2;
        Register src3;

        Register dst;


        int32 v_src1 = NO_VAL32;
        int32 v_src2 = NO_VAL32;
        int32 v_src3 = NO_VAL32;
        int32 v_imm  = NO_VAL32;
        int32 v_mask = NO_VAL32;

        int32 v_dst  = NO_VAL32;

        friend class Executor;
};

#endif // INSTRUCTION_H
