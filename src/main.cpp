#include <windows.h>
#include <cassert>
#include <array> 
#include <iostream>
#include <string>
#include <random>
#include <type_traits>
#include <mutex>

#include "../threads/mutex.h"
#include "../threads/event.h"


using thread_t = HANDLE;
using thread_id_t = DWORD;

constexpr std::size_t N_REPEAT = 1;
constexpr std::size_t N_WRITERS = 10;
constexpr std::size_t N_READERS = 20;
constexpr std::size_t SLEEP_TIME = 1'000;
constexpr std::size_t N_THREADS = N_WRITERS + N_READERS;

static std::string w_event_name = "WriteCompleted";

static const std::string w_mutex_name = "WriteMutex";
static const std::string r_mutex_name = "ReadMutex";


struct Person
{
	std::string first_name;
	std::string last_name;
};

inline std::vector<Person> personas = {
	{ "John", "Smith" },
	{ "Mary", "Davis" },
	{ "Lyndon", "Gray" },
	{ "Sarah", "Dixon" },
	{ "Rubie", "Davis" },
	{ "Alina", "Rogers" },
	{ "Lily", "Carroll" },
	{ "Alen", "Hawkins" },
	{ "Alford", "Myers" },
	{ "Max", "Anderson" },
	{ "Kellan", "Carter" },
	{ "Savana", "Rogers" },
	{ "Oscar", "Edwards" },
	{ "Sarah", "Spencer" },
	{ "Rafael", "Gibson" },
	{ "Jose", "Gonzalez" },
	{ "Charlie", "Thomas" },
	{ "Jerry", "Williams" },
	{ "Michael", "Johnson" },
	{ "Bertram", "Wooster" },
	{ "Reginald", "Jeeves" },
	{ "Hailey", "Ferguson" },
	{ "Mike", "Cunningham" },
	{ "Kelvin", "Sullivan" },
	{ "Victoria", "Perkins" },
	{ "Madaline", "Anderson" },
	{ "Kristian", "Ferguson" },
	{ "Augustus", "Fink-Nottle" }
};


bool toss()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::bernoulli_distribution bdist(0.5);
	return bdist(gen);
}

template <typename T, typename Allocator, 
	template <typename, typename> class Container>
T get_random(const Container<T, Allocator>& c)
{
	if (c.empty()) return {};
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> udist(0, static_cast<int>(c.size() - 1));
	return c[udist(gen)];
}


void reader(void* data)
{
	rw::threads::Event w_ev(SYNCHRONIZE, w_event_name);
	w_ev.wait(INFINITE);

	rw::threads::Mutex m(r_mutex_name);
	std::lock_guard lock(m);

	// print read data
	auto person_ptr = static_cast<Person*>(data);
	std::string out = "Reader #" + std::to_string(GetCurrentThreadId()) + ":\t" + \
		person_ptr->first_name + ' ' + person_ptr->last_name + '\n';
	std::cout << out;
	Sleep(SLEEP_TIME);
}

void writer(void* data)
{
	rw::threads::Mutex m(w_mutex_name);
	std::lock_guard lock(m);

	rw::threads::Event w_ev(EVENT_MODIFY_STATE, w_event_name);
	w_ev.reset();

	// change data
	auto person_ptr = static_cast<Person*>(data);
	*person_ptr = get_random(personas);
	std::string out = "Writer #" + std::to_string(GetCurrentThreadId()) + ":\t" + \
		person_ptr->first_name + ' ' + person_ptr->last_name + '\n';
	std::cout << out;
	Sleep(SLEEP_TIME);

	w_ev.set();
}

int main(int argc, char** argv)
{
	std::array<thread_t, N_THREADS> threads;
	std::array<thread_id_t, N_THREADS> thread_ids;
	Person p{ "Andrew", "Anderson" };

	assert(threads.size() > 2 && threads.size() == thread_ids.size());

	for (std::remove_const_t<decltype(N_REPEAT)> i = 0; i < N_REPEAT; ++i)
	{
		auto n_readers = N_READERS;
		auto n_writers = N_WRITERS;
		for (std::size_t i = 0; i < threads.size(); ++i)
		{
			bool choice;
			if (n_readers == 0) choice = 0;
			else if (n_writers == 0) choice = 1;
			else choice = toss();
			(choice ? n_readers : n_writers) -= 1;
			auto func = reinterpret_cast<LPTHREAD_START_ROUTINE>(choice ? &reader : &writer);
			threads[i] = CreateThread(NULL, 0, func, &p, 0, &thread_ids[i]);
		}

		WaitForMultipleObjects(N_THREADS, threads.data(), TRUE, INFINITE);

		for (std::size_t i = 0; i < threads.size(); ++i)
			CloseHandle(threads[i]);
	};
	
	rw::threads::Mutex::close(w_mutex_name);
	rw::threads::Mutex::close(r_mutex_name);

	return 0;
}