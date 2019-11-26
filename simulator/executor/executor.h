/**
 * executor.h - Implementation of Executor class
 */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unordered_map>
#include <memory>


#include <top/instruction_enum.h>


class Instruction;

class Executor
{
public:
    using Callback = void (*)(Instruction*);

    static void assign_executor(Instruction* instr);

private:
    #define DEFINSTR(name, mnemonic) \
        static void execute_##name(Instruction*);

    #include <risc-v/risc-v-instructions.def>

        static void execute_dummy(Instruction*);

    #undef DEFINSTR

    static const std::unordered_map<InstrType, Callback> callbacks;
};

#endif // EXECUTOR_H
