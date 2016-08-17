/**********************************************************************************************//**
 * @file	Game\Timer.h
 *
 * @brief	Declares the timer class.
 **************************************************************************************************/

#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include <chrono>
#include "EventsSystem.h"
#include "dll_definition.h"

namespace aeCore
{
	/**********************************************************************************************//**
	 * @class	aeClock
	 *
	 * @brief	A high resolution timer.
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeClock
	{
		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
	public:

		/**********************************************************************************************//**
		 * @fn	aeClock::aeClock()
		 *
		 * @brief	Default constructor.
		 **************************************************************************************************/

		aeClock();

		/**********************************************************************************************//**
		 * @fn	aeClock::~aeClock()
		 *
		 * @brief	Destructor.
		 **************************************************************************************************/

		~aeClock();

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/
	public:

		/**********************************************************************************************//**
		 * @fn	int Init();
		 *
		 * @brief	Gets 0 if it was initialized correctly, otherwise, it will get an error number.
		 *
		 * @return	An int.
		 **************************************************************************************************/

		int Init();

		/**********************************************************************************************//**
		 * @fn	void aeClock::Destroy();
		 *
		 * @brief	Destroys this object.
		 **************************************************************************************************/

		void Destroy();

		/**********************************************************************************************//**
		 * @fn	void aeClock::Update();
		 *
		 * @brief	Updates the delta time since last update and adds it up to the total time.
		 **************************************************************************************************/

		void Update();

		/**********************************************************************************************//**
		 * @fn	void aeClock::SetTimeScale(float NewTimeScale);
		 *
		 * @brief	Sets the time scale, for which it will multiply the delta time every update.
		 * 			In case of receiving a negative number, it will set the time scale to zero.
		 *
		 * @param	NewTimeScale	The new time scale.
		 **************************************************************************************************/

		void SetVirtualTimeScale(float NewTimeScale);

		/**********************************************************************************************//**
		 * @fn	float aeClock::VirtualTime();
		 *
		 * @brief	Returns the time since Init affected by the time scale.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float VirtualTime();

		/**********************************************************************************************//**
		 * @fn	float aeClock::RealTime();
		 *
		 * @brief	Returns the time since Init.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float RealTime();

		/**********************************************************************************************//**
		 * @fn	float aeClock::VirtualDeltaTime();
		 *
		 * @brief	Returns the delta time between update calls affected by the time scale.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float VirtualDeltaTime();

		/**********************************************************************************************//**
		 * @fn	float aeClock::RealDeltaTime();
		 *
		 * @brief	RReturns the delta time between update calls.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float RealDeltaTime();

		/**********************************************************************************************//**
		 * @fn	void aeClock::SetTimer(float Time, uint8 ID);
		 *
		 * @brief	Sets a timer.
		 *
		 * @param	Time	The time.
		 * @param	ID  	The identifier.
		 **************************************************************************************************/

		void SetTimer(float Time, uint8 ID);

		/**********************************************************************************************//**
		 * @fn	bool aeClock::PollEvents(uint8* ID);
		 *
		 * @brief	Poll events.
		 *
		 * @param [in,out]	ID	If non-null, the identifier.
		 *
		 * @return	true if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool PollEvents(uint8* ID);

	private:
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		std::chrono::high_resolution_clock::time_point m_Timer;
		std::chrono::duration<float> m_Delta;
		float m_fTimeScale;
		float m_fVirtualTimeSinceInit;
		float m_fTimeSinceInit;
		float m_fTimeSinceUpdate;

		struct aeTimer
		{
			float fTimer;
			uint32 Counter;
			uint8 ID;
		};

		std::queue<uint8> m_aEventsPile;
		std::vector<aeTimer> m_aTimers;

		void PostCalls(float RealTime);
	};
}