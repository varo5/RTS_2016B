#include "stdafx.h"
#include "Death.h"


CDeath::CDeath()
{
	m_nStateID = static_cast<int>(UnitStates::DEATH);
}


CDeath::~CDeath()
{
}

void CDeath::Init(aeStateMachineScript* pScript)
{
}

void CDeath::Destroy()
{
}

int CDeath::OnUpdate(float fDelta, aeBaseClass* pObject)
{
	(*(CUnit*)pObject).m_bWalking = false;
	return static_cast<int>(UnitStates::DEATH);
}


void CDeath::OnEnter()
{
}


void CDeath::OnExit()
{
}
