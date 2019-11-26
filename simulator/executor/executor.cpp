/**
 * executor.cpp - Implementation of Executor class
 */

#include <executor/executor.h>
#include <top/base_instruction.h>

const std::unordered_map<InstrType, Executor::Callback> Executor::callbacks = {
    #define DEFINSTR(name, mnemonic) \
        { Instr_Type_##name, execute_##name },

    #include <risc-v/risc-v-instructions.def>

        { Instr_Type_MAX, execute_dummy }

    #undef DEFINSTR
};


void Executor::assign_executor(Instruction* instr)
{
    instr->set_executor(callbacks.at(instr->get_type()));
}

