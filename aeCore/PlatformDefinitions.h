/**********************************************************************************************//**
 * @file	PlatformDefinitions.h
 *
 * @brief	Declares the platform definitions class.
 **************************************************************************************************/

#pragma once
#include "dll_definition.h"
#include <string>
#include <vector>
#include <Windows.h>

 /************************************************************************************************************************/
 /* Useful macros.				                                        												*/
 /************************************************************************************************************************/

#if defined(_DEBUG)
#	define AE_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#	define AE_DELETE delete
#	define AE_DELETE_ARRAY delete []
#else
#	define AE_NEW new
#	define AE_DELETE delete
#	define AE_DELETE_ARRAY delete []
#endif

#if !defined(SAFE_DELETE)

/**********************************************************************************************//**
 * @def	SAFE_DELETE(x) if(x) GEE_DELETE x;
 *
 * @brief	A macro that defines safe delete.
 *
 * @param	x	The void to process.
 **************************************************************************************************/

#define SAFE_DELETE(x) if(x) AE_DELETE x; x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)

/**********************************************************************************************//**
 * @def	SAFE_DELETE_ARRAY(x) if (x) GEE_DELETE_ARRAY x;
 *
 * @brief	A macro that defines safe delete array.
 *
 * @param	x	The void to process.
 **************************************************************************************************/

#define SAFE_DELETE_ARRAY(x) if (x) AE_DELETE_ARRAY x; x=NULL; 
#endif

#if !defined(SAFE_RELEASE)

/**********************************************************************************************//**
 * @def	SAFE_RELEASE(x) if(x) x->Release();
 *
 * @brief	A macro that defines safe release.
 *
 * @param	x	The void to process.
 **************************************************************************************************/

#define SAFE_RELEASE(x) if(x) x->Release(); x=NULL;
#endif

#ifdef DLL_EXPORT

/**********************************************************************************************//**
 * @def	DLL_CONFIG();
 *
 * @brief	A macro that defines DLL configuration.
 *
 * @param	dllexport	The dllexport.
 **************************************************************************************************/

#define DLL_CONFIG _declspec(dllexport)
#else

/**********************************************************************************************//**
 * @def	DLL_CONFIG();
 *
 * @brief	A macro that defines DLL configuration.
 *
 * @param	dllimport	The dllimport.
 **************************************************************************************************/

#define DLL_CONFIG _declspec(dllimport)
#endif

#if !defined(COS_PI_QUARTER)
#define COS_PI_QUARTER 0.707106f;
#endif

namespace aeCore
{
	/************************************************************************************************************************/
	/* Basic unsigned types		                                            												*/
	/************************************************************************************************************************/
	///8-bit  unsigned.
	typedef unsigned char 		LIBRARY_EXPORT uint8;
	///16-bit unsigned.
	typedef unsigned short int	LIBRARY_EXPORT uint16;
	///32-bit unsigned.
	typedef unsigned int		LIBRARY_EXPORT uint32;
	///64-bit unsigned.
	typedef unsigned long long	LIBRARY_EXPORT uint64;

	/************************************************************************************************************************/
	/* Basic signed types                                               													*/
	/************************************************************************************************************************/
	///8-bit  signed.
	typedef	signed char			LIBRARY_EXPORT int8;
	///16-bit signed.
	typedef signed short int	LIBRARY_EXPORT int16;
	///32-bit signed.
	typedef signed int	 		LIBRARY_EXPORT int32;
	///64-bit signed.
	//typedef signed long long	int64;		

	/************************************************************************************************************************/
	/* Character types		                                                  												*/
	/************************************************************************************************************************/
	///An ANSI char, normally signed
	typedef char				LIBRARY_EXPORT ANSICHAR;
	///A UNICODE char, normally signed
	typedef wchar_t				LIBRARY_EXPORT UNICHAR;

	/************************************************************************************************************************/
	/* String constants			                                              												*/
	/************************************************************************************************************************/
#ifdef UNICODE		//If UNICODE in use
#define PLATFORM_TCHAR_IS_1_BYTE 0				//Indicates that the characters in this platform are more than 1 byte long
	///Defines TCHAR as a wide char
	typedef wchar_t	LIBRARY_EXPORT TCHAR;
	///Defines the type aeString
	typedef std::wstring LIBRARY_EXPORT  aeString;
#else	//We are compiling in Multi-Byte
#define PLATFORM_TCHAR_IS_1_BYTE 1				//Indicates that the characters in this platform are 1 byte long 
	///Defines TCHAR as a wide char
	typedef char LIBRARY_EXPORT  TCHAR;
	///Defines the type aeString
	typedef std::string LIBRARY_EXPORT  aeString;
#endif	// UNICODE


/************************************************************************************************************************/
/* Functions for string conversions							        												*/
/************************************************************************************************************************/

	/**********************************************************************************************//**
	 * @fn	static std::string ws2s(const std::wstring& s)
	 *
	 * @brief	Converts UNICODE strings into ANSI strings.
	 *
	 * @param	s	The std::wstring to process.
	 *
	 * @return	A std::string.
	 **************************************************************************************************/

	static std::string ws2s(const std::wstring& s)
	{
		int slength = (int)s.length() + 1;
		int len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0) - 1;
		std::string r(len, '\0');
		WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
		return r;
	}

	/**********************************************************************************************//**
	 * @fn	static std::wstring s2ws(const std::string &s)
	 *
	 * @brief	Converts ANSI strings into UNICODE strings.
	 *
	 * @param	s	The std::string to process.
	 *
	 * @return	A std::wstring.
	 **************************************************************************************************/

	static std::wstring s2ws(const std::string &s)
	{
		int slength = (int)s.length() + 1;
		int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0) - 1;
		std::wstring r(len, '\0');
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
		return r;
	}

	/**********************************************************************************************//**
	 * @fn	template<typename T> static bool EnumCompare(T EnumClass, int Value)
	 *
	 * @brief	Compares an enum class to a integer value.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	EnumClass	The enum class.
	 * @param	Value	 	The value.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	template<typename T>
	static bool EnumCompare(T EnumClass, int Value)
	{
		return (static_cast<int>(EnumClass) == Value);
	};
}