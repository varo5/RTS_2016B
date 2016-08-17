/**********************************************************************************************//**
 * @file	Game\BreadthFirstSearch.h
 *
 * @brief	Declares the breadth first search path finder class.
 **************************************************************************************************/

#pragma once

class aeBFSPathFinder : public aePathFinder
{
/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aeBFSPathFinder();
	aeBFSPathFinder(aeTiledMap *pMap);
	virtual ~aeBFSPathFinder();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeBFSPathFinder::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::Render(aeRenderer* pRenderer);
	 *
	 * @brief	Renders the given Renderer pointer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer* pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::Reset();
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset();

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::VisitGridNode(int32 x, int32 y);
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual void aeBFSPathFinder::SetFinalNode(int32 x, int32 y);
	 *
	 * @brief	Sets final node.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void SetFinalNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aeBFSPathFinder::GiveAStep();
	 *
	 * @brief	Give a step.
	 *
	 * @return	A WalkStateID.
	 **************************************************************************************************/

	virtual WalkStateID GiveAStep();	

	/************************************************************************************************************************/
	/* Declaración de variables miembro exclusivas de esta clase            												*/
	/************************************************************************************************************************/
private:
	std::queue<aeMapTileNode*> m_open;			//Nuestra lista abierta utilizando un queue ordinario
	aeMapTileNode *m_start, *m_n, *m_end;		//Punteros a los nodos de inicio, uso y final
	aeMapTileNode **m_nodegrid;					//Matriz para almacenamiento de los nodos del mapa
};
