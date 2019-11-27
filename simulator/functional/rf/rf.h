/**
 * rf.h - Implementation of RF class
 */


#ifndef FUNCSIM_RF_H
#define FUNCSIM_RF_H

#include <array>

#include <infra/types.h>
#include <risc-v/register/riscv_register.h>
#include <top/base_instruction.h>

class RF
{
public:
    RF() { register_array.fill(0); }

    virtual ~RF() = default;
    RF(const RF&) = delete;
    RF(RF&&) = delete;
    RF& operator=(const RF&) = delete;
    RF& operator=(RF&&) = delete;

    void read_sources(std::shared_ptr<Instruction> instr) const;
    void write_dst(std::shared_ptr<Instruction> instr);

private:
    std::array<int32, RISCVRegister::Reg_Type_MAX> register_array;
};


#endif // FUNCSIM_RF_H