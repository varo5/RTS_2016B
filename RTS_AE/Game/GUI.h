#pragma once
#include "Awesomium/WebManager.h"

class aeGUI : public aeBaseClass
{
public:

	/**********************************************************************************************//**
	 * @class	InitVariables
	 *
	 * @brief	Its meant to facilitate the initialization of the GUI class.
	 **************************************************************************************************/

	struct InitVariables
	{
		aeString pszBinFilePath; 
		aeString pszFileName;
		aeRect WindowRect; 
		aeWorld* pWorld; 
		aeRenderer * pRenderer; 
		SpriteList* pSprites; 
		PresetsList* pPresetList;
	};
	/************************************************************************************************************************/
	/* Declaration of the constructor and destructor                            												*/
	/************************************************************************************************************************/
public:
	aeGUI();
	~aeGUI();

	/************************************************************************************************************************/
	/* Declaration of class functions                         												*/
	/************************************************************************************************************************/
	int Init(InitVariables * pInitVariables);
	void Destroy();

	void Update(float fDelta);
	void Render(aeRenderer* pRenderer);

	void Clic(aePoint& ClicPoint, int Button);
	void CursorUpdate(aePoint& CursorPosition);

	static int FontsDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int ButtonsDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName);


	/************************************************************************************************************************/
	/* Declaration of class variables                                 												*/
	/************************************************************************************************************************/
public:
	aeRenderer *m_pRenderer;

	std::vector<aeGUIObject*> m_aObjects;
	std::map<aeString,aeFont*> m_aFonts;
	SpriteList* m_pSprites;
	aeRect m_WindowRect;
	aeRect m_DstRect;
	aeString m_pszBinFilePath;
	PresetsList* m_pPresetList;

	CWebListener* m_pWebListener;

	aeWorld* m_pWorld;
};
