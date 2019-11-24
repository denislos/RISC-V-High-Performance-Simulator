/**
 * kernel.cpp - Implementation of Kernel class
 */

#include <memory>

#include <kernel/kernel.h>
#include <memory/elf/elf_loader.h>

#include <iostream>
std::shared_ptr<Kernel> Kernel::create_configured_kernel()
{
    return std::make_unique<Kernel>();
}


void Kernel::load_trace(const std::string& filename)
{
    ElfLoader elf_loader(filename);
    elf_loader.load_to(memory);
    start_pc = elf_loader.get_startPC();
}