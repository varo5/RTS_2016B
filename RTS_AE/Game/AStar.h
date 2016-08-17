#pragma once

class aeAStarPathFinder : public aePathFinder
{
public:
	struct NodeDist
	{
		aeAStarMapTileNode* Node;
		float Dist;
	};
	struct TileCompare
	{
		bool operator()(const NodeDist* t1, const NodeDist* t2) const
		{
			return t1->Dist > t2->Dist;
		}
	};

	/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aeAStarPathFinder();
	aeAStarPathFinder(aeTiledMap *pMap);
	virtual ~aeAStarPathFinder();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aeAStarPathFinder::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::Destroy();
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy();

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::Update(float fDelta);
	 *
	 * @brief	Updates the given fDelta.
	 *
	 * @param	fDelta	The delta.
	 **************************************************************************************************/

	virtual void Update(float fDelta);

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::Render(aeRenderer* pRenderer);
	 *
	 * @brief	Renders the given Renderer pointer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 **************************************************************************************************/

	virtual void Render(aeRenderer* pRenderer);

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::Reset();
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset();

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::SetFinalNode(int32 x, int32 y);
	 *
	 * @brief	Sets final node.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void SetFinalNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual void aeAStarPathFinder::VisitGridNode(int32 x, int32 y);
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y);

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aeAStarPathFinder::GiveAStep();
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
	std::priority_queue<NodeDist*, std::vector<NodeDist*>, TileCompare> m_open;			//Nuestra lista abierta utilizando un queue ordinario
	aeAStarMapTileNode *m_start, *m_n, *m_end;			//Punteros a los nodos de inicio, uso y final
	aeAStarMapTileNode **m_nodegrid;					//Matriz para almacenamiento de los nodos del mapa
	float m_fDist;
};