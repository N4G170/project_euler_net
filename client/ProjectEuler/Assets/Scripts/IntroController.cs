using UnityEngine;
using System.Collections;

public class IntroController : MonoBehaviour 
{
	public GameObject m_intro_panel;
	
	// Update is called once per frame
	void Update () 
	{
		if (Input.GetKeyDown (KeyCode.KeypadEnter) || Input.GetKeyDown (KeyCode.Return)) 
		{
			m_intro_panel.SetActive (false);
		}
	}
}
