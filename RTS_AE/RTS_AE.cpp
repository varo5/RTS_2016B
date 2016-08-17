/*! \mainpage My Personal Index Page
*
* \section intro_sec Introduction
*
* This is the introduction.
*
* \section install_sec Installation
*
* \subsection step1 Step 1: Opening the box
*
* etc...
*/

#include "stdafx.h"

/**********************************************************************************************//**
 * @fn	int main(int argc, char *args[])
 *
 * @brief	Main entry-point for this application.
 *
 * @param	argc	Number of command-line arguments.
 * @param	args	Array of command-line argument strings.
 *
 * @return	Exit-code for the process - 0 for success, else an error code.
 **************************************************************************************************/

int main(int argc, char *args[])
{
	aeApp App;
	int Proceed = App.Init();
	if (!Proceed)
	{
		while (App.IsRunning())
		{
			App.Update();
		}
	}
    return 0;
}

