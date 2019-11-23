/**
 * memory.cpp - Implementation of Memory class
 */


#include <memory/memory.h>


class MemoryFactory
{
public:
    static MemoryFactory* get_instance()
    {
        static MemoryFactory memory_factory;
        return &memory_factory;
    }
};