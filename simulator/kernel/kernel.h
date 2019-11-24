/**
 * kernel.h - Implementation of Kernel class
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <memory>

#include <kernel/kernel.h>
#include <top/simulator.h>
#include <memory/memory.h>

class Simulator;

class Kernel
{
public:
    static std::shared_ptr<Kernel> create_configured_kernel();

    void set_simulator(std::shared_ptr<Simulator> sim) noexcept { simulator = sim; }
    void set_memory(std::shared_ptr<Memory> mem) noexcept { memory = mem; }

    void load_trace(const std::string& filename);

    void execute() { }

    Addr get_start_pc() const noexcept { return start_pc; }

    Kernel() = default;
    virtual ~Kernel() = default;
    Kernel(const Kernel&) = delete;
    Kernel(Kernel&&) = delete;
    Kernel& operator=(const Kernel&) = delete;
    Kernel& operator=(Kernel&&) = delete;

private:
    std::shared_ptr<Simulator> simulator = nullptr;
    std::shared_ptr<Memory> memory = nullptr;

    Addr start_pc = INVALID_ADDR;
};


#endif // KERNEL_H