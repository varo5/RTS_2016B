#pragma once
#include "AnimationState.h"
class CIdleAState :
	public CAnimationState
{
public:
	CIdleAState();
	virtual ~CIdleAState();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int  OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

