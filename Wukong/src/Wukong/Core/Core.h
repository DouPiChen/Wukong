#pragma once

#include <memory>

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


namespace Wukong
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T,typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}