/**
 * main.cpp - Main file
 */

#include <cstdlib>

#include <infra/config/config.h>
#include <infra/types.h>


namespace config {
    RequiredConfigOption<std::string> trace_file("trace_file", "Trace to run", "");
    RequiredConfigOption<uint64> num_instruction("num_instruction", "Number of instructions to run", 0);
    
    ConfigOption<bool> is_functional_only("functional_only", "Use only functional simulation", false);
} // namespace config



int main(int argc, char** argv)
{
    if (!config::parse_arguments(argc, argv))
        return EXIT_SUCCESS;

    return EXIT_SUCCESS;
}