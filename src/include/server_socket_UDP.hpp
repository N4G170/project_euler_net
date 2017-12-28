#ifndef SERVER_SOCKET_UDP_H
#define SERVER_SOCKET_UDP_H
#include "define_flags.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL_net.h>
#include <vector>
#include <map>
#include <mutex>

#include "SocketException.h" //custom exception header which defines an inline class

class ServerSocketUDP
{
	private:
        /**
        * \brief TCP listen m_port
        */
		unsigned int m_port;
		/**
        * \brief The size of the message packet
        */
		unsigned int m_packet_size;

        /**
        * \brief The UDPsocket listening for new connections
        */
		UDPsocket m_server_socket;//UDPsocket is a pointer, why hide it from the user?
        /**
        * \brief The IP:Port pairs for this server socket. The IP will be 0.0.0.0 meaning "any ip"
        */
		IPaddress m_server_IP;
		/**
        * \brief The IP address of the server as a dot-quad string i.e. "127.0.0.1"
        */
		std::string m_dot_quad_string;
		/**
        * \brief Pointer to a udp packet used to read from the socket (it is like the buffer used in the tcp server)
        */
		UDPpacket* m_udp_packet_in;//receive from client
		UDPpacket* m_udp_packet_out;//send to client
		std::mutex m_send_mutex;

		/**
        * \brief All of our sockets in use, in a set to be used by SDL_net functions
        */
		SDLNet_SocketSet m_socket_set;

	public:

		ServerSocketUDP(unsigned int port, unsigned int packet_size);

		~ServerSocketUDP();

        /**
        * \brief Check if the socket received a packet
        */
		void UpdateSocketActivity();

		/**
        * \brief Process a received packet
        */
		void ProcessSocketActivity();

		/**
		* \brief Sends a datagram to the destination with the ipaddress in client_ip
		*/
		void SendMessage(IPaddress client_ip, std::string message);
};

#endif // SERVER_SOCKET_UDP_H
