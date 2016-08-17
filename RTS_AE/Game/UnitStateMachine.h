#pragma once
#include "StateMachineScript.h"

class CUnitStateMachine : public aeStateMachineScript
{
public:
	CUnitStateMachine();
	~CUnitStateMachine();

	virtual void SetState(int NewState);
};

