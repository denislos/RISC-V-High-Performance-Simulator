/**
 * funcsim.h - Implemetation of FunctionalSimulator class
 */

#ifndef FUNCSIM_H
#define FUNCSIM_H

#include <top/simulator.h>
#include <iostream> // REMOVE

class FunctionalSimulator final : public Simulator
{
public:
    void run(uint64 num_instructions) override {std::cout << "Running: " << num_instructions << " instructions" << std::endl;}

private:
};


#endif // FUNCSIM_H