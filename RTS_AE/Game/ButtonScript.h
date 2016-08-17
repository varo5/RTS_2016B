/**********************************************************************************************//**
 * @file	Game\ButtonScript.h
 *
 * @brief	Declares the button script class.
 **************************************************************************************************/

#pragma once
#include "Scripts.h"

 /** @brief	The button state machine. */
static uint8 ButtonStateMachine[2][2] = { 0,1,2,3 };

enum struct ButtonState : uint8
{
	StillReleased = 0,	/**< If the button is not pressed */
	JustPressed,		/**< If the button was just pressed */
	JustReleased,		/**< If the button was just released */
	StillPressed,		/**< If the button is being pressed */
	DoubleClick,		/**< If the button was pressed twice within the time constraints */
	Error 				/**< If the button is not registered */
};

/**********************************************************************************************//**
 * @class	aeButtonScript
 *
 * @brief	A button script.
 **************************************************************************************************/
class aeButtonScript : public aeScript
{
public:
	aeButtonScript();
	aeButtonScript(aeBaseClass* pParent);
	~aeButtonScript();

public:

	int Init(aeBaseClass* pParent);
	void Update(float fDelta);
	void Render(aeRenderer * pRenderer);
	void Destroy();

	void SetSprite(aeSprite* pSprite);

	/**********************************************************************************************//**
	 * @fn	ButtonState aeGUIButton::GetState();
	 *
	 * @brief	Gets the state.
	 *
	 * @return	The state.
	 **************************************************************************************************/

	ButtonState GetState();

	/**********************************************************************************************//**
	 * @fn	void aeGUIButton::ClickOn(aePoint Point);
	 *
	 * @brief	Click on.
	 *
	 * @param	Point	The point.
	 **************************************************************************************************/

	void ClickOn(aePoint Point);

	void SetFunction(std::function<void(void)> Function, ButtonState ExecState);

	void MirrorX(bool Flip);
	void MirrorY(bool Flip);

public:
	
	float Angle;

	int OrderOfRender;
	
	aeRect RenderRect;
	aeRect SourceRect;

protected:
	std::map<ButtonState, std::vector<std::function<void(void)>>> m_aFunction;

	union
	{
		struct
		{
			bool m_bLastState : 1;
			bool m_bCurrentState : 1;
			bool m_bDblClick : 1;
			bool m_bMirrorX : 1;
			bool m_bMirrorY : 1;
		};
		uint8 m_Flags;
	};
	
	float m_fTimeForDblClick;
	float m_fCounter;

	int m_nFlip;

	aeSprite* m_pSprite;
};