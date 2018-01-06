#ifndef PROBLEMS_RESULTS_HPP
#define PROBLEMS_RESULTS_HPP

#include <memory>
#include <queue>
#include <utility>
#include <mutex>
#include <map>
#include <thread>
#include <vector>
#include "server_socket_TCP.hpp"
#include "server_socket_UDP.hpp"
#include <string>
#include <future>

/**
 * \brief Singleton class storing the calculated results for the problems
 */
class ProblemsResults
{
    public:
        ProblemsResults();
        virtual ~ProblemsResults();

        void SetStoredResult(std::string problem_number, std::string result);

        //for TCP clients
        void RequestProblem(std::string problem_number, int client_index, ServerSocketTCP* server);

        //for UDP clients
        void RequestProblem(std::string problem_number, IPaddress client_ip, ServerSocketUDP* server);

        void CheckFuture();

        static std::string problems_list;

    private:

        void SolveProblem(std::string problem_number);

        static std::unique_ptr<ProblemsResults> s_instance;

        /**
        * \brief Constrols access to \see m_results
        */
        std::mutex m_results_mutex;

        /**
        * \brief Stores the results from previously calculated problems
        */
        std::map<std::string, std::string> m_results;
        /**
        * \brief Map with the problem number as key and a list of clients waiting for its result to be calculated
        * The std::pair stores the id in the int if the client is a tcp client and the ipaddr if udp client (the int will be -1 to mark it as an udp client)
        */
        std::map<std::string, std::queue< std::pair<int,IPaddress> >> m_problems_being_solved;

        /**
         * \brief Stores the futures of running problems
         */
        std::map< int, std::pair<bool, std::future<std::string>> > m_problems_future;

        /**
        * \brief Map storing the thread running
        */
        std::map<std::thread::id, std::thread> m_running_thread;

        /**
        * \brief Pointer to the instance of the TCP server (used to write the results on the stream)
        */
        ServerSocketTCP* m_tcp_server;

        /**
        * \brief Pointer to the instance of the UDP server (used to send the results)
        */
        ServerSocketUDP* m_udp_server;
};

#endif //PROBLEMS_RESULTS_HPP
