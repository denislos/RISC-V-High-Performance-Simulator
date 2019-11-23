#include <memory>
#include <iostream>
#include <cstring>
#include "memory.h"

#include <infra/config/config.h>

namespace config {
    ConfigOption<uint64> memory_size("memory_size", "Size of memory", 2048);
} // namespace config


std::shared_ptr<Memory> Memory::Mem = Memory::create_memory(config::memory_size);

std::shared_ptr<Memory> 
Memory::create_memory(uint64_t size)
{
    return std::shared_ptr<Memory>(new Memory(size));
}

std::shared_ptr<Memory> 
Memory::get_memory()
{
     return Mem;
}

Memory::Memory(uint64_t size) : size(size)
{
    memory.resize(size);
}

void Memory::write(Addr address, const void* data, uint64_t num_bytes)
{
    if (address + num_bytes > size)
    {
        std::cerr << "error: address is out of memory " << std::endl;
    }
    std::memcpy(&memory[address], data, num_bytes);
}

void Memory::read(Addr address, void* data, uint64_t num_bytes)
{
    if (address + num_bytes > size)
    {
        std::cerr << "error: address is out of memory " << std::endl;
    }
    std::memcpy(data, &memory[address], num_bytes);
}

void Memory::dump()
{
    for (auto& byte : memory) {
        std::cout << " " << byte << " "; 
    }
}