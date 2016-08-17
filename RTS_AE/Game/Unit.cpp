#include "stdafx.h"
#include "Unit.h"



CUnit::CUnit()
{
	m_nClassID = ClassId::AddOn;
	m_nAddOnID = AddOnId::Scripts;
	m_nScriptID = ScriptId::UserScript;
	m_nUserScriptID = static_cast<int>(UserScriptsID::Unit);
}

CUnit::~CUnit()
{
}

int CUnit::Init(aeBaseClass* pParent)
{
	m_pParent = pParent;
	m_nHP = m_pBaseUnit->m_fHP_Max;
	m_fAttackTimer = m_pBaseUnit->m_fAttack_Speed;
	m_nCurrentState = static_cast<int>(UnitStates::IDLE);
	m_vDestination = m_vPosition;
	m_fCurrenTime = 0;
	m_bCanHit = true;
	m_bWalking = false;
	return 0;
}

void CUnit::Destroy()
{
}

void CUnit::Update(float fDelta)
{
	for each (aeStateMachine* StateMachine in *m_pStateMachines)
	{
		StateMachine->SetState(m_nCurrentState);
		StateMachine->OnUpdate(fDelta, this);
	}
}

void CUnit::Move(float fDelta)
{
	m_vDirection = (m_vDestination - m_vPosition).Normalize();
	m_vPosition += m_vDirection * (m_pBaseUnit->m_fSpeed * fDelta);
	((aeGameObject*)m_pParent)->Transform.Position = aeVector3{ m_vPosition.x,m_vPosition.y };
}

void CUnit::GetHit(float Damage)
{
	m_nHP -= static_cast<int>(Damage);
	if (m_nHP <= 0)
		m_nCurrentState = static_cast<int>(UnitStates::DEATH);
}

void CUnit::SetUnitsAround(std::list<aeGameObject*>* GameObjects)
{
	std::vector<CUnit*> NewList;
	for each(auto object in *GameObjects)
		for each(auto AddOn in object->AddOns)
			if (AddOn->GetAddOnID() == AddOnId::Scripts)
				if (((aeScript*)AddOn)->GetScriptId() == ScriptId::UserScript)
					if ((((CUnit*)AddOn)->m_vPosition - m_vPosition).Magnitude() < m_pBaseUnit->m_fView_Range)
						NewList.push_back((CUnit*)AddOn);
	std::swap(m_aUnits, NewList);
}

std::vector<CUnit*>* CUnit::GetEnemiesAround(float Range)
{
	m_aEnemies.clear();
	for each(auto unit in m_aUnits)
		if (unit->m_nTeam_ID != this->m_nTeam_ID)
			if ((unit->m_vPosition - m_vPosition).Magnitude() < Range)
				m_aEnemies.push_back(unit);
	return &m_aEnemies;
}

bool CUnit::CanAttack()
{
	return m_pBaseUnit->IsMilitant;
}

bool CUnit::CanBuild()
{
	return m_pBaseUnit->CanBuild;
}

bool CUnit::EnemiesAround(float Range)
{
	for each (auto Unit in m_aUnits)
	{
		if (Unit->m_nTeam_ID != this->m_nTeam_ID)
		{
			return true;
		}
	}
	return false;
}

bool CUnit::IsAlive()
{
	bool bAlive = (m_nCurrentState == static_cast<int>(UnitStates::DEATH)) ? false : true;
	return bAlive;
}

bool CUnit::InRange()
{
	if (!m_pEnemy)return false;
	float fDistance = Distance(m_pEnemy->m_vPosition);
	if (fDistance > m_pBaseUnit->m_fAttack_Range_Min && fDistance <= m_pBaseUnit->m_fAttack_Range_Max)
	{
		return true;
	}
	return false;
}

bool CUnit::CanHit()
{
	return m_bCanHit;
}

bool CUnit::InRange(aeVector2 Point)
{
	float fDistance = Distance(Point);
	if (fDistance > m_pBaseUnit->m_fAttack_Range_Min && fDistance <= m_pBaseUnit->m_fAttack_Range_Max)
	{
		return true;
	}
	return false;
}

float CUnit::Distance(aeVector2 m_vPosition)
{
	return  (m_vPosition - this->m_vPosition).Magnitude();
}
