using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System;


public class ProblemsClientTCP : NetworkClient 
{
	TcpClient m_client;
	NetworkStream m_client_stream;
	//thread receiving the data from the server
	Thread m_receive_thread;
	Queue<string> m_received_data;
	Mutex m_data_mutex;

	ASCIIEncoding m_encoding;
	byte[] m_receive_bytes;
	byte[] m_send_bytes;

	public void Init()
	{
		m_encoding = new ASCIIEncoding ();
		m_data_mutex = new Mutex ();
		m_received_data = new Queue<string> ();

		m_receive_bytes = new byte[64];

		Connect ();
	}

	//try to connect to a server
	public override void Connect()
	{
		if (m_client != null && m_client.Connected)
			return;
		try
		{
			string ip = m_ip_input.text;
			string port = m_port_input.text;

			ip.Trim();
			port.Trim();

			if(ip.Length == 0)
			{
				ip = "127.0.0.1";
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

			m_client = new TcpClient();

			Debug.Log("Connecting.....");
			m_client.Connect(ip, System.Convert.ToInt32(port)); // use the ipaddress as in the server program
			Debug.Log("Connected");

			m_client_stream = m_client.GetStream();

			m_receive_thread = new Thread (new ThreadStart (ReceiveData));
			m_receive_thread.Start ();

			StartCoroutine(KeepAlive());

			m_connect_panel.SetActive(false);

			//as the connection can take some time (handshake and stuff) I need to request the list multiple times to avoid failure
			StartCoroutine (RequestListCoroutine());
		}
		catch(System.Exception e) 
		{
			m_error_text.text = e.Message;
		}
	}

	IEnumerator RequestListCoroutine()
	{
		var wait = new WaitForSeconds (0.05f);

		RequestList ();
		yield return wait;
		RequestList ();
		yield return wait;
		RequestList();
		yield return wait;
		RequestList();
		yield return wait;
		RequestList ();
	}

	public override void RequestList()
	{
		if (m_client != null && m_client.Connected) 
		{
			string str = "LIST|END|";

			m_send_bytes = m_encoding.GetBytes (str);

			m_client_stream.Write (m_send_bytes, 0, m_send_bytes.Length);
		}
	}

	//sends a request to the server for a specific problem
	public override void RequestProblem(string problem_number)
	{
		if (m_client != null && m_client.Connected) 
		{
			string str = "REQUEST|"+problem_number+"|END|";

			m_send_bytes = m_encoding.GetBytes (str);

			m_client_stream.Write (m_send_bytes, 0, m_send_bytes.Length);
		}
	}

	//Unity Update, process the message queue
	void Update()
	{		
		m_data_mutex.WaitOne ();//the queue might be in use by the receive data thread

		while (m_received_data.Count > 0) //process entire queue in one go
		{
			ProcessData(m_received_data.Dequeue());
		}

		m_data_mutex.ReleaseMutex ();
	}

	//sends a message to the server to keep checking the connection, as client.Connected only stores the state of the last action
	//so we keep sending messages to keep client.Connected updated
	IEnumerator KeepAlive()
	{
		while(m_client.Connected)
		{
			yield return new WaitForSeconds (1);

			try
			{
				m_send_bytes = m_encoding.GetBytes ("SUP|END|");

				m_client_stream.Write (m_send_bytes, 0, m_send_bytes.Length);
			}
			catch(System.Exception e)
			{
				Debug.Log (e.Message);

				m_error_text.text = "Disconnected from server.";
				Close (false);
			}
		}
	}

	//reads data from the socket and stores it in a queue
	//we need the queue to send the data to the main thread as unity gives an error if an UI element is 
	//used by other than the main thread
	void ReceiveData()
	{
		while (m_client.Connected) 
		{
			// Read can return anything from 0 to numBytesToRead. 
			// This method blocks until at least one byte is read.
			//m_client_stream.Read (m_receive_bytes, 0, 64);

			string message = "";

			while (m_client_stream.DataAvailable)
			{
				m_client_stream.Read (m_receive_bytes, 0, 64);
				message += Encoding.UTF8.GetString (m_receive_bytes);
				message.Trim ();

				//clear Array. If next read does not use athe entire array, we need to clean it after using it
				Array.Clear (m_receive_bytes, 0, 64);
			}

			//message.Trim ();
			//mutex to control the access to the queue as it is being used by this thread and the main thread.
			//it is needed because only the main thread can access some properties of UI elements, so I have to pass the data to it,
			//by using the queue
			m_data_mutex.WaitOne ();
			m_received_data.Enqueue(message);
			m_data_mutex.ReleaseMutex ();

			//if(message.Length > 0)
				//Debug.Log (message);
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

			/*while (exploded_data[1].Length < 3)
				exploded_data[1] = "0" + exploded_data[1];

			m_results_text.text +="P"+exploded_data[1]+": "+exploded_data[2]+"\n";*/
		}
		else if (exploded_data [0].CompareTo ("LIST") == 0)
		{
			m_problems_input.SetList (exploded_data);
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
