#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <vector>
#include "../infra/types.h"

class Memory 
{
public:
    explicit Memory(uint64 size);

    Memory() = delete;
    virtual ~Memory() = default;
    Memory(const Memory&) = delete;
    Memory(Memory&&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(Memory&&) = delete;
        
    void write(Addr address, const void* data, uint64 num_bytes);
    void read(Addr address, void* data, uint64 num_bytes);
        
    uint64 get_size() const noexcept { return size; }
    
    std::string dump() const;

    static std::shared_ptr<Memory> create_configured_memory();

private:
    std::vector<Byte> memory;
    uint64 size = 0;
};

#endif // MEMORY_H