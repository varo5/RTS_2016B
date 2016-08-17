#pragma once
#include <stack>

class aeDFSPathFinder : public aePathFinder
{
/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aeDFSPathFinder();
	aeDFSPathFinder(aeTiledMap *pMap);
	virtual ~aeDFSPathFinder();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeDFSPathFinder::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::Render(aeRenderer* pRenderer);
	 *
	 * @brief	Renders the given Renderer pointer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer* pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::Reset();
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset();

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::VisitGridNode(int32 x, int32 y);
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDFSPathFinder::SetFinalNode(int32 x, int32 y) virtual WalkStateID GiveAStep();
	 *
	 * @brief	Sets final node.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void SetFinalNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aeDFSPathFinder::GiveAStep();
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
	std::stack<aeMapTileNode*> m_open;			//Nuestra lista abierta utilizando un queue ordinario
	aeMapTileNode *m_start, *m_n, *m_end;		//Punteros a los nodos de inicio, uso y final
	aeMapTileNode **m_nodegrid;					//Matriz para almacenamiento de los nodos del mapa
};