# Project Euler project

I uploaded the code to github for convenience, but if anyone finds it useful, even as a bad example, good.

This project is based on my old [project euler](https://github.com/N4G170/project_euler).
I made it to test how easy it would be to make the project euler local program into a distributed one (client-server).

WARNING: If you want to solve them yourself do not read my solutions, study the maths and try.

The server was made in c++ and SDL_net(semi-raw sockets) and runs in a terminal. It can listen for UDP, TCP or both types of requests(edit config.json file inside data).
This program uses several threads, as many of its functionalities depend on blocking functions, mainly the protocols processing, they have their own threads to avoid any blocks between them.
The client UI was made using unity3d and raw C# sockets were used for for the communication.

At the time of this writing, the client was build using unity3d 2017.2.0f3 and the server has the same problems available as the standalone Project Euler program.

The program works the following way:
- Turn both server and client on;
- On client select the protocol to use (client can only use one at a time, the server can listen to both);
- Client requests the list of available problem to the server;
- Client requests new problem;
  - If client already received the result (from a previous request during the run), load the local value;
  - If not, send a request to the server;
- Server receives a request for a problem;
  - If the problem was already solved (from a previous request during the run), send the local value;
  - If not, check if there is a std::async task already solving the problem;
    - If yes, way in a queue for it to finish and then send the result;
    - If not, start a new std::async task to solve the problem. When the task ends, read the future and store the result, then send the result;
- Client receives the result, stores and shows it.

There is no support for NAT punchthrough or any other NAT bypass methods. Use only local or non NAT hidden IP.

## Running the program
Start the server and the client, connect to the server using the right protocol and ip/port and request solutions and have fun.

To configure the server protocol and ports, use the data/config.json file and reload the server.

## Building the program

After some work I was able to correctly configure and use cmake on windows, that way a VS project can be easly made.

### Server
#### Linux
On linux (x64 only) make sure you have the needed dependencies:
- SDL2;
- SDL2_net;
- GMP;
- Cmake;//for build configuration

Then run cmake using the commands on a terminal:
```
- mkdir build
- cd build
- cmake ..
- make -j
```
If all goes right, inside the build folder and using the terminal, you can run the server with "./euler_server". To move the program, copy the binary euler_server and the data folder.

#### Windows
The project was configured with cmake and built using VS express 15.
First download [cmake](https://cmake.org/), run it and use the project root folder(the one with data and src folders and more) as the source. For the build folder, point to an empty folder of your choice, usually a folder named build is created in the project root (check linux build instructions). Then generate the project, be sure to <b>SELECT A 64bit GENERATOR</b> the server does not run on 32bits.
If all goes right, inside the build folder you have a solution, run it and build on release mode. Inside the release folder you will have the server the data folder and the needed dlls.

### Client

Inside the client folder there is a unity3d project, open it (I used unity 2017.f.0f3) and build it, there is nothing more to it.

## TODO
I want to clean the network code and make more redundancy and fail-safe features.


As network programs are tricky to extensively test on my own, if you find any bug, error or crash, let me know.
