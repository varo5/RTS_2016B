/**********************************************************************************************//**
 * @file	Game\Scripts.h
 *
 * @brief	Declares the scripts class.
 **************************************************************************************************/

#pragma once
#include "AddOn.h"

/**********************************************************************************************//**
 * @enum	ScriptId
 *
 * @brief	Values that represent script identifiers.
 **************************************************************************************************/

enum struct ScriptId
{
	SpriteRenderer = 0,		/**< Sprite Renderer script ID */
	AnimationRenderer,		/**< Animation Renderer script ID */
	ButtonScript,			/**< Button script ID */
	UserScript				/**< User script ID */
};

/**********************************************************************************************//**
 * @class	aeScript
 *
 * @brief	A script.
 **************************************************************************************************/

class aeScript : public aeAddOn
{
	/************************************************************************************************************************/
	/* Constructors declaration                                            													*/
	/************************************************************************************************************************/
public:
	aeScript();
	virtual ~aeScript();

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	ScriptId aeScript::GetScriptId();
	 *
	 * @brief	Gets script identifier.
	 *
	 * @return	The script identifier.
	 **************************************************************************************************/

	ScriptId GetScriptId();

	/************************************************************************************************************************/
	/* Variable declaration									                												*/
	/************************************************************************************************************************/
protected:
	ScriptId m_nScriptID;
};

