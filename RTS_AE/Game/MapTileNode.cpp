/**********************************************************************************************//**
 * @file	Game\MapTileNode.cpp
 *
 * @brief	Implements the map tile node class.
 **************************************************************************************************/

#include "stdafx.h"
#include "MapTileNode.h"

aeMapTileNode::aeMapTileNode(void)
{//Constructor standard
 //Inicializamos las variables miembro de la clase
	m_cost = m_x = m_y = 0;
	m_parent = NULL;
	m_visited = false;
}
aeMapTileNode::aeMapTileNode(const int32 x, const int32 y, aeMapTileNode *parent, const bool visited, const int32 cost)
{//Constructor con parámetros establecidos
 //Inicializa los datos de la clase con los datos de los parámetros
	m_x = x; m_y = y; m_parent = parent;
	m_visited = visited;
	m_cost = cost;
}

aeMapTileNode::aeMapTileNode(const aeMapTileNode &copy)
{
	m_x = copy.m_x;
	m_y = copy.m_y;
	m_cost = copy.m_cost;
	m_parent = copy.m_parent;
	m_visited = copy.m_visited;
}

aeMapTileNode::~aeMapTileNode()
{
	m_parent = NULL;
}

aeMapTileNode & aeMapTileNode::operator=(const aeMapTileNode & rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_parent = rhs.m_parent;
	m_visited = rhs.m_visited;
	m_cost = rhs.m_cost;

	return *this;
}

bool aeMapTileNode::operator==(const aeMapTileNode & rhs)
{
	return this->Equals(rhs);
}

bool aeMapTileNode::operator<(const aeMapTileNode & rhs)
{
	return m_cost < rhs.m_cost;
}

bool aeMapTileNode::operator>(const aeMapTileNode & rhs)
{
	return m_cost > rhs.m_cost;
}

void aeMapTileNode::SetParent(aeMapTileNode* parent)
{//Establece el parent de este nodo
	m_parent = parent;
}
void aeMapTileNode::SetVisited(const bool visited)
{//Establece el estado de visitado de este nodo
	m_visited = visited;
}
bool aeMapTileNode::GetVisited() const
{//Regresa el valor de visitado de este nodo
	return m_visited;
}

void aeMapTileNode::SetCost(const int32 cost)
{
	m_cost = cost;
}

int32 aeMapTileNode::GetCost() const
{
	return m_cost;
}

bool aeMapTileNode::Equals(const aeMapTileNode &rhs) const
{//Compara las posiciones entre este y otro nodo e indica si son iguales
	return ((m_x == rhs.m_x) && (m_y == rhs.m_y));
}

aeAStarMapTileNode::aeAStarMapTileNode() : aeMapTileNode()
{//El constructor standard, llama al constructor de la clase padre e inicializa sus propias variables
	m_g = m_f = m_h = 0;
}

aeAStarMapTileNode::aeAStarMapTileNode(const aeAStarMapTileNode & copy)
{
	m_x = copy.m_x;
	m_y = copy.m_y;
	m_parent = copy.m_parent;
	m_visited = copy.m_visited;
	m_cost = copy.m_cost;
	m_g = copy.m_g;
	m_h = copy.m_h;
	m_f = copy.m_f;
}


aeAStarMapTileNode::~aeAStarMapTileNode()
{//Este destructor hace un override al destructor de la clase padre, por lo que tenemos que reimplementar
	m_parent = NULL;	//Limpiamos la referencia al parent
}

aeAStarMapTileNode & aeAStarMapTileNode::operator=(const aeAStarMapTileNode & rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_parent = rhs.m_parent;
	m_visited = rhs.m_visited;
	m_cost = rhs.m_cost;
	m_g = rhs.m_g;
	m_h = rhs.m_h;
	m_f = rhs.m_f;

	return *this;
}

void aeAStarMapTileNode::SetCost(const int32 cost)
{
	m_f = cost;
}

int32 aeAStarMapTileNode::GetCost() const
{
	return m_f;
}

aeInfluenceTileNode::aeInfluenceTileNode() : aeMapTileNode()
{//El constructor standard, llama al constructor de la clase padre e inicializa sus propias variables
	m_fInfluence = 0;
}

aeInfluenceTileNode::aeInfluenceTileNode(const aeInfluenceTileNode & copy)
{
	m_x = copy.m_x;
	m_y = copy.m_y;
	m_parent = copy.m_parent;
	m_visited = copy.m_visited;
	m_cost = copy.m_cost;
	m_fInfluence = copy.m_fInfluence;
}


aeInfluenceTileNode::~aeInfluenceTileNode()
{//Este destructor hace un override al destructor de la clase padre, por lo que tenemos que reimplementar
	m_parent = NULL;	//Limpiamos la referencia al parent
}

aeInfluenceTileNode & aeInfluenceTileNode::operator=(const aeInfluenceTileNode & rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_parent = rhs.m_parent;
	m_visited = rhs.m_visited;
	m_cost = rhs.m_cost;
	m_fInfluence = rhs.m_fInfluence;

	return *this;
}