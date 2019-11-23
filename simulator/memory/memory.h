#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <vector>
#include "../infra/types.h"

class Memory 
{
    private:
        std::vector<char> memory;
        uint64_t size = 0;
        static std::shared_ptr<Memory> Mem;
    public:
        Memory(uint64_t size);
        ~Memory() = default;
        void write(Addr address, const void* data, uint64_t num_bytes);
        void read(Addr address, void* data, uint64_t num_bytes);
        static std::shared_ptr<Memory> create_memory(uint64_t size);
        static std::shared_ptr<Memory> get_memory();
        uint64_t get_size() const { return size; }
};

#endif // MEMORY_H