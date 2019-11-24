/**
 * instruction_enum.h - Instruction definitions
 */


#ifndef INSTRUCTION_ENUM_H
#define INSTRUCTION_ENUM_H

enum Instr_Opcode {
    #define DEFINSTR(name, mnemonic) \
        Instr_Opcode_##name,
    
    #include <risc-v/risc-v-instructions.def>

        Instr_Opcode_MAX

    #undef DEFINSTR
};

#endif // INSTRUCTION_ENUM_H