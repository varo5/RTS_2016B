#pragma once
#include "UnitState.h"
#include "Unit.h"
class CIdle :
	public CUnitState
{
public:
	CIdle();
	~CIdle();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

