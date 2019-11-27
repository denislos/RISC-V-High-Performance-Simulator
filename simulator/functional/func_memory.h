/**
 * func_memory.h - Implementation of FuncMemory class
 */

#ifndef FUNC_MEMORY_H
#define FUNC_MEMORY_H

#include <memory>

#include <memory/memory.h>
#include <top/base_instruction.h>

class FuncMemory
{
public:
    FuncMemory() = default;
    virtual ~FuncMemory() = default;
    FuncMemory(const FuncMemory&) = delete;
    FuncMemory(FuncMemory&&) = delete;
    FuncMemory& operator=(const FuncMemory&) = delete;
    FuncMemory& operator=(FuncMemory&&) = delete;

    void set_memory(std::shared_ptr<Memory> mem) noexcept { memory = mem; }

    void load_store(std::shared_ptr<Instruction> instr);

private:
    std::shared_ptr<Memory> memory;
};



#endif // FUNC_MEMORY_H