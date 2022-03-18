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
} // namespace rw::threads

#endif // THREADS_THREAD_H