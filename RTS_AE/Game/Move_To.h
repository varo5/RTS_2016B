#pragma once
#include "Unit.h"
#include "UnitState.h"
class CMove_To :
	public CUnitState
{
public:
	CMove_To();
	~CMove_To();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

