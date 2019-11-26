/**
 * instruction_enum.h - Instruction definitions
 */


#ifndef INSTRUCTION_ENUM_H
#define INSTRUCTION_ENUM_H

enum InstrType {
    #define DEFINSTR(name, mnemonic) \
        Instr_Type_##name,
    
    #include <risc-v/risc-v-instructions.def>

        Instr_Type_MAX

    #undef DEFINSTR
};

#endif // INSTRUCTION_ENUM_H
