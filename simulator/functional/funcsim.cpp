/**
 * funcsim.cpp - Implemenatio on FunctionalSImulator class
 */

#include <iostream>

#include <functional/funcsim.h>


FunctionalSimulator::FunctionalSimulator()
    : Simulator()
    , fetch(std::make_unique<Fetch>())
    , rf(std::make_unique<RF>())
    , func_memory(std::make_unique<FuncMemory>())
{ }


void FunctionalSimulator::set_memory(std::shared_ptr<Memory> mem)
{
    memory = mem;
    fetch->set_memory(mem);
    func_memory->set_memory(mem);
}


void FunctionalSimulator::run(uint64 num_instructions)
{
    uint64 current_instruction = 0;

    while (current_instruction < num_instructions)
    {
        std::cout << "Executing: " << current_instruction << std::endl;
        auto instr = fetch->fetch_instr(get_pc());
        rf->read_sources(instr);
        instr->execute();
        func_memory->load_store(instr);
        rf->write_dst(instr);
        this->update_pc(instr);
        
        std::cout << pc << " " << instr->get_disasm_string() << std::endl;

        current_instruction++;
    }
}
