#pragma once
#include "BaseClass.h"
#include "State.h"
#include <vector>

class aeStateMachineScript;
class aeStateMachine : public aeBaseClass
{
public:
	aeStateMachine();
	virtual ~aeStateMachine();

	virtual void Init(aeStateMachineScript* pScript);
	virtual void AddState(CState* pNewState);
	virtual void SetState(int NewState);
	virtual void OnUpdate(float fDelta, aeBaseClass* pObject);
	virtual void Destroy();	
protected:
	CState* m_pCurrentState;
	aeStateMachineScript* m_pScript;
	std::vector<CState*> m_aPosibleStates;
};

