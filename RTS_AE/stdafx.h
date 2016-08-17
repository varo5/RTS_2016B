// stdafx.h : include file for standard system include files, or project specific include files
// that are used frequently, but are changed infrequently. 
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

// TODO: reference additional headers your program requires here
#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <list>
#include <functional>

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

// Access to the external library
#include "aeCoreStd.h"
using namespace aeCore;

#include "Awesomium/WebManager.h"

#include "Game\EnumDeclarations.h"

///Game files
#include "Game\AddOn.h"
#include "Game\BaseClass.h"
#include "Game\GameObject.h"
#include "Game\Transform.h"

///Presets
#include "Game\Presets.h"
#include "Game\UnitType.h"
#include "Game\TileType.h"

#include "Game\Animation.h"
#include "Game\World.h"


///State Machines files
#include "Game\AnimationStateMachine.h"
#include "Game\UnitStateMachine.h"
#include "Game\StateMachine.h"
#include "Game\StateMachineScript.h"

///Scripts
#include "Game/Scripts.h"
#include "Game/SpriteRenderer.h"
#include "Game/AnimationRenderer.h"
#include "Game/ButtonScript.h"
#include "Game/UserScript.h"

///State files
#include "Game\State.h"
#include "Game\UnitState.h"
#include "Game\AnimationState.h"
#include "Game\AttackAState.h"
#include "Game\DeathAState.h"
#include "Game\IdleAState.h"
#include "Game\MoveToAState.h"
#include "Game\Attack.h"
#include "Game\Death.h"
#include "Game\Idle.h"
#include "Game\Move_To.h"

//Map tile nodes
#include "Game/MapTileNode.h"
#include "Game/TiledMap.h"

//PathFinder
#include "Game/PathFinder.h"
#include "Game/BreadthFirstSearch.h"
#include "Game/DepthFirstSearch.h"
#include "Game/BestFirstSearch.h"
#include "Game/Dijkstra.h"
#include "Game/AStar.h"
#include "Game/InfluenceCalculator.h"

//GUI
#include "Game/GUIObject.h"
#include "Game/GUI.h"

#include "Game/App.h"


/**********************************************************************************************//**
// End of stdafx.h
 **************************************************************************************************/

