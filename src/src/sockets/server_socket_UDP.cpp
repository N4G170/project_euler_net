#include "server_socket_UDP.hpp"
#include "utils.hpp"
#include "problems_results.hpp"

ServerSocketUDP::ServerSocketUDP(unsigned int port, unsigned int packet_size, ProblemsResults* results): m_results{results}
{
    m_port = port;                      // The m_port number on the server we're connecting to
	m_packet_size = packet_size;        // The maximum size of a message

    m_udp_packet_in = SDLNet_AllocPacket(m_packet_size);
    m_udp_packet_out = SDLNet_AllocPacket(m_packet_size);
    m_udp_list_packet_out = SDLNet_AllocPacket(ProblemsResults::problems_list.size());

    // Create the socket set with enough space to store our desired number of sockets, in this case, 1 as we will only check the server's udp socket
	m_socket_set = SDLNet_AllocSocketSet(1);

	// Try to resolve the provided server hostname to an IP address.
	// If successful, this places the connection details in the m_server_IP object and creates a listening m_port on the
	// provided m_port number.
	// Note: Passing the second parameter as "NULL" means "make a listening m_port". SDLNet_ResolveHost returns one of two
	// values: -1 if resolving failed, and 0 if resolving was successful
	int hostResolved = SDLNet_ResolveHost(&m_server_IP, NULL, m_port);

	if (hostResolved == -1)
	{
		std::string msg = "Failed to resolve udp server host: ";
		msg += SDLNet_GetError();

		SocketException e(msg);
		throw e;
	}
	else // If we resolved the host successfully, output the details
	{
		#ifdef SERVER_DEBUGS
        // Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned
        // host address and splitting it into an array of four 8-bit unsigned numbers...
        Uint8 * dotQuad = (Uint8*)&m_server_IP.host;

        m_dot_quad_string  = std::to_string( (unsigned short)dotQuad[0] );
        m_dot_quad_string += ".";
        m_dot_quad_string += std::to_string( (unsigned short)dotQuad[1] );
        m_dot_quad_string += ".";
        m_dot_quad_string += std::to_string( (unsigned short)dotQuad[2] );
        m_dot_quad_string += ".";
        m_dot_quad_string += std::to_string( (unsigned short)dotQuad[3] );

        //... and then outputting them cast to integers. Then read the last 16 bits of the m_server_IP object to get the m_port number
        std::cout << "Successfully resolved server host to IP: " << m_dot_quad_string;
        std::cout << ", will use m_port " << SDLNet_Read16(&m_server_IP.port) << std::endl;
		#endif // SERVER_DEBUGS
	}

	// Try to open the server socket
	m_server_socket = SDLNet_UDP_Open(m_port);

	if (!m_server_socket)
	{
		std::string msg = "Failed to open udp server socket: ";
		msg += SDLNet_GetError();

		SocketException e(msg);
		throw e;
	}
	else
	{
        #ifdef SERVER_DEBUGS
		std::cout << "Sucessfully created server socket." << std::endl;
		#endif // SERVER_DEBUGS
	}

	// Add our server socket (i.e. the listening socket) to the socket set
	SDLNet_UDP_AddSocket(m_socket_set, m_server_socket);

	#ifdef SERVER_DEBUGS
    std::cout << "Awaiting for requests..." << std::endl;
	#endif // SERVER_DEBUGS

}//end constructor

ServerSocketUDP::~ServerSocketUDP()
{
    SDLNet_FreePacket(m_udp_packet_in);
    SDLNet_FreePacket(m_udp_packet_out);
    SDLNet_FreePacket(m_udp_list_packet_out);

    SDLNet_UDP_Close(m_server_socket);
    m_server_socket = nullptr;

    // Free our socket set
	SDLNet_FreeSocketSet(m_socket_set);
}

void ServerSocketUDP::UpdateSocketActivity()
{
    // Check for activity on the entire socket set. The second parameter is the number of milliseconds to wait for.
	// For the wait-time, 0 means do not wait but eats your cpu
	int total_active_sockets = SDLNet_CheckSockets(m_socket_set, 10);

	if (total_active_sockets != 0)
	{
		#ifdef SERVER_DEBUGS
        std::cout << "There are currently " << total_active_sockets << " socket(s) with data to be processed." << std::endl;
		#endif // SERVER_DEBUGS
	}
}

void ServerSocketUDP::ProcessSocketActivity()
{
    // Check if the listenning udp socket had activity (received something)
	if (SDLNet_SocketReady(m_server_socket) != 0)
	{
        int result = SDLNet_UDP_Recv(m_server_socket, m_udp_packet_in);

        if(result > 0)//success
        {
            std::string message( (char *)m_udp_packet_in->data );//the data is in a unit8 array
            std::vector<std::string> exploded_message = Explode(message, "|");

            //check the type of the message
            if(exploded_message[0].compare("REQUEST") == 0)
            {
                m_results->RequestProblem(exploded_message[1], m_udp_packet_in->address, this);

                message = "INFO|Processing UDP request for problem "+exploded_message[1]+"|END";
                //std::cout<<"RRRRRR - "<<m_udp_packet_in->address.host<<":"<<m_udp_packet_in->address.port<<" - "<<message<<std::endl;
                SendMessage(m_udp_packet_in->address, message);
                //SDLNet_UDP_Send(m_server_socket, -1, m_udp_packet_in);//works
            }
        	else if(exploded_message[0].compare("LIST") == 0)
        	{
                SendList(m_udp_packet_in->address);
        	}
        }
	}
}

void ServerSocketUDP::SendMessage(IPaddress client_ip, std::string message)
{
    m_send_mutex.lock();

    if(m_udp_packet_out == nullptr)
    {
        std::cout<<"Out packet not created"<<std::endl;
        return;
    }

    //configure package
    //memcpy(&m_udp_packet_out->address, &client_ip, sizeof(client_ip));
    //m_udp_packet_out->address = m_udp_packet_in->address;
    m_udp_packet_out->address = client_ip;
    m_udp_packet_out->channel = -1;
    m_udp_packet_out->data = (Uint8 *) message.c_str();
    m_udp_packet_out->len = m_packet_size;

	SDLNet_UDP_Send(m_server_socket, -1, m_udp_packet_out);//the channel -1 means, no channel used and the unbound udp socket will be used

    m_send_mutex.unlock();
}

void ServerSocketUDP::SendList(IPaddress client_ip)
{
    m_send_mutex.lock();

    if(m_udp_list_packet_out == nullptr)
    {
        std::cout<<"Out packet not created"<<std::endl;
        return;
    }

    //configure package
    //memcpy(&m_udp_list_packet_out->address, &client_ip, sizeof(client_ip));
    //m_udp_list_packet_out->address = m_udp_packet_in->address;
    m_udp_list_packet_out->address = client_ip;
    m_udp_list_packet_out->channel = -1;
    m_udp_list_packet_out->data = (Uint8 *) ProblemsResults::problems_list.c_str();
    m_udp_list_packet_out->len = ProblemsResults::problems_list.size();

	SDLNet_UDP_Send(m_server_socket, -1, m_udp_list_packet_out);//the channel -1 means, no channel used and the unbound udp socket will be used

    m_send_mutex.unlock();
}
