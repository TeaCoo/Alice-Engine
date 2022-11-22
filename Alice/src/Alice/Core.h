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

#ifdef ALICE_ENABLE_ASSERTS
	#define ALICE_ASSERT(x, ...) { if(!(x)) { ALICE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak(); } }
	#define ALICE_CORE_ASSERT(x, ...) { if(!(x)) { ALICE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak(); } }
#else
	#define ALICE_ASSERT(x, ...)
	#define ALICE_CORE_ASSERT(x, ...)
#endif // ALICE_ENABLE_ASSERTS



#define BIT(x) (1 << x)