/**
 * Simulator.cpp - Implementation of Simulator class
 */


#include <top/simulator.h>
#include <functional/funcsim.h>
#include <infra/config/config.h>

namespace config {
    extern ConfigOption<bool> is_functional_only;
} // namespace config


class SimulatorFactory
{
public:
    std::shared_ptr<Simulator> get_funcsim() const
    {
        return std::make_unique<FunctionalSimulator>();
    }

    static SimulatorFactory* get_instance()
    {
        static SimulatorFactory factory;
        return &factory; 
    }
};


std::shared_ptr<Simulator> Simulator::create_configured_simulator()
{
    if (config::is_functional_only)
    {
        return SimulatorFactory::get_instance()->get_funcsim();
    }
    else
    {
        return nullptr;
    }
}