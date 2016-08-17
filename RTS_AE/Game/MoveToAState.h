#pragma once
#include "AnimationState.h"
class CMoveToAState :
	public CAnimationState
{
public:
	CMoveToAState();
	virtual ~CMoveToAState();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void Destroy();
	virtual int  OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void OnEnter();
	virtual void OnExit();
};

