#pragma once

namespace Dogo {

#if DG_PLATFORM_WINDOWS
	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0 / static_cast<double>(frequency.QuadPart);

			QueryPerformanceCounter(&m_Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}

	};
#else
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> m_Start;
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_Start = HighResolutionClock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
		}

	};
#endif

}