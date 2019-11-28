
#ifndef _TINNET_PLATFORM_CALLINGCONVENTION_H

#define _TINNET_PLATFORM_CALLINGCONVENTION_H

#ifdef _TINNET_PLATFORM_WINDOWS

#	define _TINNET_CDECL __cdecl
#	define _TINNET_STDCALL __stdcall
#	define _TINNET_REGCALL __regcall

#else

#	define _TINNET_CDECL __attribute__((cdecl))
#	define _TINNET_STDCALL __attribute__((stdcall))
#	define _TINNET_REGCALL __attribute__((regcall))

#endif

#endif