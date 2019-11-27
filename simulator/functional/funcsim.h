/**
 * funcsim.h - Implemetation of FunctionalSimulator class
 */

#ifndef FUNCSIM_H
#define FUNCSIM_H

#include <memory>

#include <top/simulator.h>
#include <functional/fetch/fetch.h>
#include <functional/func_memory.h>
#include <functional/rf/rf.h>

class FunctionalSimulator final : public Simulator
{
public:
    FunctionalSimulator();

    virtual ~FunctionalSimulator() = default;
    FunctionalSimulator(const FunctionalSimulator&) = delete;
    FunctionalSimulator(FunctionalSimulator&&) = delete;
    FunctionalSimulator& operator=(const FunctionalSimulator&) = delete;
    FunctionalSimulator& operator=(FunctionalSimulator&&) = delete;

    void run(uint64 num_instructions) override;
    void set_memory(std::shared_ptr<Memory> mem) override;

    void update_pc(std::shared_ptr< Instruction> instr)
    {
        if (instr->is_branch_taken())
            set_pc(instr->get_newPC());
        else
            set_pc(get_pc() + 4);
    }

private:
    std::unique_ptr<Fetch> fetch;
    std::unique_ptr<RF> rf;
    std::unique_ptr<FuncMemory> func_memory;
};


#endif // FUNCSIM_H
