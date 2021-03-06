#ifndef THREADS_MUTEX_H
#define THREADS_MUTEX_H

#include <windows.h>
#include <stdexcept>
#include <string>

#include "../utils/lasterror.h"


namespace rw::threads
{
	using mutex_t = HANDLE;

	class Mutex
	{
	public:
		Mutex();
		explicit Mutex(const std::string& name);
		void lock() const;
		void unlock();
		void close();
		static void close(const std::string& name);
	private:
		mutex_t m_;
	};
} // namespace rw::threads

#endif // THREADS_MUTEX_H