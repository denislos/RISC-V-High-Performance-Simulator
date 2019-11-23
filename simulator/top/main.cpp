/**
 * main.cpp - Main file
 */

#include <string>
#include <cstdlib>

#include <infra/types.h>
#include <infra/arg_parse/arg_parser.h>
#include <memory/memory.h>


int main(int argc, char** argv)
{
    ArgParser arg_parser;
    const bool should_continue = arg_parser.parse_arguments(argc, argv);

    if (!should_continue)
        return EXIT_SUCCESS;

    
    const std::string trace_file = arg_parser.get_option_trace();
    const uint64 num_instructions = arg_parser.get_optionl_num_instrs();
    const bool is_functional_only = arg_parser.get_option_functional_only();


    auto memory = Memory::create_memory();
    //auto simulator = Simulator::create_simulator(num_instructions, is_functional_only);
    
    //auto kernel = Kernel::create_kernel();


    return EXIT_SUCCESS;
}