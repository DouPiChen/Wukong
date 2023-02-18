#pragma once
#include "Wupch.h"

#include "Instrumentor.h"

namespace Wukong
{
	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}

}

#define WU_PROFILE 1
#if WU_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define WU_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define WU_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define WU_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define WU_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define WU_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define WU_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define WU_FUNC_SIG __func__
	#else
		#define WU_FUNC_SIG "WU_FUNC_SIG unknown!"
	#endif

	#define WU_PROFILE_BEGIN_SESSION(name, filepath) ::Wukong::Instrumentor::Get().BeginSession(name, filepath)
	#define WU_PROFILE_END_SESSION() ::Wukong::Instrumentor::Get().EndSession()
	#define WU_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::Wukong::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												   ::Wukong::InstrumentationTimer timer##line(fixedName##line.Data)
	#define WU_PROFILE_SCOPE_LINE(name, line) WU_PROFILE_SCOPE_LINE2(name, line)
	#define WU_PROFILE_SCOPE(name) WU_PROFILE_SCOPE_LINE(name, __LINE__)
	#define WU_PROFILE_FUNCTION() WU_PROFILE_SCOPE(WU_FUNC_SIG)
#else
	#define WU_PROFILE_BEGIN_SESSION(name, filepath)
	#define WU_PROFILE_END_SESSION()
	#define WU_PROFILE_SCOPE(name)
	#define WU_PROFILE_FUNCTION()
#endif
