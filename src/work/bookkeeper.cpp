#include "bookkeeper.h"


namespace rw::work
{
	BookKeeper::BookKeeper()
	{
		for (std::remove_const_t<decltype(N_REPEAT)> i = 0; i <= N_REPEAT; ++i)
		{
			std::cout << i + 1 << " run\n";
			threads_.reserve(N_THREADS);
			Person p{ "Andrew", "Anderson" };
			for (std::remove_const_t<decltype(N_THREADS)> j = 0; j < N_THREADS; ++j)
				threads_.emplace_back(j < N_READERS ? writer : reader, p);
			rw::threads::wait_multiple_threads_completion(threads_);
			threads_.clear();
		}
	}

	BookKeeper::~BookKeeper()
	{
		rw::threads::Mutex::close(w_mutex_name);
		rw::threads::Mutex::close(r_mutex_name);
		rw::threads::close_multiple_threads(threads_);
	}
} // namespace rw::work