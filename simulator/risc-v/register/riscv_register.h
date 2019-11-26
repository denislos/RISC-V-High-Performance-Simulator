/**
 * riscv_register.h - Implemenetation of RISC-V Register class
 */


#ifndef RISCV_REGISTER_H
#define RISCV_REGISTER_H

#include <iostream>

class RISCVRegister
{
public:
    enum RegType
    {
        #define DEFREG(register) \
            Reg_Type_##register,

        #include <risc-v/register/risc-v-registers.def>
            
            Reg_Type_MAX

        #undef DEFREG
    };

    explicit constexpr RISCVRegister(RegType id) noexcept 
        : value(id < Reg_Type_MAX ? id : Reg_Type_MAX) 
    { }
    constexpr RISCVRegister() noexcept : RISCVRegister(Reg_Type_zero) { }

    bool is_zero() const noexcept { return value == Reg_Type_zero; }

    std::size_t to_rf_index() const noexcept { return value; }

    bool operator==(const RISCVRegister& rhs) const noexcept { return value == rhs.value; }
    bool operator!=(const RISCVRegister& rhs) const noexcept { return value != rhs.value; }

    bool is_valid() const noexcept { value != Reg_Type_MAX; }

private:
    RegType value = Reg_Type_zero;
};

#endif // RISCV_REGISTER_H
