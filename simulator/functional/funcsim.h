/**
 * funcsim.h - Implemetation of FunctionalSimulator class
 */

#ifndef FUNCSIM_H
#define FUNCSIM_H

#include <top/simulator.h>

class FunctionalSimulator final : public Simulator
{
public:
    FunctionalSimulator()
        : Simulator()
    { }

    virtual ~FunctionalSimulator() = default;
    FunctionalSimulator(const FunctionalSimulator&) = delete;
    FunctionalSimulator(FunctionalSimulator&&) = delete;
    FunctionalSimulator& operator=(const FunctionalSimulator&) = delete;
    FunctionalSimulator& operator=(FunctionalSimulator&&) = delete;

    void run(uint64 num_instructions) override;


private:
};


#endif // FUNCSIM_H
