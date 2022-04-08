#include "thread.h"


namespace rw::threads
{
	void Thread::wait(DWORD time_ms) const
	{
		if (WaitForSingleObject(t_, time_ms) != WAIT_OBJECT_0)
		{
			throw std::runtime_error("Thread::wait(time_ms) failed with error: " + \
				utils::lasterror());
		}
	}

	void Thread::close()
	{
		if (!CloseHandle(t_))
		{
			throw std::runtime_error("Thread::close() failed with error: " + \
				utils::lasterror());
		}
	}

	void Thread::terminate()
	{
		if (!TerminateThread(t_, 3))
		{
			throw std::runtime_error("Thread::terminate() failed");
		}
	}
} // namespace rw::threads