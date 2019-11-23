#include <string>
#include <memory>

#include "../memory.h"
#include "elf_loader.h"
#include "../../../external/elfio/elfio.hpp"


static void load_elf_section(std::shared_ptr<Memory> memory, const ELFIO::section& section, AddrDiff offset)
{
    using namespace std::literals::string_literals;
    if (section.get_address() == 0 || section.get_data() == nullptr)
        std::cout << "Exception should be issued\n";

    memory->write(section.get_address() + offset, section.get_data(), section.get_size());
}


ElfLoader::ElfLoader(const std::string& filename)
    : reader(std::make_unique<ELFIO::elfio>())
{
    if (!reader->load(filename))
        std::cout << "Exception should be issued\n";
}


void ElfLoader::load_to(std::shared_ptr<Memory> memory, AddrDiff offset) const
{
    for (const auto& section : reader->sections)
        if ((section->get_flags() & SHF_ALLOC) != 0)
            load_elf_section(memory, *section, offset);
}

void ElfLoader::dump_sections()
{
    for (const auto& section : reader->sections) 
        if ((section->get_flags() & SHF_ALLOC) != 0)
            for (auto& byte : section->get_data())
                std::cout << " " << byte << " ";

}


Addr ElfLoader::get_text_section_addr() const
{
    return reader->sections[".text"] != nullptr ? reader->sections[".text"]->get_address() : 0;
}

Addr ElfLoader::get_startPC() const
{
    for (const auto& section : reader->sections) {
        if (section->get_type() != SHT_SYMTAB)
            continue;

        ELFIO::symbol_section_accessor symbols(*reader, section);
        for (ELFIO::Elf_Xword j = 0; j < symbols.get_symbols_num(); ++j ) {
            std::string name;
            ELFIO::Elf64_Addr value = 0;
            ELFIO::Elf_Xword size;
            unsigned char bind;
            unsigned char type;
            ELFIO::Elf_Half section_index;
            unsigned char other;
            symbols.get_symbol(j, name, value, size, bind, type, section_index, other );
            if (name == "__start" || name == "_start")
                return value;
        }
    }
    return 0; // Exception 
}

ElfLoader::~ElfLoader() = default;