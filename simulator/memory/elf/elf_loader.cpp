#include <string>
#include <memory>
#include <sstream>


#include <memory/elf/elf_loader.h>
#include <memory/memory.h>

#include <iostream>
static void load_elf_section(std::shared_ptr<Memory> memory, const ELFIO::section& section, AddrDiff offset)
{
    using namespace std::literals::string_literals;
    if (section.get_address() == 0 || section.get_data() == nullptr) {
        std::cout << "Exception should be issued\n";
    }

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
        {
            if (section->get_data() != nullptr)
            {
                std::cout << (memory == nullptr) << std::endl;
                load_elf_section(memory, *section, offset);
            }
        }
}

std::string ElfLoader::dump() const
{
    std::ostringstream oss;

    for (const auto& section : reader->sections) 
        if ((section->get_flags() & SHF_ALLOC) != 0)
        {
            auto data = section->get_data();

            if (data != nullptr)
            {
                for (uint64 i = 0; i < section->get_size(); i++)
                    oss << data[i];
            }
        }

    return oss.str();
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