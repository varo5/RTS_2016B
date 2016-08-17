#include "aeCoreStd.h"
#include "Inputs.h"

namespace aeCore
{
	static KeyStatesDecode KeyStateMachine[2][2] =
	{
		KeyStatesDecode::StillReleased,
		KeyStatesDecode::JustPressed,
		KeyStatesDecode::JustReleased,
		KeyStatesDecode::StillPressed
	};

	aeKeyStates::aeKeyStates()
	{
	}

	aeKeyStates::aeKeyStates(uint8 NumericValue, bool LastState, bool CurrentState)
	{
		this->NumericValue = NumericValue;
		this->LastState = LastState;
		this->CurrentState = CurrentState;
	}

	aeKeyStates::aeKeyStates(uint8 NumericValue, uint8 States)
	{
		this->NumericValue = NumericValue;
		this->States = States;
	}

	aeKeyStates::~aeKeyStates()
	{
	}

	void aeKeyStates::UpdateKeyState(bool CurrentState)
	{
		LastState = CurrentState;
		CurrentState = CurrentState;
	}


	aeKeyboard::aeKeyboard()
	{
	}

	aeKeyboard::~aeKeyboard()
	{
	}

	int aeKeyboard::Init()
	{
		for (size_t i = 0; i < m_pCurrentState.size(); i++)
		{
			m_pLastState[i] = false;
			m_pCurrentState[i] = false;
		}
		return 0;
	}

	void aeKeyboard::Update()
	{
		m_pCurrentState.swap(m_pLastState);
		GetKeyboardState(&m_pCurrentState[0]);

		for (size_t i = 0; i < m_pCurrentState.size(); i++)
		{
			KeyStatesDecode State = (*this)[i];
			if (State == KeyStatesDecode::JustPressed || State == KeyStatesDecode::JustReleased)
			{
				aeKeyboardEvent* pEvent = new aeKeyboardEvent();
				pEvent->Type = static_cast<uint8>(EventTypes::KeyboardEvent);
				pEvent->Priority = static_cast<uint8>(EventPriority::Medium);
				pEvent->Key = static_cast<uint8>(i);
				pEvent->State = static_cast<uint8>(State);
				PostEvent(pEvent);
			}
		}
	}

	KeyStatesDecode aeKeyboard::operator[](int Key)
	{
		return KeyStateMachine[m_pLastState[Key] ? 1 : 0][m_pCurrentState[Key] ? 1 : 0];
	}

	aeMouse::aeMouse()
	{
	}

	aeMouse::~aeMouse()
	{
	}

	int aeMouse::Init()
	{
		m_pButtons[0] = aeKeyStates{ VK_LBUTTON, false, false };
		m_pButtons[1] = aeKeyStates{ VK_MBUTTON, false, false };
		m_pButtons[2] = aeKeyStates{ VK_RBUTTON, false, false };
		return 0;
	}

	void aeMouse::Update()
	{
		CURSORINFO cursorInfo = { 0 };
		cursorInfo.cbSize = sizeof(cursorInfo);

		if (GetCursorInfo(&cursorInfo))
		{
			if (cursorInfo.ptScreenPos.x != m_pointCurrentPosition.x || cursorInfo.ptScreenPos.y != m_pointCurrentPosition.y)
			{
				aeMouseMoveEvent* pMove = new aeMouseMoveEvent();
				pMove->Type = static_cast<uint8>(EventTypes::MouseMove);
				pMove->Priority = static_cast<uint8>(EventPriority::Low);
				pMove->x = static_cast<uint16>(cursorInfo.ptScreenPos.x);
				pMove->y = static_cast<uint16>(cursorInfo.ptScreenPos.y);
				PostEvent(pMove);
			}
			m_pointCurrentPosition.x = cursorInfo.ptScreenPos.x;
			m_pointCurrentPosition.y = cursorInfo.ptScreenPos.y;
		}

		int Size = sizeof(m_pButtons) / sizeof(aeKeyStates);
		bool boolean = false;
		for (int i = 0; i < Size; i++)
		{
			boolean = false;
			int Key = m_pButtons[i].NumericValue;
			if (GetAsyncKeyState(Key) & 0x8000)
				boolean = true;
			UpdateButton(i, boolean);
			KeyStatesDecode State = (*this)[Key];
			if (State == KeyStatesDecode::JustPressed || State == KeyStatesDecode::JustReleased)
			{
				aeMouseButtonEvent* pClic = new aeMouseButtonEvent();
				pClic->Type = static_cast<uint8>(EventTypes::MouseClic);
				pClic->Priority = static_cast<uint8>(EventPriority::Medium);
				pClic->x = m_pointCurrentPosition.x;
				pClic->y = m_pointCurrentPosition.y;
				pClic->Button = Key;
				pClic->State = static_cast<uint8>(State);
				PostEvent(pClic);
			}
		}
	}

	void aeMouse::UpdateButton(int Key, bool CurrentState)
	{
		m_pButtons[Key].UpdateKeyState(CurrentState);
	}

	aePoint aeMouse::GetLastClicPosition()
	{
		return m_vClicPosition;
	}
	aePoint aeMouse::GetCurrentPosition()
	{
		return m_pointCurrentPosition;
	}

	KeyStatesDecode aeMouse::operator[](int Key)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_pButtons[i].NumericValue == Key)
			{
				return KeyStateMachine[m_pButtons[i].LastState ? 1 : 0][m_pButtons[i].CurrentState ? 1 : 0];
			}
		}
		return KeyStatesDecode::Error;
	}

	aeInputs::aeInputs()
	{
	}

	aeInputs::~aeInputs()
	{

	}

	int aeInputs::Init()
	{
		if (Keyboard.Init() || Mouse.Init())
		{
			return -1;
		}
		return 0;
	}

	void aeInputs::Update()
	{
		Keyboard.Update();
		Mouse.Update();
	}
}