#pragma once
#include <queue>
#include <vector>
#include "../BasicClasses.h"
#include "dll_definition.h"

namespace aeCore
{
	/**********************************************************************************************//**
	 * @enum	EventTypes
	 *
	 * @brief	Values that represent event types.
	 **************************************************************************************************/

	enum struct LIBRARY_EXPORT EventTypes
	{
		Event = 0,
		KeyboardEvent,
		MouseClic,
		MouseMove,
		ResizeEvent,
		MoveEvent,
		UserEvent,
		QuitEvent
	};

	/**********************************************************************************************//**
	 * @enum	EventPriority
	 *
	 * @brief	Values that represent event priorities.
	 **************************************************************************************************/

	enum struct LIBRARY_EXPORT EventPriority
	{
		High = 0,
		Medium,
		Low
	};

	/**********************************************************************************************//**
	 * @struct	aeEvent
	 *
	 * @brief	An event message.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeEvent
	{
		uint8 Type;
		uint8 Priority;
	};

	/**********************************************************************************************//**
	 * @struct	aeKeyboardEvent
	 *
	 * @brief	A Keyboard message.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeKeyboardEvent : aeEvent
	{
		uint8 Key;
		uint8 State;
	};

	/**********************************************************************************************//**
	 * @struct	aeMouseMoveEvent
	 *
	 * @brief	A .
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMouseMoveEvent : aeEvent
	{
		uint16 x, y;
	};

	/**********************************************************************************************//**
	 * @struct	aeMouseButtonEvent
	 *
	 * @brief	A mouse button event.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMouseButtonEvent : aeMouseMoveEvent
	{
		uint8 Button;
		uint8 State;
	};

	/**********************************************************************************************//**
	 * @struct	aeResizeEvent
	 *
	 * @brief	A resize event.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeResizeEvent : aeEvent
	{
		uint16 w, h;
	};

	/**********************************************************************************************//**
	 * @struct	aeMoveEvent
	 *
	 * @brief	An ae move event.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMoveEvent : aeEvent
	{
		uint16 x, y;
	};

	/**********************************************************************************************//**
	 * @struct	aeUserEvent
	 *
	 * @brief	A user event.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeUserEvent : aeEvent
	{
		uint8 Code;
		void *Data1;
		void *Data2;
	};

	/**********************************************************************************************//**
	 * @struct	aeQuitEvent
	 *
	 * @brief	A quit event.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeQuitEvent : aeEvent
	{
	};

	/**********************************************************************************************//**
	 * @struct	aeEventsHandler
	 *
	 * @brief  This class stores all the events in a vector, and stores temporal events a queue for
	 * 		    in-n-out communication.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeEventsHandler
	{
		aeEventsHandler();
		~aeEventsHandler();

		struct EventCompare
		{
			bool operator()(const aeEvent* t1, const aeEvent* t2) const
			{
				return t1->Priority < t2->Priority;
			}
		};

		std::priority_queue<aeEvent*, std::vector<aeEvent*>, EventCompare> m_aMessagePile;
		std::vector<aeEvent*> m_aHistory;
	};

	/**********************************************************************************************//**
	 * @fn	extern void InitEventHandler();
	 *
	 * @brief	Handler, called when the init event.
	 **************************************************************************************************/

	extern void LIBRARY_EXPORT InitEventHandler();

	/**********************************************************************************************//**
	 * @fn	static void aeEventSystem::PostEvent(aeEvent &Event);
	 *
	 * @brief	Posts an event.
	 *
	 * @param [in,out]	Event	The event.
	 **************************************************************************************************/

	extern void LIBRARY_EXPORT PostEvent(aeEvent *Event);

	/**********************************************************************************************//**
	 * @fn	extern bool PollEvent(aeEvent *Event);
	 *
	 * @brief	Poll event.
	 *
	 * @param [in,out]	Event	If non-null, the event.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	extern bool LIBRARY_EXPORT  PollEvent(aeEvent **Event);
}