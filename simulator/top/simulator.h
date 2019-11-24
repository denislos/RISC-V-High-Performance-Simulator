/**
 * simulator.h - Implementation of Simulator class
 */


#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>

#include <infra/types.h>
#include <kernel/kernel.h>
#include <memory/memory.h>

class Kernel;

class Simulator
{
public:
    static std::shared_ptr<Simulator> create_configured_simulator();

    virtual void run(uint64 num_instructions) = 0;

    void set_pc(Addr pc_value) noexcept { pc = pc_value; }
    virtual Addr get_pc() const noexcept { return pc; }

    virtual void set_memory(std::shared_ptr<Memory> mem) { memory = mem; }
    virtual void set_kernel(std::shared_ptr<Kernel> krn) { kernel = krn; }

protected:
    Addr pc = INVALID_ADDR;

    std::shared_ptr<Memory> memory = nullptr;
    std::shared_ptr<Kernel> kernel = nullptr;
};


#endif // SIMULATOR_H