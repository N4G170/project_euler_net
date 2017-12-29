using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;
using System.Threading;


public class ProblemsClientUDP : NetworkClient 
{
	UdpClient m_client;

	//thread receiving the data from the server
	Thread m_receive_thread;
	Queue<string> m_received_data;
	Mutex m_data_mutex;
	Mutex m_timer_mutex;

	IPEndPoint m_remote_end_point;
	ASCIIEncoding m_encoding;
	byte[] m_receive_bytes;
	byte[] m_send_bytes;

	int m_timer_onhold_value = -2;
	float m_timer = 0;//-1 will suspend the timer
	int m_max_time = 10;//time to wait for an answer after a request

	public void Init()
	{
		m_encoding = new ASCIIEncoding ();
		m_data_mutex = new Mutex ();
		m_timer_mutex = new Mutex ();
		m_received_data = new Queue<string> ();

		m_receive_bytes = new byte[64];

		m_timer = m_timer_onhold_value;

		Connect ();
	}

	//try to "connect" to a server, actually it sets the new remote host as the default
	public override void Connect()
	{
		if (m_client != null)
			return;
		try
		{
			string ip = m_ip_input.text;
			string port = m_port_input.text;

			ip.Trim();
			port.Trim();

			if(ip.Length == 0)
			{
				ip = "51.255.196.122";
			}
			if(port.Length == 0)
			{
				port = "45456";
			}

			//check if inserted ip is valid
			if(!CheckValidIP(ip))
			{				
				m_error_text.text = "Invalid IP";
				return;
			}

			m_client = new UdpClient();
			m_client.DontFragment = true;

			Debug.Log("Connecting.....");
			m_client.Connect(ip, System.Convert.ToInt32(port)); // use the ipaddress as in the server program
			Debug.Log("Connected");

			m_remote_end_point = new IPEndPoint(IPAddress.Parse(ip), 0);

			m_receive_thread = new Thread (new ThreadStart (ReceiveData));
			m_receive_thread.Start ();

			m_connect_panel.SetActive(false);
		}
		catch(System.Exception e) 
		{
			m_error_text.text = e.Message;
		}
	}

	//sends a request to the server for a specific problem
	public override void RequestProblem(string problem_number)
	{
		if (m_client != null) 
		{
			string str = "REQUEST|"+problem_number+"|END|";

			m_send_bytes = m_encoding.GetBytes (str);

			m_client.Send (m_send_bytes, m_send_bytes.Length);

			//reset Timer
		}
	}

	//Unity Update, process the message queue
	void Update()
	{		
		m_timer_mutex.WaitOne ();
		if (m_timer > 0) 
		{
			m_timer -= Time.deltaTime;

			if (m_timer <= 0 && m_timer > m_timer_onhold_value) //just a small interval for safety
			{
				m_error_text.text = "Timeout "+m_max_time+"s: no answer from server.";
				Close (false);
			}
		}
		m_timer_mutex.ReleaseMutex ();


		m_data_mutex.WaitOne ();//the queue might be in use by the receive data thread

		while (m_received_data.Count > 0) //process entire queue in one go
		{
			ProcessData(m_received_data.Dequeue());
		}

		m_data_mutex.ReleaseMutex ();
	}

	//reads data from the socket and stores it in a queue
	//we need the queue to send the data to the main thread as unity gives an error if an UI element is 
	//used by other than the main thread
	void ReceiveData()
	{
		while (m_client != null) 
		{
			// Read can return anything from 0 to numBytesToRead. 
			// This method blocks until at least one byte is read.
			m_receive_bytes = m_client.Receive(ref m_remote_end_point);

			string message = Encoding.UTF8.GetString (m_receive_bytes);
			message.Trim ();
			//mutex to control the access to the queue as it is being used by this thread and the main thread.
			//it is needed because only the main thread can access some properties of UI elements, so I have to pass the data to it,
			//by using the queue
			m_data_mutex.WaitOne ();
			m_received_data.Enqueue(message);
			m_data_mutex.ReleaseMutex ();

			if(message.Length > 0)
				Debug.Log (message);
		}

	}

	//close the socket and return to the connect panel
	public void Close (bool reset_error = true)
	{
		m_client.Close ();
		m_client = null;

		if(reset_error)
			m_error_text.text = "";
		
		m_connect_panel.SetActive(true);
		gameObject.SetActive (false);
	}

	//process the received data and writes/stores it
	void ProcessData(string data)
	{
		string[] exploded_data = data.Split ('|');

		if (exploded_data [0].CompareTo ("INFO") == 0) 
		{
			m_server_text.text += exploded_data [1] + "\n";
		} 
		else if (exploded_data [0].CompareTo ("RESULT") == 0)
		{
			//save the result for later use
			m_problems_input.StoreResult (exploded_data[1], exploded_data[2]);

			while (exploded_data[1].Length < 3)
				exploded_data[1] = "0" + exploded_data[1];

			m_results_text.text +="P"+exploded_data[1]+": "+exploded_data[2]+"\n";
		}
	}

	//checks if the input ip is a valid ip to be used
	public bool CheckValidIP(string ip)
	{
		string[] arr_octets = ip.Split('.');
		if (arr_octets.Length != 4)//has 4 octets
			return false;

		//Check each substring checking that parses to byte
		byte obyte = 0;
		foreach (string str_octet in arr_octets)
			if (!byte.TryParse(str_octet, out obyte)) 
				return false;

		return true;
	}
}
