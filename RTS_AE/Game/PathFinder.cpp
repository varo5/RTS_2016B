/**********************************************************************************************//**
 * @file	Game\PathFinder.cpp
 *
 * @brief	Implements the path finder class.
 **************************************************************************************************/

#include "stdafx.h"
#include "PathFinder.h"

aePathFinder::aePathFinder()
{
}

aePathFinder::aePathFinder(aeTiledMap * pMap) 
{
	m_State = WalkStateID::NotLooking;
}

aePathFinder::~aePathFinder()
{
}

int aePathFinder::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;
	return 0;
}

bool aePathFinder::WeightedGraphSupported()
{
	return false;
}

bool aePathFinder::HeuristicsSupported()
{
	return false;
}

int aePathFinder::GetState()
{
	return static_cast<int>(m_State);
}

void aePathFinder::DebugMode(bool State)
{
	m_bDebug = State;
}

void aePathFinder::SetStartPosition(aePoint StartPosition)
{
	m_Start = StartPosition;
}

void aePathFinder::SetEndPosition(aePoint EndPosition)
{
	m_End = EndPosition;
}

int aePathFinder::MakeSearch(aePoint StartPosition, aePoint EndPosition)
{
	SetStartPosition(StartPosition);
	SetEndPosition(EndPosition);
	Reset();
	m_State = WalkStateID::StillLooking;
	return 0;
}

aePoint aePathFinder::GetStartPosition()
{
	return m_Start;
}

aePoint aePathFinder::GetEndPosition()
{
	return m_End;
}
