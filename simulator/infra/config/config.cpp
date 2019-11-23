/**
 * 
 */

#include <infra/config/config.h>


namespace config {

    bool ConfigArgsLoader::parse_arguments(int argc, char** argv)
    {
        try
        {
            po::store(po::parse_command_line(argc, argv, args_description), vm);

            if (vm.count("help")) 
            {  
                std::cout << args_description << std::endl;
                return false;
            }

            po::notify(vm);
        }
        catch(const boost::program_options::required_option& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
            
        return true;
    }

} // namespace config