#include "mutex.h"

namespace rw::threads
{
	Mutex::Mutex()
	{
		m_ = CreateMutexA(NULL, FALSE, NULL);
		if (!m_)
		{
			throw std::runtime_error("Mutex() failed with error: " + \
				utils::lasterror());
		}
	}

	Mutex::Mutex(std::string name)
	{
		m_ = CreateMutexA(NULL, FALSE, name.data());
		if (!m_)
		{
			throw std::runtime_error("Mutex() failed with error: " + \
				utils::lasterror());
		}
	}

	void Mutex::lock()
	{
		auto wait_res = WaitForSingleObject(m_, INFINITE);
		if (wait_res != WAIT_OBJECT_0)
		{
			throw std::runtime_error("Mutex::lock() failed with error: " + \
				utils::lasterror());
		}
	}

	void Mutex::unlock()
	{
		if (!ReleaseMutex(m_))
		{
			throw std::runtime_error("Mutex::unlock() failed with error: " + \
				utils::lasterror());
		}
	}
} // namespace rw::threads