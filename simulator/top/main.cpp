/**
 * main.cpp - Main file
 */

#include <cstdlib>

#include <infra/config/config.h>
#include <infra/types.h>


namespace config {
    RequiredConfigOption<std::string> trace_file("trace", "Trace to run", "");
    RequiredConfigOption<uint64> num_instructions("num_instructions", "Number of instructions to run", 0);
    
    ConfigOption<bool> is_functional_only("functional_only", "Use only functional simulation", false);
} // namespace config



int main(int argc, char** argv)
{
    if (!config::parse_arguments(argc, argv))
        return EXIT_SUCCESS;
    
    std::cout << config::trace_file << std::endl;

    return EXIT_SUCCESS;
}