#pragma once


#ifdef DLL_BUILD   
#ifdef DLL_EXPORT   
#define LIBRARY_EXPORT __declspec(dllexport) 
#else   
#define LIBRARY_EXPORT __declspec(dllimport) 
#endif
#else
#define LIBRARY_EXPORT
#endif