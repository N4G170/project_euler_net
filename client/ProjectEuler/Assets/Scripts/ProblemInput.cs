﻿using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;

public class ProblemInput : MonoBehaviour 
{
	public ProblemsClientTCP m_tcp_client;
	public ProblemsClientUDP m_udp_client;

	public InputField m_input_field;
	public Text m_result_text;
	public Text m_problems_list;

	private Dictionary<string, string> m_results;
	private List<KeyValuePair<string, string>> m_render_results;
	public bool m_can_update;

	//change this to a message sent by the server with its available problems
	public List<string> m_available_problems;

	public void Start()
	{
		m_available_problems = new List<string>();

		m_results = new Dictionary<string, string> ();
		m_render_results = new List<KeyValuePair<string, string>> ();
		m_can_update = false;

		StartCoroutine (WriteToResult ());
	}

	IEnumerator WriteToResult()
	{
		var wait = new WaitForSeconds (0.005f);

		while(true)
		{
			string text="";

			foreach(var entry in m_render_results)
			{
				string result = entry.Key;
				while (result.Length < 3)
					result = "0" + result;
				text +="P"+result+": "+entry.Value+"\n";
			}

			m_result_text.text = text;
			yield return wait;
		}
	}

	//Update, reads input and updates the problems input box
	void Update()
	{
		if(!m_can_update)//no client active so we block this update
			return;

		if (Input.GetKeyDown (KeyCode.Alpha0) || Input.GetKeyDown (KeyCode.Keypad0)) 
		{
			if(m_input_field.text.Length > 0)//this avoids left side zeros
				m_input_field.text += 0;
		}
		if(Input.GetKeyDown(KeyCode.Alpha1) || Input.GetKeyDown(KeyCode.Keypad1))
			m_input_field.text += 1;
		if(Input.GetKeyDown(KeyCode.Alpha2) || Input.GetKeyDown(KeyCode.Keypad2))
			m_input_field.text += 2;
		if(Input.GetKeyDown(KeyCode.Alpha3) || Input.GetKeyDown(KeyCode.Keypad3))
			m_input_field.text += 3;
		if(Input.GetKeyDown(KeyCode.Alpha4) || Input.GetKeyDown(KeyCode.Keypad4))
			m_input_field.text += 4;
		if(Input.GetKeyDown(KeyCode.Alpha5) || Input.GetKeyDown(KeyCode.Keypad5))
			m_input_field.text += 5;
		if(Input.GetKeyDown(KeyCode.Alpha6) || Input.GetKeyDown(KeyCode.Keypad6))
			m_input_field.text += 6;
		if(Input.GetKeyDown(KeyCode.Alpha7) || Input.GetKeyDown(KeyCode.Keypad7))
			m_input_field.text += 7;
		if(Input.GetKeyDown(KeyCode.Alpha8) || Input.GetKeyDown(KeyCode.Keypad8))
			m_input_field.text += 8;
		if(Input.GetKeyDown(KeyCode.Alpha9) || Input.GetKeyDown(KeyCode.Keypad9))
			m_input_field.text += 9;

		if (Input.GetKeyDown (KeyCode.Return) || Input.GetKeyDown (KeyCode.KeypadEnter))
			OK ();
	}

	//save the result of a problem to avoid calling the server again
	public void StoreResult(string problem_number, string result)
	{
		m_render_results.Add (new KeyValuePair<string, string>(problem_number, result));
		if (!m_results.ContainsKey (problem_number)) 
		{
			m_results.Add (problem_number, result);
		}
	}

	public void ButtonDown(int number)
	{
		if (number == 0) 
		{
			if(m_input_field.text.Length > 0)//this avoids left side zeros
				m_input_field.text += 0;
		}
		else
			m_input_field.text += number;
	}

	public void Clear()
	{
		m_input_field.text = "";
	}

	//request problem solution
	public void OK()
	{
		if (m_input_field.text.Length <= 0)
			return;

		string problem_number = m_input_field.text;

		//problem does not have a solution, yet
		if (!ProblemIsAvailable (problem_number)) 
		{
			while (problem_number.Length < 3)
				problem_number = "0" + problem_number;
			m_result_text.text +="P"+problem_number+" is not available\n";

			m_input_field.text = "";//clear proble input box
			return;
		}

		//we already have the solution, so no request is made and we display the solution 
		if (m_results.ContainsKey (problem_number)) 
		{
			string result = m_results [problem_number];

			//while (problem_number.Length < 3)
				//problem_number = "0" + problem_number;

			m_render_results.Add (new KeyValuePair<string, string>(problem_number, result));
			//m_result_text.text +="P"+problem_number+": "+result+"\n";
		} 
		else //uses the loaded client
		{
			if(m_tcp_client.gameObject.activeSelf)
				m_tcp_client.RequestProblem (problem_number);
			else
				m_udp_client.RequestProblem (problem_number);
		}

		m_input_field.text = "";
	}

	//check if a problem can be solved by the server
	bool ProblemIsAvailable(string problem_number)
	{
		bool exists = false;

		/*if (m_available_problems.Find (number => number.CompareTo (problem_number) == 0))
			return true;*/
		for (int i = 0; i < m_available_problems.Count; i++) 
		{
			if (m_available_problems [i] == problem_number) 
			{
				exists = true;
				break;
			}
		}

		return exists;
	}

	public void SetList(string[] list)
	{
		string list_string = "Available problems: ";
		m_available_problems.Clear ();

		//ignore first and last
		for (int i = 1; i < list.Length -1; ++i)
		{
			m_available_problems.Add (list [i]);
			list_string += list [i];

			if(i < list.Length - 2)//ignore last problem
				list_string += ", ";
		}

		m_problems_list.text = list_string;
	}
}
