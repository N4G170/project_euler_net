#include "server_socket_TCP.hpp"
#include "utils.hpp"
#include "eulerproblems.h"

// Static constants for the ServerSocket class
const std::string ServerSocketTCP::SERVER_NOT_FULL = "OK";
const std::string ServerSocketTCP::SERVER_FULL     = "FULL";

// ServerSocket constructor
ServerSocketTCP::ServerSocketTCP(unsigned int port, unsigned int buffer_size, unsigned int max_clients)
{
	m_port = port;                      // The m_port number on the server we're connecting to
	m_buffer_size = buffer_size;                // The maximum size of a message
	m_max_sockets = max_clients + 1;                // Maximum number of sockets in our socket set
	m_max_clients = max_clients;            // Maximum number of clients who can connect to the server

    m_client_sockets = std::vector<TCPsocket>(m_max_clients, nullptr);
    m_free_sockets = std::vector<bool>(m_max_clients, true);

	m_buffer = new char[m_buffer_size];            // Create the traSDLNet_GetErrornsmission buffer character array

	m_client_count = 0;


	// Create the socket set with enough space to store our desired number of connections (i.e. sockets)
	m_socket_set = SDLNet_AllocSocketSet(m_max_sockets);
	if (m_socket_set == nullptr)
	{
		std::string msg = "Failed to allocate the socket set: ";
		msg += SDLNet_GetError();

		SocketException e(msg);//custom pseudo exception
		throw e;
	}
	else
	{
	    #ifdef SERVER_DEBUGS
        std::cout << "Allocated socket set size: " << m_max_sockets << ", of which " << m_max_clients << " are free." <<  std::endl;
		#endif // SERVER_DEBUGS
	}

	// Initialize all the client sockets (i.e. blank them ready for use!)
	/*for (unsigned int loop = 0; loop < m_max_clients; loop++)
	{
		pClientSocket[loop] = NULL;
	}*/

	// Try to resolve the provided server hostname to an IP address.
	// If successful, this places the connection details in the m_server_IP object and creates a listening m_port on the
	// provided m_port number.
	// Note: Passing the second parameter as "NULL" means "make a listening m_port". SDLNet_ResolveHost returns one of two
	// values: -1 if resolving failed, and 0 if resolving was successful
	int hostResolved = SDLNet_ResolveHost(&m_server_IP, NULL, m_port);

	if (hostResolved == -1)
	{
		std::string msg = "Failed to open the server socket: ";
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
	m_server_socket = SDLNet_TCP_Open(&m_server_IP);

	if (!m_server_socket)
	{
		std::string msg = "Failed to open the server socket: ";
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
	SDLNet_TCP_AddSocket(m_socket_set, m_server_socket);

	#ifdef SERVER_DEBUGS
    std::cout << "Awaiting clients..." << std::endl;
	#endif // SERVER_DEBUGS

} // End of constructor

// ServerSocket destructor
ServerSocketTCP::~ServerSocketTCP()
{
	// Close all the open client sockets
	for (unsigned int i = 0; i < m_max_clients; i++)
	{
		if (!m_free_sockets[i])
		{
			SDLNet_TCP_Close(m_client_sockets[i]);
		}
	}

	// Close our server socket
	SDLNet_TCP_Close(m_server_socket);
    m_server_socket = nullptr;

	// Free our socket set
	SDLNet_FreeSocketSet(m_socket_set);

	// Release any properties on the heap
	delete m_buffer;
}

void ServerSocketTCP::UpdateSocketSet()
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

void ServerSocketTCP::CheckForNewConnections()
{
	// Check if the server socket had any activity
	// Note: SocketReady can only be called on a socket which is part of a SDLNet_SocketSet and that has CheckSockets called on it
	//The only activity that this socket can have is the arrival of a new client trying to connect
	if (SDLNet_SocketReady(m_server_socket) != 0)
	{
		// If we have room for more clients...
		if (m_client_count < m_max_clients)
		{
			// Find the first free socket in the std::vector of client sockets
			int free_slot = -1;
			for (unsigned int i = 0; i < m_max_clients; i++)
			{
				if (m_free_sockets[i] == true)
				{
					#ifdef SERVER_DEBUGS
                    std::cout << "Found a free spot at position: " << i << std::endl;
					#endif // SERVER_DEBUGS

					m_free_sockets[i] = false; //mark position as taken
					free_slot = i;
					break;
				}
			}

			//Accept the client connection#ifdef
			m_client_sockets[free_slot] = SDLNet_TCP_Accept(m_server_socket);//for some reason this Accept funtion is non blocking

			//Add the new client socket to the socket set
			SDLNet_TCP_AddSocket(m_socket_set, m_client_sockets[free_slot]);

			// Increase our client count
			m_client_count++;

			// Send a message to the client saying "OK" to indicate the incoming connection has been accepted
			/*strcpy( m_buffer, SERVER_NOT_FULL.c_str() );

			int message_size = strlen(m_buffer) + 1;

			SDLNet_TCP_Send(m_client_sockets[free_slot], (void *)m_buffer, message_size);*/

			SendMessage(free_slot, SERVER_NOT_FULL);
            std::cout<<"MESSAGE: TCP CONNECTED"<<std::endl;
			#ifdef SERVER_DEBUGS
			std::cout << "Client connected. There are now " << m_client_count << " client(s) connected." << std::endl;
			#endif // SERVER_DEBUGS
		}
		else // If we don't have room for new clients...
		{
		    #ifdef SERVER_DEBUGS
		    std::cout << "Max client count reached - rejecting client connection" << std::endl;
		    #endif // SERVER_DEBUGS

			// Accept the client connection to clear it from the incoming connections list
			TCPsocket temp_sock = SDLNet_TCP_Accept(m_server_socket);

			// Send a message to the client saying "FULL" to tell the client to go away
			/*strcpy( m_buffer, SERVER_FULL.c_str() );

			int message_size = strlen(m_buffer) + 1;

			SDLNet_TCP_Send(temp_sock, (void *)m_buffer, message_size);*/

			SendMessage(temp_sock, SERVER_FULL);

			// Shutdown, disconnect, and close the socket to the client
			SDLNet_TCP_Close(temp_sock);
		}

	} //if (SDLNet_SocketReady(m_server_socket) != 0)

}//CheckForNewConnections

// Function to do something appropriate with the detected socket activity
void ServerSocketTCP::ProcessSocketActivity(unsigned int client_number)
{
	// Get the contents of the buffer as a string
	std::string buffer_contents = m_buffer;//the m_buffer var was updated during the CheckForSocketActivity call (if there was activity)

	// Output the message the server received to the screen
	#ifdef SERVER_DEBUGS
    //std::cout << "Received: >>>> " << buffer_contents << " from client number: " << client_number << std::endl;
	#endif // SERVER_DEBUGS

    std::vector<std::string> exploded_message = Explode(buffer_contents, "|");

    //std::cout<<"RECEIVED: "<<buffer_contents<<std::endl;
    //check the type of the message
    if(exploded_message[0].compare("REQUEST") == 0)
    {
        ProblemsResults::Instance()->RequestProblem(exploded_message[1], client_number, this);

        buffer_contents = "INFO|Processing TCP request for problem "+exploded_message[1]+"|END";

        SendMessage(client_number, buffer_contents);
    }

}//ProcessSocketActivity

// Check all connected client sockets for activity
// If we find a client with activity we return its index or -1 for no activity
int ServerSocketTCP::CheckForSocketActivity()
{
    //SDLNet_CheckSockets was called previously by UpdateSocketSet
	// Loop to check all possible client sockets for activity
	for (unsigned int client_index = 0; client_index < m_max_clients; client_index++)
	{
		// non-zero for activity
		int client_socket_activity = SDLNet_SocketReady(m_client_sockets[client_index]);

		// The line below produces a LOT of debug messages, so only uncomment if the code's seriously misbehaving!
		#ifdef SERVER_DEBUGS
		//std::cout << "Client index " << client_index << " has activity status: " << client_socket_activity << std::endl;
        #endif // SERVER_DEBUGS

		//Found socket with activity
		if (client_socket_activity != 0)
		{
			// Check if the client socket has transmitted any data by reading from the socket and placing it in the buffer character array
			int received_byte_count = SDLNet_TCP_Recv(m_client_sockets[client_index], m_buffer, m_buffer_size);

			// If there was activity, but we didn't read anything from the client socket we assume that the client has disconnected...
			if (received_byte_count <= 0)
			{
				#ifdef SERVER_DEBUGS
				std::cout << "Client " << client_index << " disconnected." << std::endl;
				#endif // SERVER_DEBUGS

				//Free the socket slot to be used by another client
				SDLNet_TCP_DelSocket(m_socket_set, m_client_sockets[client_index]);//remove from set
				SDLNet_TCP_Close(m_client_sockets[client_index]);//close connection
				m_client_sockets[client_index] = nullptr;//free slot

				//mark postion as free
				m_free_sockets[client_index] = true;

				//decrement total clients
				m_client_count--;
                std::cout<<"MESSAGE: TCP DISCONNECTED"<<std::endl;
				#ifdef SERVER_DEBUGS
                std::cout << "Server is now connected to: " << m_client_count << " client(s)." << std::endl;
                #endif // SERVER_DEBUGS
			}
			else//some data was read
			{
				//resturns the client index that will be processed by ProcessSocketActivity
				return client_index;
			}

		}//if (client_socket_activity != 0)

	}//for

	// If we got here then there are no more clients with activity to process!
	return -1;

}//CheckForSocketActivity

void ServerSocketTCP::SendMessage(int target_index, std::string message)
{
    if(m_client_sockets[target_index] == nullptr)//client no longer exists
        return;

    strcpy( m_buffer, message.c_str() );

	int message_size = strlen(m_buffer) + 1;

	SDLNet_TCP_Send(m_client_sockets[target_index], (void *)m_buffer, message_size);
}

void ServerSocketTCP::SendMessage(TCPsocket& target, std::string message)
{
    strcpy( m_buffer, message.c_str() );

	int message_size = strlen(m_buffer) + 1;

	SDLNet_TCP_Send(target, (void *)m_buffer, message_size);
}

void ServerSocketTCP::SendMessage(int target_index, char* message)
{
    if(m_client_sockets[target_index] == nullptr)//client no longer exists
        return;

    strcpy( m_buffer, message );

	int message_size = strlen(m_buffer) + 1;

	SDLNet_TCP_Send(m_client_sockets[target_index], (void *)m_buffer, message_size);
}
