/**********************************************************************************************//**
 * @file	Game\BaseClass.h
 *
 * @brief	Declares the base class for the hereditary tree.
 **************************************************************************************************/

#pragma once
#include <vector>
/**********************************************************************************************//**
 * @enum	ClassIds
 *
 * @brief	Values that represent the class identifiers.
 **************************************************************************************************/

enum struct ClassId
{
	BaseClass =	0,		/**< Basic class ID */
	Preset,				/**< Preset ID */
	GameObject,			/**< Game Object ID */
	AddOn,				/**< Add On ID */
	StateMachine,		/**< State machine ID */
	StateMachineScript,	/**< State machine script ID */
	State,				/**< State ID */
	GUI,				/**< GUI ID */
	GUIObject,			/**< GUI Object ID */
};

/**********************************************************************************************//**
 * @class	aeBaseClass
 *
 * @brief	A base class.
 **************************************************************************************************/

class aeBaseClass
{
public:
	/************************************************************************************************************************/
	/* Constructors declaration                                            													*/
	/************************************************************************************************************************/
	///Default constructor
	aeBaseClass();
	///Destructor
	virtual ~aeBaseClass();

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual void aeBaseClass::Destroy() = 0;
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy() = 0;

	/**********************************************************************************************//**
	 * @fn	ClassId aeBaseClass::GetClassID();
	 *
	 * @brief	Gets the identifier.
	 *
	 * @return	The identifier.
	 **************************************************************************************************/

	ClassId GetClassID();

	/**********************************************************************************************//**
	 * @fn	inline void aeBaseClass::SetParent(aeBaseClass* pNewParent)
	 *
	 * @brief	Sets as parent.
	 *
	 * @param [in,out]	pNewParent	If non-null, the new parent.
	 **************************************************************************************************/

	void SetParent(aeBaseClass* pNewParent);

	/**********************************************************************************************//**
	 * @fn	inline aeBaseClass* aeBaseClass::GetParent()
	 *
	 * @brief	Gets the parent of this item.
	 *
	 * @return	null if it fails, else the parent.
	 **************************************************************************************************/

	aeBaseClass* GetParent();

	/************************************************************************************************************************/
	/* Variable declaration									                												*/
	/************************************************************************************************************************/
protected:
	/** @brief	Identifier for the class. */
	ClassId m_nClassID;
	/** @brief	The parent. */
	aeBaseClass* m_pParent;
};