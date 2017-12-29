# Project Euler project

I uploaded the code to github for convenience, but if anyone finds it useful, even as a bad example, good.

This project is based on my old [project euler](https://github.com/N4G170/project_euler).
It was made to test how easy it would be to make the project euler local program in a distributed one (client-server).
The answer, it was somewhat trivial.

The server was made in cpp and SDL_net(semi-raw sockets) and runs in a terminal. It can listen for UDP, TCP or both types of requests. Each protocol has its own thread.
The windows version of the server has some problems disabled.

The client was made using unity3d for the UI and raw C# sockets for the communication.
Currently when I open it in newer version of unity, the resulting build has its networking part broken.

WARNING: If you want to solve them yourself do not read my solutions, study the maths and try.

## Running the program
Start the server, the the client, connect to the server using the right protocol and ip  and request solutions and have fun.

To config the server protocol and ports, use the config file and reload the server.

NOTE: The default ip on the client builds is no longer in use. Insert the correct server ip (most likely 127.0.0.1).

## Building the program

Give the current state of the client, I do not recommend build any of it. Instead you can test the old builds on the releases page.

If you try, src folder has the server and the client folder the unity project

## TODO

Find what the problem with the client is, solve it (or make a new one), and update the server to have more solutions.
I will only do this after solving the problems with the windows build of the main [project euler](https://github.com/N4G170/project_euler).

If you find any bug of error, let me know.
