#include "eulerproblems.h"

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

//init static var
std::unique_ptr<ProblemsResults> ProblemsResults::s_instance;

std::unique_ptr<ProblemsResults>& ProblemsResults::Instance()
{
    //possibly move initialization to a new function and CALL IT at the beginning of the program
    //and remove this check, as it will run every time Instance() is called
    if(!s_instance)//does not exists
    {
        s_instance.reset(new ProblemsResults);
    }

    return s_instance;
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

    auto result = m_results.find(problem_number);

    std::string result_str = "";

    if(result != m_results.end())//found it
    {
        result_str = "RESULT|"+problem_number+"|"+result->second+"|END|";
        m_udp_server->SendMessage(client_ip, result_str);
    }
    else
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

void ProblemsResults::SolveProblem(std::string problem_number)
{
    unsigned int problem = std::stoul( problem_number );
    //std::cout<<"START: "<<problem_number<<std::endl;
    switch(problem)
    {
        case 1: { std::thread t(Problem001); t.detach(); } break;
        case 2: { std::thread t(Problem002); t.detach(); } break;
        case 3: { std::thread t(Problem003); t.detach(); } break;
        case 4: { std::thread t(Problem004); t.detach(); } break;
        case 5: { std::thread t(Problem005); t.detach(); } break;
        case 6: { std::thread t(Problem006); t.detach(); } break;
        case 7: { std::thread t(Problem007); t.detach(); } break;
        case 8: { std::thread t(Problem008); t.detach(); } break;
        case 9: { std::thread t(Problem009); t.detach(); } break;
        case 10: { std::thread t(Problem010); t.detach(); } break;
        //case 2: std::thread t2(Problem002); m_running_thread[t2.get_id()] = t2; t2.detach(); break;

        case 11: { std::thread t(Problem011); t.detach(); } break;
        case 12: { std::thread t(Problem012); t.detach(); } break;
        case 13: { std::thread t(Problem013); t.detach(); } break;
        case 14: { std::thread t(Problem014); t.detach(); } break;
        case 15: { std::thread t(Problem015); t.detach(); } break;
        case 16: { std::thread t(Problem016); t.detach(); } break;
        case 17: { std::thread t(Problem017); t.detach(); } break;
        case 18: { std::thread t(Problem018); t.detach(); } break;
        case 19: { std::thread t(Problem019); t.detach(); } break;
        case 20: { std::thread t(Problem020); t.detach(); } break;

        case 21: { std::thread t(Problem021); t.detach(); } break;
        case 22: { std::thread t(Problem022); t.detach(); } break;
        case 23: { std::thread t(Problem023); t.detach(); } break;
        case 24: { std::thread t(Problem024); t.detach(); } break;
        case 25: { std::thread t(Problem025); t.detach(); } break;
        //case 26: { std::thread t(Problem006); t.detach(); } break;
        case 27: { std::thread t(Problem027); t.detach(); } break;
        //case 28: { std::thread t(Problem008); t.detach(); } break;
        case 29: { std::thread t(Problem029); t.detach(); } break;
        case 30: { std::thread t(Problem030); t.detach(); } break;

        case 34: { std::thread t(Problem034); t.detach(); } break;
        case 35: { std::thread t(Problem035); t.detach(); } break;
        case 36: { std::thread t(Problem036); t.detach(); } break;

        case 42: { std::thread t(Problem042); t.detach(); } break;
        case 48: { std::thread t(Problem048); t.detach(); } break;

        case 67: { std::thread t(Problem067); t.detach(); } break;

        case 81: { std::thread t(Problem081); t.detach(); } break;
    }
}
