#pragma once

/**********************************************************************************************//**
 * @class	aeGUIObject
 *
 * @brief	A graphical user interface object.
 **************************************************************************************************/

class aeGUIObject : public aeBaseClass
{
public:
	aeGUIObject();
	virtual ~aeGUIObject();

public:
	aeTransform Transform;

	aeString Name;
	aeString Tag;

	aeAddOns AddOns;

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeGUIObject::Init();
	 *
	 * @brief	Gets the init.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init();

	/**********************************************************************************************//**
	 * @fn	virtual void aeGUIObject::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeGUIObject::Render(aeRenderer * pRenderer);
	 *
	 * @brief	Renders the given pRenderer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer * pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeGUIObject::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();
};

