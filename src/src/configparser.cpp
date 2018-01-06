#include <iostream>
#include <fstream>
#include <system_error>

#include "configparser.h"
#include "json.h"

/**
 * \brief Tries to load(from file) application configuration into config_json var
 */
int ProgramConfigReader(int argc, char *argv[], Json::Value& config_json)
{
    std::ifstream config_file_stream;
    //choose the specific error flags you whant to check in the stream. If the flags were set before this call, the exception is launched now
    config_file_stream.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // std::string param = "-f";
    //
    // for(int i = 0; i< argc; i++)
    // {
    //     //found request for specific config file use
    //     if(param.compare(argv[i]) == 0)//cstring compare
    //     {
    //         try
    //         {
    //             config_file_stream.open(argv[i+1]);
    //
    //             if(config_file_stream.is_open())
    //             {
    //                 config_file_stream >> config_json;
    //             }
    //
    //             //ALLWAYS close your damn files, although config_file_stream destructor would close all when its get out of scope
    //             config_file_stream.close();
    //
    //             return 0;
    //         }
    //         catch(const std::ios_base::failure &fail)
    //         {
    //             //Due to a bug in the GCC compiler, std::ios_base::failure exception are not being thrown as std::ios_base::failure
    //             //Will keep this block here to remind me to check if the bug is corrected and then update my code
    //             //For now, a generic exception will be used
    //             std::cout << "Bugged Exception Caught "<< fail.what()<< std::endl;
    //         }
    //         catch(const std::exception &e)
    //         {
    //             std::cout << "Failed to open user defined config file - " << e.what() << std::endl << "trying default file"<<std::endl;
    //         }
    //     }
    // }

    //try to load default file (if the program got here, no file was provided)
    try
    {
        config_file_stream.open("data/config.json");

        if(config_file_stream.is_open())
        {
            config_file_stream >> config_json;
        }

        //ALLWAYS close your damn files, although config_file_stream destructor would close all when its get out of scope
        config_file_stream.close();
    }
    catch(const std::ios_base::failure &fail)
    {
        //Due to a bug in the GCC compiler, std::ios_base::failure exception are not being thrown as std::ios_base::failure
        //Will keep this block here to remind me to check if the bug is corrected and then update my code
        //For now, a generic exception will be used
        std::cout << "Bugged Exception Caught " << fail.what() <<std::endl;
    }
    catch(const std::exception &e)
    {
        std::cout << "Failed to open default config file - " << e.what() << " ... \n" << "Terminating application" << std::endl;
        return -1;//will kill the program as the program was unable to initialize its basic configuration
    }

    return 0;
}
