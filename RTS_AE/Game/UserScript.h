/**********************************************************************************************//**
 * @file	Game\UserScript.h
 *
 * @brief	Declares the user script class.
 **************************************************************************************************/

#pragma once
#include "Scripts.h"

/**********************************************************************************************//**
 * @class	aeUserScript
 *
 * @brief	An user script.
 **************************************************************************************************/

class aeUserScript : public aeScript
{
	/************************************************************************************************************************/
	/* Constructors declaration                                            													*/
	/************************************************************************************************************************/
public:
	aeUserScript();
	virtual ~aeUserScript();

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	int aeUserScript::GetUserScriptId();
	 *
	 * @brief	Gets user script identifier.
	 *
	 * @return	The user script identifier.
	 **************************************************************************************************/

	int GetUserScriptId();

	/************************************************************************************************************************/
	/* Variable declaration									                												*/
	/************************************************************************************************************************/
protected:
	int m_nUserScriptID;
};