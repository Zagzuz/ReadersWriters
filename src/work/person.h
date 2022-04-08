#ifndef WORK_PERSON_H
#define WORK_PERSON_H

#include <vector>
#include <string>
#include <fstream>


namespace rw::work
{
	struct Person
	{
		std::string first_name;
		std::string last_name;
		Person(std::string f, std::string l) : 
			first_name(f), last_name(l) {};
		Person() : Person("First_name", "Last_name") {};
	};

	inline std::vector<Person> personas()
	{
		static std::vector<Person> ps;
		if (ps.empty())
		{
			std::ifstream fin(data_path);
			if (fin.is_open())
			{
				std::string first_name, last_name;
				while (fin >> first_name >> last_name)
					ps.emplace_back(first_name, last_name);
				fin.close();
			}
			else
			{
				throw std::runtime_error("'personas.txt' not found");
			}
		}
		return ps;
	}
} // namespace rw::work

#endif // WORK_PERSON_H
