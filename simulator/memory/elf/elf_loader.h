#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include <string>
#include <memory>

#include <infra/types.h>
#include <memory/memory.h>

#include <elfio/elfio.hpp>



class ElfLoader
{
public:
    explicit ElfLoader(const std::string& filename);

    ~ElfLoader() = default;
    ElfLoader(const ElfLoader&) = delete;
    ElfLoader(ElfLoader&&) = delete;
    ElfLoader& operator=(const ElfLoader&) = delete;
    ElfLoader& operator=(ElfLoader&&) = delete;

    void load_to(std::shared_ptr<Memory> memory, AddrDiff offset = 0) const;
    Addr get_startPC() const;
    Addr get_text_section_addr() const;

    std::string dump() const;

private:
    const std::unique_ptr<ELFIO::elfio> reader;
};
   
#endif