#ifndef UTILS_RAND_H
#define UTILS_RAND_H

#include <random>


namespace rw::utils
{
	bool toss()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::bernoulli_distribution bdist(0.5);
		return bdist(gen);
	}

	template <class Container>
	typename Container::value_type get_random(const Container& c)
	{
		if (c.empty()) return {};
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> udist(0, static_cast<int>(c.size() - 1));
		return c[udist(gen)];
	}

} // namespace rw::utils

#endif // UTILS_RAND_H