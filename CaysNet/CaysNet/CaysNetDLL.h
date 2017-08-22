
/*
	2017.08.22
	Created by AcrylicShrimp.
*/

#ifndef _CAYS_NET_DLL

#define _CAYS_NET_DLL

#ifdef _CAYS_NET_DLL_EXPORT

#define CAYSNET_DLL __declspec(dllexport)

#else

#define CAYSNET_DLL __declspec(dllimport)

#endif

#endif