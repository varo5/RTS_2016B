#pragma once
#include "UnitState.h"
#include "Unit.h"
class CAttack :
	public CUnitState
{
public:
	CAttack();
	~CAttack();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

