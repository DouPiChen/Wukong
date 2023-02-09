#pragma once

#ifdef WU_DEBUG
	#define WU_ENABLE_ASSERTS
#endif

#ifdef WU_ENABLE_ASSERTS
	#define WU_ASSERT(x,...) { if(!(x)) { WU_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
	#define WU_CORE_ASSERT(x,...) { if(!(x)) { WU_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
#else
	#define WU_ASSERT(x,...)
	#define WU_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)
