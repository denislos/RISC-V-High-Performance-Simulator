/**
 * arg_parser.h - Implementation of class ArgParser
 */


#ifndef INFRA_ARG_PARSE_H
#define INFRA_ARG_PARSE_H

#include <string>

#include <infra/types.h>


class ArgParser
{
public:
    bool parse_arguments(int argc, char** argv);

    std::string get_option_trace() const noexcept { return option_trace; }
    uint64 get_optionl_num_instrs() const noexcept { return option_num_instrs; }
    bool get_option_functional_only() const noexcept { return option_functional_only; }

    ArgParser() = default;
    virtual ~ArgParser() = default;
    ArgParser( const ArgParser&) = delete;
    ArgParser( ArgParser&&) = delete;
    ArgParser& operator=( const ArgParser&) = delete;
    ArgParser& operator=( ArgParser&&) = delete;

private:
    std::string option_trace;
    uint64 option_num_instrs = 0;
    bool option_functional_only = false;
};


#endif // INFRA_ARG_PARSE_H