/**********************************************************************************************//**
 * @file	Game\PathFinder.h
 *
 * @brief	Declares the path finder class.
 **************************************************************************************************/

#pragma once
#include "TiledMap.h"

/**********************************************************************************************//**
 * @class	aePathFinder
 *
 * @brief	A path finder algorithm for the aeTileMap Class.
 **************************************************************************************************/

class aePathFinder : public aeScript
{
	/************************************************************************************************************************/
	/* Constructors declaration																								*/
	/************************************************************************************************************************/
public:
	aePathFinder();
	aePathFinder(aeTiledMap *pMap);
	virtual ~aePathFinder();

	/************************************************************************************************************************/
	/* Functions declaration                                      															*/
	/************************************************************************************************************************/
public:

	/**********************************************************************************************//**
	 * @fn	virtual int aePathFinder::Init(aeBaseClass* pParent);
	 *
	 * @brief	Initializes with the given parent pointer.
	 *
	 * @param [in,out]	pParent	If non-null, the parent.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	virtual int Init(aeBaseClass* pParent);

	/**********************************************************************************************//**
	 * @fn	virtual void aePathFinder::Reset() = 0;
	 *
	 * @brief	Resets this object.
	 **************************************************************************************************/

	virtual void Reset() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual bool aePathFinder::WeightedGraphSupported();
	 *
	 * @brief	Determines if the pathfinder is weighted graph supported.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool WeightedGraphSupported();

	/**********************************************************************************************//**
	 * @fn	virtual bool aePathFinder::HeuristicsSupported();
	 *
	 * @brief	Determines if the pathfinder is heuristics supported.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool HeuristicsSupported();

	/**********************************************************************************************//**
	 * @fn	int aePathFinder::GetState();
	 *
	 * @brief	Gets the state.
	 *
	 * @return	The state.
	 **************************************************************************************************/

	int GetState();

	/**********************************************************************************************//**
	 * @fn	void aePathFinder::DebugMode(bool State);
	 *
	 * @brief	Turns on or off the debug mode.
	 *
	 * @param	State	true to state.
	 **************************************************************************************************/

	void DebugMode(bool State);

	/**********************************************************************************************//**
	 * @fn	void aePathFinder::SetStartPosition(aePoint StartPosition);
	 *
	 * @brief	Sets start position.
	 *
	 * @param	StartPosition	The start position.
	 **************************************************************************************************/

	virtual void SetStartPosition(aePoint StartPosition);

	/**********************************************************************************************//**
	 * @fn	void aePathFinder::SetEndPosition(aePoint EndPosition);
	 *
	 * @brief	Sets end position.
	 *
	 * @param	EndPosition	The end position.
	 **************************************************************************************************/

	void SetEndPosition(aePoint EndPosition);

	/**********************************************************************************************//**
	 * @fn	int aePathFinder::MakeSearch(aePoint StartPosition, aePoint EndPosition);
	 *
	 * @brief	Makes a search.
	 *
	 * @param	StartPosition	The start position.
	 * @param	EndPosition  	The end position.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	int MakeSearch(aePoint StartPosition, aePoint EndPosition);

	/**********************************************************************************************//**
	 * @fn	aePoint aePathFinder::GetStartPosition();
	 *
	 * @brief	Gets start position.
	 *
	 * @return	The start position.
	 **************************************************************************************************/

	aePoint GetStartPosition();

	/**********************************************************************************************//**
	 * @fn	aePoint aePathFinder::GetEndPosition();
	 *
	 * @brief	Gets end position.
	 *
	 * @return	The end position.
	 **************************************************************************************************/

	aePoint GetEndPosition();
	uint8 GetID() {
		return m_ID;
	}

protected:

	/**********************************************************************************************//**
	 * @fn	virtual void aePathFinder::VisitGridNode(int32 x, int32 y) = 0;
	 *
	 * @brief	Marks a node as visited.
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	virtual void VisitGridNode(int32 x, int32 y) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual WalkStateID aePathFinder::GiveAStep();
	 *
	 * @brief	Give a step.
	 *
	 * @return	A WalkStateID.
	 **************************************************************************************************/

	virtual WalkStateID GiveAStep() = 0;

	
	/************************************************************************************************************************/
	/* Class members declaration					                                 										*/
	/************************************************************************************************************************/
protected:		
	aePoint m_Start;	
	aePoint m_End;				
	WalkStateID m_State;
	uint8 m_SearchType;
	bool m_bDebug;
	uint8 m_ID;
};