using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;
using System.Threading;

//this class is not in use right now (although it is the base class for the clients)
public class NetworkClient : MonoBehaviour
{
	public Text m_results_text;
	public Text m_server_text;
	public ProblemInput m_problems_input;

	public GameObject m_connect_panel;
	public InputField m_ip_input;
	public InputField m_port_input;
	public Text m_error_text;

	public virtual void Connect (){}
	public virtual void RequestProblem(string problem_number){}
}