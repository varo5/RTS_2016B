/**********************************************************************************************//**
 * @file	Game\MapTileNode.h
 *
 * @brief	Declares the map tile node class.
 **************************************************************************************************/

#pragma once

 /************************************************************************************************************************/
 /* Constants declaration						                    													*/
 /************************************************************************************************************************/

/**********************************************************************************************//**
 * @def	TILENODE_BLOCKED
 *
 * @brief	A macro that defines if a tile is blocked.
 **************************************************************************************************/

#define TILENODE_BLOCKED 3000	

class aeMapTileNode
{
	/************************************************************************************************************************/
	/* Constructors declaration														                                      	*/
	/************************************************************************************************************************/
public:
	aeMapTileNode();
	aeMapTileNode(const int32 x, const int32 y, aeMapTileNode *parent, const bool visited, const int32 cost);
	aeMapTileNode(const aeMapTileNode &copy);	
	virtual ~aeMapTileNode();

	/************************************************************************************************************************/
	/* Operands declaration								                           											*/
	/************************************************************************************************************************/
public:
	virtual aeMapTileNode &operator=(const aeMapTileNode &rhs);		
	virtual bool operator==(const aeMapTileNode &rhs);				
	virtual bool operator<(const aeMapTileNode &rhs);				
	virtual bool operator>(const aeMapTileNode &rhs);				

	/************************************************************************************************************************/
	/* Declaración de funciones de acceso                                   												*/
	/************************************************************************************************************************/
	void SetParent(aeMapTileNode* parent);
	void SetVisited(const bool visited);
	bool GetVisited() const;

	virtual void SetCost(const int32 cost);	
	virtual int32 GetCost() const;			

	/************************************************************************************************************************/
	/* Funciones de ayuda                                                   												*/
	/************************************************************************************************************************/
	bool Equals(const aeMapTileNode &rhs) const;

	/************************************************************************************************************************/
	/* Declaración de variables miembro de la clase                         												*/
	/************************************************************************************************************************/
public:
	int32 m_x;						//Indica la posición en el eje X del nodo
	int32 m_y;						//Indica la posición en el eje Y del nodo
	int32 m_cost;					//Indica el costo para moverse a este nodo
	bool m_visited;					//Bandera que indica si este nodo fue o no visitado
	aeMapTileNode *m_parent;
};

/************************************************************************************************************************/
/* Declaración de la clase aeAStarMapTileNode, derivada de aeMapTileNode (extiende el nodo para su uso en A*)			*/
/************************************************************************************************************************/
class aeAStarMapTileNode : public aeMapTileNode
{
	/************************************************************************************************************************/
	/* Declaración de contructores e implementación del destructor 															*/
	/************************************************************************************************************************/
public:
	aeAStarMapTileNode();
	aeAStarMapTileNode(const aeAStarMapTileNode &copy);
	virtual ~aeAStarMapTileNode();

	/************************************************************************************************************************/
	/* Definición de operadores                                             												*/
	/************************************************************************************************************************/
	virtual aeAStarMapTileNode &operator=(const aeAStarMapTileNode &rhs);

	/************************************************************************************************************************/
	/* Funciones de acceso a datos                                          												*/
	/************************************************************************************************************************/
	virtual void SetCost(const int32 cost);		//Override de la función para establecer costo de un nodo utilizado para AStar
	virtual int32 GetCost() const;				//Override de la función para obtener costo de un nodo utilizado para AStar

	/************************************************************************************************************************/
	/* Declaración de variables miembro de la clase                         												*/
	/************************************************************************************************************************/
public:
	int32 m_f;	//Fitness
	int32 m_g;	//Goal
	int32 m_h;	//Heuristic
};

/************************************************************************************************************************/
/* Declaración de la clase aeAStarMapTileNode, derivada de aeMapTileNode												*/
/*(extiende el nodo para su uso en el mapa de influencia)																	*/
/************************************************************************************************************************/
class aeInfluenceTileNode : public aeMapTileNode
{
	/************************************************************************************************************************/
	/* Declaración de contructores e implementación del destructor 															*/
	/************************************************************************************************************************/
public:
	aeInfluenceTileNode();
	aeInfluenceTileNode(const aeInfluenceTileNode &copy);
	virtual ~aeInfluenceTileNode();

	/************************************************************************************************************************/
	/* Definición de operadores                                             												*/
	/************************************************************************************************************************/
	virtual aeInfluenceTileNode &operator=(const aeInfluenceTileNode &rhs);

	/************************************************************************************************************************/
	/* Declaración de variables miembro de la clase                         												*/
	/************************************************************************************************************************/
public:
	float m_fInfluence;
};