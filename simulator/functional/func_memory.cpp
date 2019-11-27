/**
 * func_memory.cpp - Implementation of FuncMemory class
 */

#include <functional/func_memory.h>


void FuncMemory::load_store(std::shared_ptr<Instruction> instr)
{
    if (instr->reads_memory())
    {
        int32 read_data = 0;
        memory->read(instr->get_mem_addr(), (void*)&read_data, instr->get_mem_access_size());

        instr->set_dst_value(instr->transform_load_data(read_data));
    }


    if (instr->writes_memory())
    {
        int32 data = instr->get_store_value();
        memory->write(instr->get_mem_addr(), (void*)&data, instr->get_mem_access_size());
    }
}