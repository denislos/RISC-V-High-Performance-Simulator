#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
Class Memory 
{
    private:
        std::vector<char> memory;
    public:
        write(Addr address, void* data);
        read(Addr address, void* data);
}

#endif // MEMORY_H