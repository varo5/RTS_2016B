#pragma once

struct aeInfluencePoint
{
	float Influence;
	int32 x, y;
};

class aeInfluenceCalculator : public aePathFinder
{
/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aeInfluenceCalculator();
	aeInfluenceCalculator(aeTiledMap *pMap);
	virtual ~aeInfluenceCalculator();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeInfluenceCalculator::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::Render(aeRenderer* pRenderer);
	 *
	 * @brief	Renders the given Renderer pointer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer* pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::Reset();
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset();

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::SetInfluencePoints(aeInfluencePoint* Points, int size);
	 *
	 * @brief	Sets influence points.
	 *
	 * @param [in,out]	Points	If non-null, the points.
	 * @param	size		  	The size.
	 **************************************************************************************************/

	virtual void SetInfluencePoints(aeInfluencePoint* Points, int size);

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::VisitGridNode(int32 x, int32 y);
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual void aeInfluenceCalculator::SetFinalNode(int32 x, int32 y);
	 *
	 * @brief	Sets final node.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void SetFinalNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aeInfluenceCalculator::GiveAStep();
	 *
	 * @brief	Give a step.
	 *
	 * @return	A WalkStateID.
	 **************************************************************************************************/

	virtual WalkStateID GiveAStep(int32 x, int32 y);

	virtual WalkStateID GiveAStep();

	float Dist(int x, int y);

	/************************************************************************************************************************/
	/* Declaración de variables miembro exclusivas de esta clase            												*/
	/************************************************************************************************************************/
public:
	float m_fMomentum;
	float m_fDecay;
	float m_fMaxInf;
	float m_fMinInf;
	float m_Inf;
private:
	int _x, _y;
	aeInfluenceTileNode *m_n;		//Punteros a los nodos de inicio, uso y final
	aeInfluenceTileNode **m_nodegrid;					//Matriz para almacenamiento de los nodos del mapa
};