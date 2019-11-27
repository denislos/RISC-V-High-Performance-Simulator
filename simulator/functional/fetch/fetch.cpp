/**
 * fetch.cpp - Implementation of Fetch class
 */


#include <functional/fetch/fetch.h>

#include <iostream> // REMOVE
std::shared_ptr<Instruction> Fetch::fetch_instr(Addr pc)
{
    uint32 instr_to_decode = 0;
    memory->read(pc, (void*)&instr_to_decode, 4);

    DecodeTree tree(config::yaml);
    auto instr = tree.decode(instr_to_decode);
    if (instr == nullptr)
        return nullptr;
    instr->set_PC(pc);

    return instr;
}
