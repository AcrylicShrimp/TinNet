
/*
	2017.08.22
	Created by AcrylicShrimp.
*/

#ifndef _TINNET_DLL

#define _TINNET_DLL

#ifdef _TINNET_DLL_EXPORT

#define TINNET_DLL __declspec(dllexport)

#else

#define TINNET_DLL __declspec(dllimport)

#endif

#endif