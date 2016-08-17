#pragma once

/**********************************************************************************************//**
 * @enum	UnitStates
 *
 * @brief	Values that represent unit states.
 **************************************************************************************************/

enum struct UnitStates
{
	IDLE = 0,		/**< Sprite Renderer script ID */
	DEATH = 1,
	MOVE_TO = 2,
	ATTACK = 3
};

/**********************************************************************************************//**
 * @enum	AnimationStates
 *
 * @brief	Values that represent animation states.
 **************************************************************************************************/

enum struct AnimationStates
{
	IDLE = 0,
	DEATH = 1,
	MOVE_TO = 2,
	ATTACK = 3
};

/**********************************************************************************************//**
 * @enum	Directions
 *
 * @brief	Values that represent directions.
 **************************************************************************************************/

enum struct Directions
{
	N = 0,
	NW = 1,
	S = 2,
	SW = 3,
	W = 4
};

/**********************************************************************************************//**
 * @enum	UserScriptsID
 *
 * @brief	Values that represent user scripts identifiers.
 **************************************************************************************************/

enum struct UserScriptsID
{
	Unit = 0,

};

/**********************************************************************************************//**
 * @enum	TimersID
 *
 * @brief	Values that represent timers identifiers.
 **************************************************************************************************/

enum struct TimersID
{
	Update = 0,
	Render
};

/**********************************************************************************************//**
 * @enum	PresetsID
 *
 * @brief	Values that represent presets identifiers.
 **************************************************************************************************/

enum struct PresetsID
{
	UnitType = 0,
	TileType,
	MapPreset
};

/**********************************************************************************************//**
 * @enum	WalkStateID
 *
 * @brief	Values that represent walk state identifiers.
 **************************************************************************************************/

enum struct WalkStateID
{
	StillLooking = 0,
	GoalReached,
	UnableToReachGoal,
	NotLooking
};