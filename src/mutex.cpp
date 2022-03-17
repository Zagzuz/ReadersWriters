#include "mutex.h"

Mutex::Mutex()
{
	m_ = CreateMutexA(NULL, FALSE, NULL);
	if (!m_)
	{
		throw std::runtime_error("Mutex() failed with error: " + last_error());
	}
}

Mutex::Mutex(std::string name)
{
	m_ = CreateMutexA(NULL, FALSE, name.data());
	if (!m_)
	{
		throw std::runtime_error("Mutex() failed with error: " + last_error());
	}
}

void Mutex::lock()
{
	auto wait_res = WaitForSingleObject(m_, INFINITE);
	if (wait_res != WAIT_OBJECT_0)
	{
		throw std::runtime_error("Mutex::lock() failed with error: " + last_error());
	}
}

void Mutex::unlock()
{
	if (!ReleaseMutex(m_))
	{
		throw std::runtime_error("Mutex::unlock() failed with error: " + last_error());
	}
}
