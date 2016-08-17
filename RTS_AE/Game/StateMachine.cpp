#include "stdafx.h"
#include "StateMachine.h"


aeStateMachine::aeStateMachine()
{
	m_nClassID = ClassId::StateMachine;
	m_pCurrentState = nullptr;
}


aeStateMachine::~aeStateMachine()
{
	Destroy();
}

void aeStateMachine::Init(aeStateMachineScript* pScript)
{
	m_pScript = pScript;
	m_pScript->SetStateList(&m_aPosibleStates);
	m_pScript->SetStateReference(&m_pCurrentState);
	for each (CState* State in m_aPosibleStates)
	{
		State->Init(pScript);
	}
}

void aeStateMachine::AddState(CState * NewState)
{
	m_aPosibleStates.push_back(NewState);
}

void aeStateMachine::SetState(int NewState)
{
	m_pScript->SetState(NewState);
}

void aeStateMachine::OnUpdate(float fDelta, aeBaseClass * pObject)
{
	SetState(((CUnit*)pObject)->m_nCurrentState);
	((CUnit*)pObject)->m_nCurrentState = m_pCurrentState->OnUpdate(fDelta, pObject);
}

void aeStateMachine::Destroy()
{
	for each (CState* State in m_aPosibleStates)
	{
		State->Destroy();
	}
}
