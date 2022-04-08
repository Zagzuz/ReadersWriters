#ifndef WORK_BOOKKEEPER_H
#define WORK_BOOKKEEPER_H

#include "../threads/thread.h"
#include "../threads/event.h"
#include "../threads/mutex.h"
#include "../utils/rand.h"
#include "../config.h"
#include "person.h"

#include <iostream>
#include <vector>
#include <mutex>


namespace rw::work
{
	class BookKeeper
	{
	public:
		BookKeeper();
		~BookKeeper();
	private:
		std::vector<rw::threads::Thread> threads_;
	};

	inline void reader(void* data)
	{
		rw::threads::Event w_ev(SYNCHRONIZE, w_event_name);
		w_ev.wait(INFINITE);
		rw::threads::Mutex m(r_mutex_name);
		std::lock_guard lock(m);
	
		auto person_ptr = static_cast<Person*>(data);
		std::string out = "Reader #" + std::to_string(GetCurrentThreadId()) + ":\t" + \
			person_ptr->first_name + ' ' + person_ptr->last_name + '\n';
		std::cout << out;
		Sleep(SLEEP_TIME);
	}
	
	inline void writer(void* data)
	{
		rw::threads::Mutex m(w_mutex_name);
		std::lock_guard lock(m);
		rw::threads::Event w_ev(EVENT_MODIFY_STATE, w_event_name);
		w_ev.reset();

		auto person_ptr = static_cast<Person*>(data);
		*person_ptr = utils::get_random(personas);
		std::string out = "Writer #" + std::to_string(GetCurrentThreadId()) + ":\t" + \
			person_ptr->first_name + ' ' + person_ptr->last_name + '\n';
		std::cout << out;
		Sleep(SLEEP_TIME);

		w_ev.set();
	}
} // namespace rw::work

#endif // WORK_BOOKKEEPER_H