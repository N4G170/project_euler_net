using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ClientSelector : MonoBehaviour 
{
	public ProblemsClientTCP m_tcp_client;
	public ProblemsClientUDP m_udp_client;

	public Toggle m_tcp_toggle;
	public Toggle m_udp_toggle;
	public ProblemInput m_problems;

	public void Connect()
	{
		if (m_tcp_toggle.isOn) 
		{
			m_udp_client.gameObject.SetActive(false);
			m_tcp_client.gameObject.SetActive(true);
			m_tcp_client.Init ();

			m_problems.m_can_update = true;
			return;
		}

		if (m_udp_toggle.isOn) 
		{
			m_tcp_client.gameObject.SetActive(false);
			m_udp_client.gameObject.SetActive(true);
			m_udp_client.Init ();

			m_problems.m_can_update = true;
			return;
		}
	}

	public void Disconnect()
	{
		if (m_tcp_client.gameObject.activeSelf) 
		{
			m_tcp_client.Close ();
			m_problems.m_can_update = false;
			return;
		}

		if (m_udp_client.gameObject.activeSelf) 
		{
			m_udp_client.Close ();
			m_problems.m_can_update = false;
			return;
		}
	}
}
