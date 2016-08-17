#include "stdafx.h"
#include "AttackAState.h"


CAttackAState::CAttackAState()
{
	m_nStateID = static_cast<int>(UnitStates::ATTACK);
}


CAttackAState::~CAttackAState()
{
}

void CAttackAState::Init(aeStateMachineScript* pScript)
{
	SetWorldReference((aeWorld*)((CAnimationStateMachine*)pScript)->pPassAlong);
}

void CAttackAState::Destroy()
{
}

int CAttackAState::OnUpdate(float fDelta, aeBaseClass * pObject)
{
	float fAngle = (*(CUnit*)pObject).m_vDirection.AngleBetweenVectors(aeVector2(1, 0));
	fAngle *= 180 / PI;
	if (fAngle < 0)
	{
		fAngle += 360;
	}
	m_bCiclic = true;
	m_bPaused = false;
	m_bPlaying = true;
	m_bStopped = false;
	int Direction = Trunc( fAngle / 60);
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		float temp = fAngle - 45 * i;
		if (temp < 45)
		{
			Direction = i;
			break;
		}
	}
	int ID = ((CUnit*)pObject)->m_pBaseUnit->m_nImageID;
	int State = ((CUnit*)pObject)->m_nCurrentState;
	if (((CUnit*)pObject)->CanHit())
	{
		m_bCiclic = false;
		m_bPaused = true;
		m_bPlaying = true;
		m_bStopped = false;
	} 
	if (((CUnit*)pObject)->m_bWalking)
	{
		State = static_cast<int>(UnitStates::MOVE_TO);
	}
	else
	{
		State = static_cast<int>(UnitStates::ATTACK);
	}
	((CUnit*)pObject)->m_pRenderer->Booleans = m_byteBooleans;
	switch (Direction)
	{
	case 0:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::W)), true);
		break;
	case 1:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::NW)), true);
		break;
	case 2:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::N)), false);
	case 3:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::NW)), false);
	case 4:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::W)), false);
		break;
	case 5:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::SW)), false);
		break;
	case 6:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::S)), false);
		break;
	case 7:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::SW)), true);
		break;
	case 8:
		((CUnit*)pObject)->m_pRenderer->SetObject(
			m_pWorldReference->GetAnimation(ID, State, static_cast<int>(Directions::W)), true);
		break;
	default:
		break;
	}
	return 0;
}

void CAttackAState::OnEnter()
{
}

void CAttackAState::OnExit()
{
}
