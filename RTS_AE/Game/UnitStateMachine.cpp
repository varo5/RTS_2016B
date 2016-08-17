#include "stdafx.h"
#include "UnitStateMachine.h"

CUnitStateMachine::CUnitStateMachine()
{
	m_nClassID = ClassId::StateMachineScript;
}


CUnitStateMachine::~CUnitStateMachine()
{
}

void CUnitStateMachine::SetState(int NewState)
{
	if (*m_ppCurrentState != nullptr)
	{
		if (*((CUnitState*)*m_ppCurrentState) == NewState)
		{
			return;
		}
		(*m_ppCurrentState)->OnExit();
	}
	
	for each (CState* State in *m_pStateList)
	{
		if ((*((CUnitState*)State) == static_cast<int>(UnitStates::IDLE)) && (NewState == static_cast<int>(UnitStates::IDLE)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CUnitState*)State) == static_cast<int>(UnitStates::DEATH)) && (NewState == static_cast<int>(UnitStates::DEATH)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CUnitState*)State) == static_cast<int>(UnitStates::MOVE_TO)) && (NewState == static_cast<int>(UnitStates::MOVE_TO)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CUnitState*)State) == static_cast<int>(UnitStates::ATTACK)) && (NewState == static_cast<int>(UnitStates::ATTACK)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
	}
	(*m_ppCurrentState)->OnEnter();
}

