//#include "define_flags.h"
#define SERVER_DEBUGS
#include <iostream>
#include <map>
#include <forward_list>
#include <string>
#include <SDL2/SDL_net.h>//so my system does not have SDL_NET 2.0

#include <system_error>
#include <memory>

#include "configparser.h"
#include "structs.h"
#include "server_socket_TCP.hpp"
#include "server_socket_UDP.hpp"
#include <thread>
#include "message_writer.h"

/**
 * \brief Initializes ALL SDL subsystems that will be used
 * \details Initializes SDL_net
 * \return Whether all subsystems initialized correctly or at least one failed
 */
bool InitSDL()
{
    // Initialise SDL_net
	if (SDLNet_Init() == -1)
	{
		std::cout<<"SDL_net could not initialize! Error: "<<SDLNet_GetError()<<std::endl;
        return false;
	}

    return true;
}

/**
 * \brief Terminates all SDL subsystems and clears "global" pointers
 * \details Tries to reset (clear) all "global" pointers and terminates NET subsystems
 */
void TerminateSDL()
{
    //Quit SDL subsystems
    // Shutdown SDLNet - the ServerSocketTCP will clean up after itself on destruction
	SDLNet_Quit();
}

//{ TCP MAIN LOOP
void TCPMainLoop(std::unique_ptr<ServerSocketTCP>& tcp_server_socket, bool & quit, bool& start_server)
{
    if(!start_server)
        return;
    try
    {
        // index for the client with detected activity, -1if no activity
        int active_clients_index = -1;

        MessageWriter::Instance()->WriteLineToConsole("MESSAGE: STARTED TCP SERVER");

        // Main loop...
        while (!quit)
        {
            tcp_server_socket->UpdateSocketSet();

            // Check for any incoming connections to the server socket, the accept call is non-blocking
            tcp_server_socket->CheckForNewConnections();

            // At least once, but as many times as necessary to process all active clients
            do
            {
                // get client index with unprocessed activity (returns -1 if none)
                active_clients_index = tcp_server_socket->CheckForSocketActivity();

                //found one
                if (active_clients_index != -1)
                {
                    tcp_server_socket->ProcessSocketActivity(active_clients_index);
                }
            }
            while (active_clients_index != -1);


        }



    }
    catch (SocketException e)
    {
        std::cerr << "Caught an exception in the main loop..." << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << "Terminating application." << std::endl;

        quit = true;//break threads loops
    }
}
//}

//{ UDP MAIN LOOP
void UDPMainLoop(std::unique_ptr<ServerSocketUDP>& udp_server_socket, bool& quit, bool& start_server)
{
    if(!start_server)
        return;
    try
    {
        MessageWriter::Instance()->WriteLineToConsole("MESSAGE: STARTED UDP SERVER");

        // Main loop...
        while (!quit)
        {
            //update the activity flag for the udp server socket
            udp_server_socket->UpdateSocketActivity();

            // process for any incoming packet if the activity flag is up
            udp_server_socket->ProcessSocketActivity();
        }
    }
    catch (SocketException e)
    {
        std::cerr << "Caught an exception in the main loop..." << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << "Terminating application." << std::endl;

        quit = true;//break threads loops
    }
}
//}

//{ MAIN
int main(int argc, char *argv[])
{
    //Json var to hold application base configuration
    Json::Value config_json;

    //Tries to load(from file) application configuration into config_json var
    if(ProgramConfigReader(argc, argv, config_json) != 0)
        return -1;

    bool quit = false;

    //init SDL subsystems
    bool init_result = InitSDL();

    if(!init_result)
    {
        //failed to initialize sdl

        //terminate any initialized sdl subsystems
        TerminateSDL();

        return -2;
    }
    else
    {
        bool start_tcp = config_json["start_tcp_server"].asBool();
        bool start_udp = config_json["start_udp_server"].asBool();

        std::unique_ptr<ServerSocketTCP> tcp_server_socket;
        std::unique_ptr<ServerSocketUDP> udp_server_socket;

        //tcp server
        try
        {
            if(start_tcp)
            {
                // Try to instantiate the server socket
                // Parameters: port number, buffer size (i.e. max message size), max sockets
                tcp_server_socket.reset(new ServerSocketTCP(config_json["tcp_default_port"].asInt(), config_json["message_buffer_size"].asInt(), config_json["max_clients"].asInt()));
            }

        }
        catch (SocketException e)
        {
            std::cout << "Something went wrong creating a SocketServerTCP object." << std::endl;
            std::cout << "Error is: " << e.what()   << std::endl;
            std::cout << "Terminating..." << std::endl;

            //terminate any initialized sdl subsystems
            TerminateSDL();
            return -3;
        }

        //udp server
        try
        {
            if(start_udp)
            {
                // Try to instantiate the server socket
                // Parameters: port number, buffer size (i.e. max message size), max sockets
                udp_server_socket.reset(new ServerSocketUDP(config_json["udp_default_port"].asInt(), config_json["message_buffer_size"].asInt() ));
            }
        }
        catch (SocketException e)
        {
            std::cout << "Something went wrong creating a SocketServerUDP object." << std::endl;
            std::cout << "Error is: " << e.what()   << std::endl;
            std::cout << "Terminating..." << std::endl;

            //terminate any initialized sdl subsystems
            TerminateSDL();
            return -4;
        }

        //I know that the main thread will remain unused.
        //I chose this solution to make the code clearer

        //start server threads
        std::thread tcp_thread (TCPMainLoop, std::ref(tcp_server_socket), std::ref(quit), std::ref(start_tcp));
        std::thread udp_thread (UDPMainLoop, std::ref(udp_server_socket), std::ref(quit), std::ref(start_udp));

        MessageWriter::Instance()->WriteLineToConsole("Type 'q', 'quit' or 'exit' to shutdown the server");
        //kill the app
        std::string console_input;
        while(!quit)
        {
            //read from the console to check if we have to kill the app
            std::cin >> console_input;
            if(console_input == "q" || console_input == "quit" || console_input == "exit")
                quit = true;
        }

        //join all threads
        tcp_thread.join();
        udp_thread.join();

    }

    //Terminate SDL and clear "global" pointers
    TerminateSDL();

    return 0;
}
//}
