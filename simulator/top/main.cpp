/**
 * main.cpp - Main file
 */

#include <cstdlib>

#include <infra/config/config.h>
#include <infra/types.h>
#include <memory/memory.h>
#include <memory/elf/elf_loader.h>


namespace config {
    RequiredConfigOption<std::string> trace_file("trace", "Trace to run", "");
    RequiredConfigOption<uint64> num_instructions("num_instrs", "Number of instructions to run", 0);
    
    ConfigOption<bool> is_functional_only("functional_only", "Use only functional simulation", false);
} // namespace config



int main(int argc, char** argv)
{
    if (!config::parse_arguments(argc, argv))
        return EXIT_SUCCESS;

    auto memory = Memory::get_memory();

    ElfLoader elf_loader = ElfLoader(config::trace_file);
    elf_loader.load_to(memory);

    return EXIT_SUCCESS;
}