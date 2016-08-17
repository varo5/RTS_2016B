#include "stdafx.h"
#include "AnimationStateMachine.h"

CAnimationStateMachine::CAnimationStateMachine()
{
	m_nClassID = ClassId::StateMachineScript;
}


CAnimationStateMachine::~CAnimationStateMachine()
{
}

void CAnimationStateMachine::SetState(int NewState)
{
	if (*m_ppCurrentState != nullptr)
	{
		if (*((CAnimationState*)*m_ppCurrentState) == NewState)
		{
			return;
		}
		(*m_ppCurrentState)->OnExit();
	}

	for each (CState* State in *m_pStateList)
	{
		if ((*((CAnimationState*)State) == static_cast<int>(AnimationStates::IDLE)) && (NewState == static_cast<int>(AnimationStates::IDLE)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CAnimationState*)State) == static_cast<int>(AnimationStates::DEATH)) && (NewState == static_cast<int>(AnimationStates::DEATH)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CAnimationState*)State) == static_cast<int>(AnimationStates::MOVE_TO)) && (NewState == static_cast<int>(UnitStates::MOVE_TO)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
		else if ((*((CAnimationState*)State) == static_cast<int>(AnimationStates::ATTACK)) && (NewState == static_cast<int>(AnimationStates::ATTACK)))
		{
			(*m_ppCurrentState) = State;
			break;
		}
	}
	(*m_ppCurrentState)->OnEnter();
}
