#ifndef THREADS_THREAD_H
#define THREADS_THREAD_H

#include <windows.h>
#include <stdexcept>
#include <functional>

#include "../utils/lasterror.h"


namespace rw::threads
{
	using thread_t = HANDLE;

	class Thread
	{
	public:
		template <typename Func, typename Parameters> Thread(Func& f, Parameters& ps);
		void wait(DWORD time_ms) const;
		void close();
		void terminate();
		template <class Container> friend void wait_multiple_threads(DWORD time_ms, const Container& threads);
	private:
		thread_t t_;
	};

	template <typename Func, typename Parameters>
	inline Thread::Thread(Func& f, Parameters& ps)
	{
		t_ = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&f),
			static_cast<LPVOID>(&ps), 0, NULL);
		if (!t_)
		{
			throw std::runtime_error("Thread(f, ps) failed with error: " + \
				utils::lasterror());
		}
	}

	template <class Container>
	void wait_multiple_threads(DWORD time_ms, const Container& threads)
	{
		for (const Thread& thread : threads)
			thread.wait(time_ms);
	}

	template <class Container>
	void wait_multiple_threads_completion(Container& threads)
	{
		for (Thread& thread : threads)
		{
			try
			{
				thread.wait(INFINITE);
			}
			catch (std::runtime_error& e)
			{
				std::cerr << e.what() << "; thread terminated;";
				thread.terminate();
			}
		}
	}

	template <class Container>
	void close_multiple_threads(Container& threads)
	{
		for (Thread& thread : threads)
			thread.close();
	}
} // namespace rw::threads

#endif // THREADS_THREAD_H