#ifndef THREADS_EVENT_H
#define THREADS_EVENT_H

#include <windows.h>
#include <stdexcept>
#include <string>

#include "../utils/lasterror.h"


namespace rw::threads
{
	using event_t = HANDLE;
	
	class Event
	{
	public:
		Event(DWORD access, std::string name);
		void set();
		void reset();
		void wait(DWORD time_ms) const;
		void close();
		static Event create(std::string name);
		static void close(std::string name);
	private:
		explicit Event(event_t ev) : ev_(ev) {}

		event_t ev_;
	};
} // namespace rw::threads

#endif // THREADS_EVENT_H