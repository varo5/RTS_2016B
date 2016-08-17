#include "stdafx.h"
#include "Move_To.h"


CMove_To::CMove_To()
{
	m_nStateID = static_cast<int>(UnitStates::MOVE_TO);
}


CMove_To::~CMove_To()
{
}

void CMove_To::Init(aeStateMachineScript* pScript)
{
}

void CMove_To::Destroy()
{
}

int CMove_To::OnUpdate(float fDelta, aeBaseClass* pObject)
{
	(*(CUnit*)pObject).m_bWalking = false;
	if (((*(CUnit*)pObject).m_vDestination - (*(CUnit*)pObject).m_vPosition).Magnitude() > (*(CUnit*)pObject).m_pBaseUnit->m_nRadius)
	{
		(*(CUnit*)pObject).m_bWalking = true;
		(*(CUnit*)pObject).Move(fDelta);
		return static_cast<int>(UnitStates::MOVE_TO);
	}
	return static_cast<int>(UnitStates::IDLE);
}

void CMove_To::OnEnter()
{
}


void CMove_To::OnExit()
{
}
