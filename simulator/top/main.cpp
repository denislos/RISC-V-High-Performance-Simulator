/**
 * main.cpp - Main file
 */

#include <cstdlib>

#include <infra/config/config.h>
#include <infra/types.h>
#include <memory/memory.h>
#include <top/simulator.h>
#include <kernel/kernel.h>


namespace config {
    RequiredConfigOption<std::string> trace_file("trace", "Trace to run", "");
    RequiredConfigOption<uint64> num_instructions("num_instrs", "Number of instructions to run", 0);
    
    ConfigOption<bool> is_functional_only("functional_only", "Use only functional simulation", false);
} // namespace config



int main(int argc, char** argv)
{
    if (!config::parse_arguments(argc, argv))
        return EXIT_SUCCESS;

    auto memory    = Memory::create_configured_memory();
    auto simulator = Simulator::create_configured_simulator();


    auto kernel = Kernel::create_configured_kernel();

    kernel->set_simulator(simulator);
    kernel->set_memory(memory);

    kernel->load_trace(config::trace_file);
    /*
    simulator->set_kernel(kernel);
    simulator->set_memory(memory);

    simulator->set_pc(kernel->get_start_pc());
    simulator->run(config::num_instructions);
    */

    return EXIT_SUCCESS;
}