#include "event.h"

namespace rw::threads
{
	Event::Event(DWORD access, std::string name)
	{
		ev_ = OpenEventA(access, FALSE, TEXT(name.data()));
		if (!ev_)
		{
			(void)create(name);
		}
		ev_ = OpenEventA(access, FALSE, TEXT(name.data()));
		if (!ev_)
		{
			throw std::runtime_error("Event(access, name) failed with error: " + \
				utils::lasterror());
		}
	}

	Event Event::create(std::string name)
	{
		Event res(CreateEventA(NULL, TRUE, FALSE, TEXT(name.data())));
		if (!res.ev_)
		{
			throw std::runtime_error("Event::create(name) failed with error: " + \
				utils::lasterror());
		}
		return res;
	}

	void Event::set()
	{
		if (!SetEvent(ev_))
		{
			throw std::runtime_error("Event::set() failed with error: " + \
				utils::lasterror());
		}
	}

	void Event::reset()
	{
		if (!ResetEvent(ev_))
		{
			throw std::runtime_error("Event::reset() failed with error: " + \
				utils::lasterror());
		}
	}

	void Event::wait(DWORD time_ms) const
	{
		if (WaitForSingleObject(ev_, time_ms) != WAIT_OBJECT_0)
		{
			throw std::runtime_error("Event::wait() failed with error: " + \
				utils::lasterror());
		}
	}

	void Event::close()
	{
		if (!CloseHandle(ev_))
		{
			throw std::runtime_error("Event::close() failed with error: " + \
				utils::lasterror());
		}
	}

	void Event::close(std::string name)
	{
		auto ev_ = OpenEventA(EVENT_MODIFY_STATE, FALSE, TEXT(name.data()));
		if (!ev_)
		{
			throw std::runtime_error("Event::close(name) failed with error: " + \
				utils::lasterror());
		}
		if (!CloseHandle(ev_))
		{
			throw std::runtime_error("Event::close(name) failed with error: " + \
				utils::lasterror());
		}
	}
} // namespace rw::threads