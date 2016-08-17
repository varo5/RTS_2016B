#pragma once
#include "UnitType.h"
#include "StateMachine.h"
#include "UnitStateMachine.h"
#include "UserScript.h"
#include "AnimationRenderer.h"
#include "AnimationStateMachine.h"

class CUnitStateMachine;

class CUnit : public aeUserScript
{	
public:
	CUnit();
	virtual ~CUnit();

	int m_nTeam_ID;
	int m_nHP;
	int m_nCurrentState;
	bool m_bCanHit;
	bool m_bWalking;
	float m_fAttackTimer;
	float m_fCurrenTime;

	aeUnitType * m_pBaseUnit;
	aeVector2 m_vPosition;
	aeVector2 m_vDirection;
	aeVector2 m_vDestination;

	std::vector<CUnit*> m_aUnits;
	std::vector<CUnit*> m_aEnemies;
	std::vector<aeStateMachine*>* m_pStateMachines;

	CAnimationRenderer * m_pRenderer;
	
	CUnit * m_pEnemy;
	CUnit * m_pFriend;

	int Init(aeBaseClass* pParent);
	void Destroy();
	void Update(float fDelta);

	void Move(float fDelta);
	void GetHit(float Damage);

	void SetUnitsAround(std::list<aeGameObject*>* GameObjects);
	std::vector<CUnit*>* GetEnemiesAround(float Range);

	bool CanAttack();
	bool CanBuild();
	bool EnemiesAround(float Range);
	bool IsAlive();
	bool InRange();
	bool CanHit();
	bool InRange(aeVector2 Point);
	float Distance(aeVector2 Position);
};