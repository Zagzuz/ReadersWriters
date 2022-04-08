#ifndef WORK_PERSON_H
#define WORK_PERSON_H

#include <vector>
#include <string>


namespace rw::work
{
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
} // namespace rw::work

#endif // WORK_PERSON_H