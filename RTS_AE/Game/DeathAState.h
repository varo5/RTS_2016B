#pragma once
#include "AnimationState.h"
class CDeathAState :
	public CAnimationState
{
public:
	CDeathAState();
	virtual ~CDeathAState();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int  OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

