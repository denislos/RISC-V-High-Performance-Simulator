#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include "memory.h"
#include <string>

class Memory;

namespace ELFIO {
    class elfio;
} 

class ElfLoader
{
public:
    explicit ElfLoader( const std::string& filename);
    ~ElfLoader();

    ElfLoader( const ElfLoader&) = delete;
    ElfLoader( ElfLoader&&) = delete;
    ElfLoader& operator=( const ElfLoader&) = delete;
    ElfLoader& operator=( ElfLoader&&) = delete;

    void load_to( WriteableMemory *memory, AddrDiff offset = 0) const;
    Addr get_startPC() const;
    Addr get_text_section_addr() const;
private:
    const std::unique_ptr<ELFIO::elfio> reader;
};
   
#endif