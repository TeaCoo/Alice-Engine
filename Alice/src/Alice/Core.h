#pragma once

#ifdef ALICE_PLATFORM_WINDOWS
	#ifdef ALICE_BUILD_DLL
		#define ALICE_API __declspec(dllexport)
	#else
		#define ALICE_API __declspec(dllimport)
	#endif // ALICE_BUILD_DLL
#else
	#error Alice only supports windows!
#endif
