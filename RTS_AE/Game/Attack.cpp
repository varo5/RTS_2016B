#include "stdafx.h"
#include "Attack.h"


CAttack::CAttack()
{
	m_nStateID = static_cast<int>(UnitStates::ATTACK);
}


CAttack::~CAttack()
{
}

void CAttack::Init(aeStateMachineScript* pScript)
{
}

void CAttack::Destroy()
{
}

int CAttack::OnUpdate(float fDelta, aeBaseClass* pObject)
{
	(*(CUnit*)pObject).m_bWalking = false;
	if (!((*(CUnit*)pObject).m_pEnemy) || !((*(CUnit*)pObject).m_pEnemy)->IsAlive()) 
		return static_cast<int>(UnitStates::IDLE);

	if (((*(CUnit*)pObject).m_pEnemy)->InRange())
	{
		if ((*(CUnit*)pObject).m_fAttackTimer == (*(CUnit*)pObject).m_pBaseUnit->m_fAttack_Speed)
		{
				((*(CUnit*)pObject).m_pEnemy)->GetHit((*(CUnit*)pObject).m_pBaseUnit->m_fStrength);
				(*(CUnit*)pObject).m_bCanHit = false;
		}
		else if ((*(CUnit*)pObject).m_fAttackTimer < 0)
		{
			(*(CUnit*)pObject).m_fAttackTimer = (*(CUnit*)pObject).m_pBaseUnit->m_fAttack_Speed;
			(*(CUnit*)pObject).m_bCanHit = true;
			return static_cast<int>(UnitStates::ATTACK);
		}
		
		(*(CUnit*)pObject).m_fAttackTimer -= fDelta;
		
		return static_cast<int>(UnitStates::ATTACK);
	}
	else if ((*(CUnit*)pObject).Distance(((*(CUnit*)pObject).m_pEnemy)->m_vPosition) < (*(CUnit*)pObject).m_pBaseUnit->m_fAttack_Range_Min)
	{
		(*(CUnit*)pObject).m_vDestination = ((((*(CUnit*)pObject).m_pEnemy)->m_vPosition- (*(CUnit*)pObject).m_vPosition).Normalize())*-((*(CUnit*)pObject).m_pBaseUnit->m_fAttack_Range_Min);
		(*(CUnit*)pObject).Move(fDelta);
		return static_cast<int>(UnitStates::ATTACK);
	}
	else
	{
		(*(CUnit*)pObject).m_bWalking = true;
		(*(CUnit*)pObject).m_vDestination = ((*(CUnit*)pObject).m_pEnemy)->m_vPosition;
		if (((*(CUnit*)pObject).m_vDestination - (*(CUnit*)pObject).m_vPosition).Magnitude() > (*(CUnit*)pObject).m_pBaseUnit->m_fAttack_Range_Max)
		{
			(*(CUnit*)pObject).Move(fDelta);
		}
		return static_cast<int>(UnitStates::ATTACK);
	}
}

void CAttack::OnEnter()
{
}


void CAttack::OnExit()
{
}
