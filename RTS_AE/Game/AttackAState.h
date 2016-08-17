#pragma once
#include "AnimationState.h"
class CAttackAState :
	public CAnimationState
{
public:
	CAttackAState();
	virtual ~CAttackAState();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int  OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

