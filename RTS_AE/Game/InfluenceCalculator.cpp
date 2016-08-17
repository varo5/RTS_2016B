#include "stdafx.h"
#include "InfluenceCalculator.h"
aeInfluenceCalculator::aeInfluenceCalculator()
{
	m_n = NULL;
	m_nodegrid = NULL;
	m_ID = 1;
}

aeInfluenceCalculator::aeInfluenceCalculator(aeTiledMap * pMap) : aePathFinder(pMap)
{
	m_n = NULL;
	m_nodegrid = NULL;
	m_ID = 1;
	Init(pMap);
}

aeInfluenceCalculator::~aeInfluenceCalculator()
{
	Destroy();
}

int aeInfluenceCalculator::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;
	if (m_nodegrid != NULL)
	{
		Destroy();
	}

	m_nodegrid = new aeInfluenceTileNode*[((aeTiledMap*)m_pParent)->GetMapSize()];
	for (int32 i = 0; i<((aeTiledMap*)m_pParent)->GetMapSize(); i++)
	{
		m_nodegrid[i] = new aeInfluenceTileNode[((aeTiledMap*)m_pParent)->GetMapSize()];
		for (int32 j = 0; j<((aeTiledMap*)m_pParent)->GetMapSize(); j++)
		{
			m_nodegrid[i][j].SetVisited(false);
			m_nodegrid[i][j].m_x = i;
			m_nodegrid[i][j].m_y = j;
			m_nodegrid[i][j].m_fInfluence = ((aeTiledMap*)m_pParent)->GetInfluence(i,j);
		}
	}
	return 0;
}

void aeInfluenceCalculator::Destroy()
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

void aeInfluenceCalculator::Update(float fDelta)
{
	
}

void aeInfluenceCalculator::Render(aeRenderer * pRenderer)
{
	int Size = ((aeTiledMap*)m_pParent)->GetMapSize();
	for (size_t i = 0; i < Size; ++i)
		for (size_t j = 0; j < Size; ++j)
		{
			GiveAStep(i, j);
		}
}

void aeInfluenceCalculator::Reset()
{
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
}

void aeInfluenceCalculator::SetInfluencePoints(aeInfluencePoint * Points, int size)
{
	for (size_t i = 0; i < size; ++i)
	{
		
		SetStartPosition(aePoint{ Points[i].x,Points[i].y });
		m_nodegrid[Points[i].x][Points[i].y].m_fInfluence = (Points[i].Influence);
	}
	Reset();
	int Size = ((aeTiledMap*)m_pParent)->GetMapSize();
	for (size_t i = 0; i < Size; ++i)
		for (size_t j = 0; j < Size; ++j)
		{
			GiveAStep(i, j);
		}
}

void aeInfluenceCalculator::VisitGridNode(int32 x, int32 y)
{
	float Inf = m_nodegrid[x][y].m_fInfluence * expf(-Dist(x, y)*m_fDecay);
	m_fMaxInf = Max(Inf, m_fMaxInf);
}

void aeInfluenceCalculator::SetFinalNode(int32 x, int32 y)
{
}

WalkStateID aeInfluenceCalculator::GiveAStep(int32 x, int32 y)
{
	_x = x;
	_y = y;
	m_fMaxInf = 0;
	m_n = &m_nodegrid[x][y];	//Obtenemos el nodo actual para chequeos

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
	m_n->m_fInfluence = Lerp(m_n->m_fInfluence, m_fMaxInf, m_fMomentum);
	if (abs(m_n->m_fInfluence) > 0.1f)
		((aeTiledMap*)m_pParent)->SetInfluence(m_n->m_x, m_n->m_y, m_n->m_fInfluence);
	else
		((aeTiledMap*)m_pParent)->SetInfluence(m_n->m_x, m_n->m_y, 0);

	return WalkStateID::StillLooking;
}

WalkStateID aeInfluenceCalculator::GiveAStep()
{
	return WalkStateID();
}

float aeInfluenceCalculator::Dist(int x, int y)
{
	return aeVector2{(float)_x-x,(float)_y-y}.Magnitude();
}
