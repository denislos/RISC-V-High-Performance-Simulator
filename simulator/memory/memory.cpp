#include <memory>
#include <sstream>
#include <cstring>

#include <memory/memory.h>
#include <infra/config/config.h>

namespace config {
    ConfigOption<uint64> memory_size("memory_size", "Size of memory", 4096);
} // namespace config


std::shared_ptr<Memory> 
Memory::create_configured_memory()
{
     return std::make_unique<Memory>(config::memory_size);
}

Memory::Memory(uint64 size) : size(size)
{
    memory.resize(size);
}

void Memory::write(Addr address, const void* data, uint64 num_bytes)
{
    if (address + num_bytes > size)
    {
        std::cerr << "error: address is out of memory " << std::endl;
    }
    std::memcpy(&memory[address], data, num_bytes);
}

void Memory::read(Addr address, void* data, uint64 num_bytes)
{
    if (address + num_bytes > size)
    {
        std::cerr << "error: address is out of memory " << std::endl;
    }
    std::memcpy(data, &memory[address], num_bytes);
}

std::string Memory::dump() const
{
    std::ostringstream oss;

    for (const auto& byte : memory)
        oss << std::hex << byte;

    return oss.str();
}