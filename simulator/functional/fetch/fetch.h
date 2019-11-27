/**
 * fetch.h - Implementation of Fetchc class
 */


#ifndef FUNCSIM_FETCH_H
#define FUNCSIM_FETCH_H

#include <memory>

#include <infra/types.h>
#include <infra/decoder/decode_tree.h>
#include <infra/config/config.h>
#include <top/base_instruction.h>
#include <memory/memory.h>

namespace config {
    extern ConfigOption<std::string> yaml;
} // namespace config

class Fetch
{
public:
    Fetch()
        : decode_tree(config::yaml)
    { }

    virtual ~Fetch() = default;
    Fetch(const Fetch&) = delete;
    Fetch(Fetch&&) = delete;
    Fetch& operator=(const Fetch&) = delete;
    Fetch& operator=(Fetch&&) = delete;

    void set_memory(std::shared_ptr<Memory> mem) noexcept { memory = mem; }

    std::shared_ptr<Instruction> fetch_instr(Addr pc);

private:
    DecodeTree decode_tree;
    std::shared_ptr<Memory> memory;
};

#endif // FUNCSIM_FETCH_H