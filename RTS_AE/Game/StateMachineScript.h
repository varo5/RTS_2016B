#pragma once
#include "BaseClass.h"
#include "StateMachine.h"
#include "State.h"

class CState;

class aeStateMachineScript : public aeBaseClass
{
public:
	aeStateMachineScript()
	{
		m_nClassID = ClassId::StateMachineScript;
	};

	virtual ~aeStateMachineScript() {};

	void Destroy() {};
	virtual void SetState(int NewState) = 0;

	inline void SetStateList(std::vector<CState*>* pStateList)
	{
		m_pStateList = pStateList;
	}
	inline void SetStateReference(CState** CurrentStateReference)
	{
		m_ppCurrentState = CurrentStateReference;
	}
protected:
	std::vector<CState*>* m_pStateList;
	CState** m_ppCurrentState;
};
