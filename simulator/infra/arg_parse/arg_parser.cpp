/**
 * arg_parser.cpp - Implementation of class ArgParser
 */

#include <iostream>

#include <infra/arg_parse/arg_parser.h>

#include <boost/program_options.hpp>


namespace po = boost::program_options;


bool ArgParser::parse_arguments(int argc, char** argv)
{
    try
    {
        po::options_description description("Options");
        description.add_options()
            ("help", "Help message")
            ("trace,t", po::value<std::string>()->required(), "Binary trace to run")
            ("num_instrs,n", po::value<uint64>()->required(), "Number of instructions to run")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, description), vm);
        po::notify(vm);

        if (vm.count("help")) 
        {  
            std::cout << description << std::endl;
            return false;
        }

        po::notify(vm);
    }
    catch(boost::program_options::required_option& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}