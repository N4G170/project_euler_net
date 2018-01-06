#include "problems_results.hpp"
#include "eulerproblems.hpp"

std::string ProblemsResults::problems_list = "LIST|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|27|29|30|34|35|36|40|42|48|49|52|67|71|72|73|80|81|83|92|94|END";

ProblemsResults::ProblemsResults()
{
    m_tcp_server = nullptr;
    m_udp_server = nullptr;
}

ProblemsResults::~ProblemsResults()
{
    m_tcp_server = nullptr;
    m_udp_server = nullptr;
}

void ProblemsResults::RequestProblem(std::string problem_number, int client_index, ServerSocketTCP* server)
{
    if(m_tcp_server == nullptr)
        m_tcp_server = server;//store the server ref to let us send the result

    m_results_mutex.lock();

    auto result = m_results.find(problem_number);

    std::string result_str = "";

    if(result != m_results.end())//found it
    {
        result_str = "RESULT|"+problem_number+"|"+result->second+"|END|";
        m_tcp_server->SendMessage(client_index, result_str);
    }
    else
    {
        auto solving = m_problems_being_solved.find(problem_number);//check if the problem is already being solved

        if(solving == m_problems_being_solved.end())//start new thread
        {
            SolveProblem(problem_number);
        }

        std::pair<int, IPaddress> client;
        client.first = client_index;
        //if the map entry does not exist, just by calling it we create it
        m_problems_being_solved[problem_number].push(client);//save client in queue
    }

    m_results_mutex.unlock();
}

void ProblemsResults::RequestProblem(std::string problem_number, IPaddress client_ip, ServerSocketUDP* server)
{
    if(m_udp_server == nullptr)
        m_udp_server = server;//store the server ref to let us send the result

    m_results_mutex.lock();

    //check if we have solved the problem
    auto result = m_results.find(problem_number);

    std::string result_str = "";

    if(result != m_results.end())//found it
    {
        result_str = "RESULT|"+problem_number+"|"+result->second+"|END|";
        m_udp_server->SendMessage(client_ip, result_str);
    }
    else//failed to find it, so we request it
    {
        auto solving = m_problems_being_solved.find(problem_number);//check if the problem is already being solved

        if(solving == m_problems_being_solved.end())//start new thread
        {
            SolveProblem(problem_number);
        }

        std::pair<int, IPaddress> client;
        client.first = -1;
        client.second = client_ip;

        //if the map entry does not exist, just by calling it we create it
        m_problems_being_solved[problem_number].push(client);//save client in queue
    }

    m_results_mutex.unlock();
}

void ProblemsResults::SetStoredResult(std::string problem_number, std::string result)
{
    m_results_mutex.lock();
    m_results[problem_number] = result;

    std::string result_to_send = "RESULT|"+problem_number+"|"+result+"|END|";

    while(m_problems_being_solved[problem_number].size() > 0)
    {
        std::pair<int, IPaddress> client = m_problems_being_solved[problem_number].front();
        m_problems_being_solved[problem_number].pop();

        if(client.first >= 0)//tcp client
            m_tcp_server->SendMessage(client.first, result_to_send);
        else//udp client
            m_udp_server->SendMessage(client.second, result_to_send);
    }

    m_results_mutex.unlock();
}

void ProblemsResults::CheckFuture()
{
    //checks if a running problem finished processing and prints its result
    for(auto& problem : m_problems_future)
    {
        //the auto var will be a std::pair, being the Key the first var and its value the second var
        //the second itself is a std::pair, that holds a bool(first) that tells if the problem is running
        //and the second holds the problem future
        if(problem.second.first && problem.second.second.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        // if(problem.second.first && problem.second.second.valid())
        {
            problem.second.first = false;
            this->SetStoredResult(std::to_string(problem.first), problem.second.second.get());
        }
    }
}

void ProblemsResults::SolveProblem(std::string problem_number)
{
    unsigned int requested_problem = std::stoul( problem_number );

    //std::cout<<"START: "<<problem_number<<std::endl;
    switch(requested_problem)
    {
        case 1: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem001); break;
        case 2: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem002); break;
        case 3: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem003); break;
        case 4: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem004); break;
        case 5: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem005); break;
        case 6: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem006); break;
        case 7: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem007); break;
        case 8: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem008); break;
        case 9: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem009); break;
        case 10: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem010); break;

        case 11: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem011); break;
        case 12: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem012); break;
        case 13: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem013); break;
        case 14: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem014); break;
        case 15: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem015); break;
        case 16: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem016); break;
        case 17: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem017); break;
        case 18: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem018); break;
        case 19: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem019); break;
        case 20: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem020); break;

        case 21: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem021); break;
        case 22: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem022); break;
        case 23: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem023); break;
        case 24: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem024); break;
        case 25: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem025); break;

        //case 26: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem026); break;
        case 27: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem027); break;
        //case 28: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem028); break;
        case 29: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem029); break;
        case 30: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem030); break;

        case 34: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem034); break;
        case 35: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem035); break;
        case 36: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem036); break;
        case 40: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem040); break;

        case 42: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem042); break;

        //case 47: if(!m_problems_future[requested_problem].first){ m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem047); } break;
        case 48: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem048); break;
        case 49: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem049); break;

        case 52: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem052); break;
        // case 54: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem054); break;

        //case 61: if(!m_problems_future[requested_problem].first){ m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem061); } break;
        case 67: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem067); break;

        case 71: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem071); break;
        case 72: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem072); break;
        case 73: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem073); break;
        //case 74: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem074); break;

        case 80: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem080); break;
        case 81: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem081); break;
        //case 82: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem082); break;
        case 83: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem083); break;

        case 92: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem092); break;
        case 94: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem094); break;

        // default:  break;
    }
}
