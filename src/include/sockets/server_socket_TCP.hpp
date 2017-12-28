#ifndef SERVER_SOCKET_TCP_H
#define SERVER_SOCKET_TCP_H
#include "define_flags.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL_net.h>
#include <vector>
#include <map>

#include "SocketException.h" //custom exception header which defines an inline class

class ServerSocketTCP
{
	private:
        /**
        * \brief TCP listen m_port
        */
		unsigned int m_port;
		/**
        * \brief The size of the message buffer
        */
		unsigned int m_buffer_size;
		/**
        * \brief Max number of sockets (connections) that we can process (will be m_max_clients + 1 as the server listen socket takes one slot)
        */
		unsigned int m_max_sockets;    // Max number of sockets
		/**
        * \brief Max number of clients in our socket set (defined as m_max_sockets - 1 as the server socket itself take 1 m_port)
        */
		unsigned int m_max_clients;

        /**
        * \brief The IP:Port pairs for this server socket. The IP will be 0.0.0.0 meaning "any ip"
        */
		IPaddress m_server_IP;
		/**
        * \brief The TCPsocket listening for new connections
        */
		TCPsocket m_server_socket;//TCPsocket is a pointer, why hide it from the user?
		/**
        * \brief The IP address of the server as a dot-quad string i.e. "127.0.0.1"
        */
		std::string m_dot_quad_string;

        /**
        * \brief std::vector holding all the TCPsocket objects in use and free to use (the free are a nullptr)
        */
		std::vector<TCPsocket> m_client_sockets;
		/**
        * \brief std::vector with the socket slots in use marked as false
        */
		std::vector<bool> m_free_sockets;
		/**
        * \brief Array of characters used to store the messages we receive
        */
		char* m_buffer;

        /**
        * \brief All of our sockets in use, in a set to be used by SDL_net functions
        */
		SDLNet_SocketSet m_socket_set;

        /**
        * \brief How many clients are currently connected to the serve
        */
		unsigned int m_client_count;

	public:
	    //static string with messages
		static const std::string SERVER_NOT_FULL;
		static const std::string SERVER_FULL;

		ServerSocketTCP(unsigned int port, unsigned int buffer_size, unsigned int max_sockets);

		~ServerSocketTCP();

        /**
        * \brief Update the socket set, marking the sockets with activity. MUST BE CALLED BEFORE ANY OTHER SOCKET FUNCTION
        */
        void UpdateSocketSet();

		/**
        * \brief Check if there are new connections
        */
		void CheckForNewConnections();

        /**
        * \brief Check the activity of a socket (message sent/connection lost)
        * \return client "id" or -1 in no active clients
        */
		int CheckForSocketActivity();

		/**
        * \brief If a client did something, we process it here
        */
		void ProcessSocketActivity(unsigned int client_number);

        /**
        * \brief Sends a message through a connected stream (called socket in this lib)
        * \param target_index the stored index of the client \see m_client_sockets
        */
		void SendMessage(int target_index, std::string message);
		void SendMessage(TCPsocket& target, std::string message);
		void SendMessage(int target_index, char* message);
};


#endif//SERVER_SOCKET_TCP_H
