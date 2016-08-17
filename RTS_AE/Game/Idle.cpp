#include "stdafx.h"
#include "Idle.h"


CIdle::CIdle()
{
	m_nStateID = static_cast<int>(UnitStates::IDLE);
}


CIdle::~CIdle()
{
}

void CIdle::Init(aeStateMachineScript* pScript)
{
}

void CIdle::Destroy()
{
}

int CIdle::OnUpdate(float fDelta, aeBaseClass* pObject)
{
	(*(CUnit*)pObject).m_bWalking = false;
	if (!((*(CUnit*)pObject).m_pBaseUnit->IsMilitant))
		return static_cast<int>(UnitStates::IDLE);
	
	std::vector<CUnit*>* Enemies = (*(CUnit*)pObject).GetEnemiesAround((*(CUnit*)pObject).m_pBaseUnit->m_fView_Range);
	if (Enemies->size() > 0)
	{
		float fShortestDistance = 100000;
		for (int i = 0; i < Enemies->size(); i++)
		{
			float fTemp = ((*Enemies)[i]->m_vPosition - (*(CUnit*)pObject).m_vPosition).Magnitude();
			if (fTemp< fShortestDistance && (&(*(CUnit*)pObject) != (*Enemies)[i]) )
			{
				fShortestDistance = fTemp;
				(*(CUnit*)pObject).m_pEnemy = (*Enemies)[i];
			}
		}
		return	 static_cast<int>(UnitStates::ATTACK);
	}
	return  static_cast<int>(UnitStates::IDLE);
}

void CIdle::OnEnter()
{
}

void CIdle::OnExit()
{
}
