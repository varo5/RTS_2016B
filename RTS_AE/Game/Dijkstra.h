#pragma once
#include <set>

class aeDijkstraPathFinder : public aePathFinder
{
public:
	/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aeDijkstraPathFinder();
	aeDijkstraPathFinder(aeTiledMap *pMap);
	virtual ~aeDijkstraPathFinder();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeDijkstraPathFinder::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDijkstraPathFinder::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual void aeDijkstraPathFinder::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDijkstraPathFinder::Render(aeRenderer* pRenderer);
	 *
	 * @brief	Renders the given Renderer pointer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer* pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeDijkstraPathFinder::Reset();
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset();

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aeDijkstraPathFinder::VisitGridNode(int32 x, int32 y);
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aeDijkstraPathFinder::GiveAStep();
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
	std::set<std::pair<int32, aeMapTileNode*> > m_open;			//Nuestra lista abierta utilizando un queue ordinario
	aeMapTileNode *m_start, *m_n, *m_end;		//Punteros a los nodos de inicio, uso y final
	aeMapTileNode **m_nodegrid;					//Matriz para almacenamiento de los nodos del mapa
	int32 m_nDist;
};