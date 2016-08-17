#include "stdafx.h"
#include "AStar.h"

aeAStarPathFinder::aeAStarPathFinder()
{
	m_n = NULL;
	m_nodegrid = NULL;
}

aeAStarPathFinder::aeAStarPathFinder(aeTiledMap * pMap) : aePathFinder(pMap)
{
	m_n = NULL;
	m_nodegrid = NULL;
	Init(pMap);
}

aeAStarPathFinder::~aeAStarPathFinder()
{
	Destroy();
}

int aeAStarPathFinder::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;
	if (m_nodegrid != NULL)
	{
		Destroy();
	}

	m_nodegrid = new aeAStarMapTileNode*[((aeTiledMap*)m_pParent)->GetMapSize()];
	for (int32 i = 0; i < ((aeTiledMap*)m_pParent)->GetMapSize(); i++)
	{
		m_nodegrid[i] = new aeAStarMapTileNode[((aeTiledMap*)m_pParent)->GetMapSize()];
		for (int32 j = 0; j < ((aeTiledMap*)m_pParent)->GetMapSize(); j++)
		{
			m_nodegrid[i][j].SetVisited(false);
			m_nodegrid[i][j].m_x = i;
			m_nodegrid[i][j].m_y = j;
			m_nodegrid[i][j].m_cost = ((aeTiledMap*)m_pParent)->GetCost(i, j);
			m_nodegrid[i][j].m_f = 3000;
		}
	}
	return 0;
}

void aeAStarPathFinder::Destroy()
{
	if (m_nodegrid != NULL)
	{
		for (int32 i = 0; i < ((aeTiledMap*)m_pParent)->GetMapSize(); i++)
		{
			AE_DELETE_ARRAY(m_nodegrid[i]);
		}
		AE_DELETE_ARRAY(m_nodegrid);
	}

	m_nodegrid = NULL;
	m_n = NULL;
}

void aeAStarPathFinder::Update(float fDelta)
{
	if (!m_bDebug)
	{
		while (m_State == WalkStateID::StillLooking)
		{
			m_State = GiveAStep();
		}
	}
}

void aeAStarPathFinder::Render(aeRenderer * pRenderer)
{
	if (m_bDebug)
	{
		if (m_State == WalkStateID::StillLooking)
		{
			m_State = GiveAStep();
		}
	}
}

void aeAStarPathFinder::Reset()
{
	m_State = WalkStateID::NotLooking;

	while (m_open.size() > 0)
	{
		m_open.pop();
	}

	//Establecemos que no hay un nodo actual en chequeo
	m_n = NULL;

	//Para este punto los nodos ya están creados, solo limpiamos la bandera de visitado a false en todos
	for (int32 i = 0; i < ((aeTiledMap*)m_pParent)->GetMapSize(); i++)
	{
		for (int j = 0; j < ((aeTiledMap*)m_pParent)->GetMapSize(); j++)
		{
			((aeTiledMap*)m_pParent)->SetLayer4(i, j, -1);
			m_nodegrid[i][j].SetVisited(false);
		}
	}

	//Obtenemos el punto de inicio, lo marcamos como visitado y lo establecemos como el nodo inicial
	aePoint Point = GetStartPosition();
	m_start = &m_nodegrid[Point.x][Point.y];
	m_start->SetVisited(true);

	//Obtenemos el punto final, obtenemos el nodo y lo marcamos como el nodo final
	Point = GetEndPosition();
	m_end = &m_nodegrid[Point.x][Point.y];

	//Agregamos el nodo inicial a la lista abierta
	m_start->m_f = 0;
	aeVector2 TempVector = aeVector2{ (float)m_end->m_x - m_start->m_x , (float)m_end->m_y - m_start->m_y };
	m_open.push(new NodeDist{ m_start, TempVector.Magnitude()});
}

void aeAStarPathFinder::VisitGridNode(int32 x, int32 y)
{
	if (((aeTiledMap*)m_pParent)->GetCost(x, y) >= TILENODE_BLOCKED || m_nodegrid[x][y].GetVisited())
	{//Si este nodo está bloqueado o ya fue visitado
		return;	//Regresamos sin hacer nada
	}
	
	//Marcamos este nodo como visitable agregándolo a la lista abierta
	aeVector2 TempVector = aeVector2{ (float)m_end->m_x - m_n->m_x , (float)m_end->m_y - m_n->m_y };
	m_open.push(new NodeDist{ &m_nodegrid[x][y],m_nodegrid[x][y].m_cost*TempVector.Magnitude() });

	((aeTiledMap*)m_pParent)->SetLayer4(x, y, ((aeTiledMap*)m_pParent)->PositionOfOpenMask);

	//Tambien marcamos que el nodo en chequeo actual es el padre de este nodo
	m_nodegrid[x][y].m_parent = m_n;
}

void aeAStarPathFinder::SetFinalNode(int32 x, int32 y)
{
	m_end = &m_nodegrid[x][y];
}

WalkStateID aeAStarPathFinder::GiveAStep()
{
	if (m_open.size() > 0)
	{//Hay objetos, por lo que podemos seguir calculando una ruta
		NodeDist Temp = *m_open.top();
		m_n = Temp.Node;	//Obtenemos el nodo actual para chequeos
		m_open.pop();							//Sacamos este objeto de la lista abierta
		m_n->SetVisited(true);					//Marcamos este nodo como visitado
		((aeTiledMap*)m_pParent)->SetLayer4(m_n->m_x, m_n->m_y, ((aeTiledMap*)m_pParent)->PositionOfVisitedMask);

		//Revisamos si el nodo está en la posición del objetivo
		if (m_n->Equals(*m_end))
		{//Este es el objetivo
			return WalkStateID::GoalReached;	//Indicamos que hemos llegado a la ruta pedida
		}

		//Creamos variables temporales para almacenar la dirección de chequeo
		int32 x, y;

		//Agregamos todos los nodos adyacentes a este

		//Agregamos el nodo ESTE
		x = m_n->m_x + 1;
		y = m_n->m_y;
		if (m_n->m_x < (((aeTiledMap*)m_pParent)->GetMapSize() - 1))
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo SUD-ESTE
		x = m_n->m_x + 1;
		y = m_n->m_y + 1;
		if (m_n->m_x < (((aeTiledMap*)m_pParent)->GetMapSize() - 1) && m_n->m_y < (((aeTiledMap*)m_pParent)->GetMapSize() - 1))
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo SUR
		x = m_n->m_x;
		y = m_n->m_y + 1;
		if (m_n->m_y < (((aeTiledMap*)m_pParent)->GetMapSize() - 1))
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo SUD-OESTE
		x = m_n->m_x - 1;
		y = m_n->m_y + 1;
		if (m_n->m_y < (((aeTiledMap*)m_pParent)->GetMapSize() - 1) && m_n->m_x > 0)
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo OUSTE
		x = m_n->m_x - 1;
		y = m_n->m_y;
		if (m_n->m_x > 0)
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo NOR-OESTE
		x = m_n->m_x - 1;
		y = m_n->m_y - 1;
		if (m_n->m_x > 0 && m_n->m_y > 0)
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agregamos el nodo NORTE
		x = m_n->m_x;
		y = m_n->m_y - 1;
		if (m_n->m_y > 0)
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		//Agragamos el nodo NOR-ESTE
		x = m_n->m_x + 1;
		y = m_n->m_y - 1;
		if (m_n->m_y > 0 && m_n->m_x < (((aeTiledMap*)m_pParent)->GetMapSize() - 1))
		{//Si no nos hemos salido del rango del mapa
			VisitGridNode(x, y);	//Visitamos el nodo
		}

		return WalkStateID::StillLooking;	//Indicamos que aún estamos buscando el objetivo
	}

	return WalkStateID::UnableToReachGoal;
}