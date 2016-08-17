#pragma once
#include "StateMachineScript.h"

class CAnimationStateMachine : public aeStateMachineScript
{
public:
	CAnimationStateMachine();
	~CAnimationStateMachine();

	virtual void SetState(int NewState);
	
	void* pPassAlong;
};

