/**
 * config.h - Implementation
 */


#ifndef INFRA_CONFIG_H
#define INFRA_CONFIG_H

#include <string>
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace config {

    template <typename T> class BaseConfigOption;

    class ConfigArgsLoader
    {
    public:
        ConfigArgsLoader()
            : args_description("Options")
        {
            args_description.add_options()
                ("help", "Help message")
            ;
        }

        template <typename T>
        void add_config_option(BaseConfigOption<T>* config_option)
        {
            if (config_option->is_required())
            {
                args_description.add_options()
                    (config_option->get_option_name().c_str(), 
                     po::value<T>(config_option->get_value_pointer())->required(), 
                     config_option->get_description().c_str())
                ;
            }
            else
            {
                args_description.add_options()
                    (config_option->get_option_name().c_str(), 
                     po::value<T>(config_option->get_value_pointer()), 
                     config_option->get_description().c_str())
                ;
            }
        }

        bool parse_arguments(int argc, char** argv);

        static ConfigArgsLoader* get_instance()
        {
            static ConfigArgsLoader config_args_loader;
            return &config_args_loader;
        }
    
    private:
        po::options_description args_description;
        po::variables_map vm;
    };


    template <typename T>
    class BaseConfigOption
    {
    public:
        BaseConfigOption(const char* option_name,
                         const char* description,
                         const T& default_value,
                         bool is_required)
            : option_name(option_name)
            , description(description)
            , _is_required(is_required)
            , value(default_value)
        { 
            ConfigArgsLoader::get_instance()->add_config_option<T>(this);
        }

        std::string get_option_name() const noexcept { return option_name; }
        std::string get_description() const noexcept { return description; }
        T get_value() const noexcept { return value; }
        bool is_required() const noexcept { return _is_required; }

        T* get_value_pointer() noexcept { return &value; }

        BaseConfigOption() = delete;
        virtual ~BaseConfigOption() = default;
        BaseConfigOption( const BaseConfigOption&) = delete;
        BaseConfigOption( BaseConfigOption&&) = delete;
        BaseConfigOption& operator=( const BaseConfigOption&) = delete;
        BaseConfigOption& operator=( BaseConfigOption&&) = delete;
    
    private:
        const std::string option_name;
        const std::string description;
        const bool _is_required;

        T value;
    };


    template <typename T>
    class ConfigOption : BaseConfigOption<T>
    {
    public:
        ConfigOption(const char* option_name,
                     const char* description,
                     const T& default_value)
            : BaseConfigOption<T>(option_name, description, default_value, false)
        { }
    };


    template <typename T>
    class RequiredConfigOption : BaseConfigOption<T>
    {
    public:
        RequiredConfigOption(const char* option_name,
                             const char* description,
                             const T& default_value)
            : BaseConfigOption<T>(option_name, description, default_value, true)
        { }
    };


    static inline bool parse_arguments(int argc, char** argv)
    {
        return ConfigArgsLoader::get_instance()->parse_arguments(argc, argv);
    }

} // namespace config


#endif // INFRA_CONFIG_H