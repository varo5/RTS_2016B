#pragma once
#include "BaseClass.h"
#include "StateMachineScript.h"

class CState : public aeBaseClass
{
	/************************************************************************************************************************/
	/* Constructors declaration                                            													*/
	/************************************************************************************************************************/
public:
	CState();
	virtual ~CState();

	/************************************************************************************************************************/
	/* Variable declaration									                												*/
	/************************************************************************************************************************/
protected:
	int m_nStateID;

	/************************************************************************************************************************/
	/* Functions declaration									                												*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual void CState::Init(aeStateMachineScript* pScript) = 0;
	 *
	 * @brief	Initializes the with the given state machine script.
	 *
	 * @param [in,out]	pScript	If non-null, the script.
	 **************************************************************************************************/

	virtual void Init(aeStateMachineScript* pScript) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void CState::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual int CState::OnUpdate(float fDelta, aeBaseClass* pObject) = 0;
	 *
	 * @brief	Executes the update action.
	 *
	 * @param	fDelta		   	The delta.
	 * @param [in,out]	pObject	If non-null, the object.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int  OnUpdate(float fDelta, aeBaseClass* pObject) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void CState::OnEnter() = 0;
	 *
	 * @brief	Executes the enter action.
	 **************************************************************************************************/

	virtual void OnEnter() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void CState::OnExit() = 0;
	 *
	 * @brief	Executes the exit action.
	 **************************************************************************************************/

	virtual void OnExit() = 0;

	/**********************************************************************************************//**
	 * @fn	inline bool CState::operator==(int StateID)
	 *
	 * @brief	Equality operator.
	 *
	 * @param	StateID	Identifier for the state.
	 *
	 * @return	true if the parameters are considered equivalent.
	 **************************************************************************************************/

	inline bool operator==(int StateID)
	{
		return this->m_nStateID == StateID;
	};
};

