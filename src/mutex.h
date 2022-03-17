#include <windows.h>
#include <stdexcept>
#include <string>

#include "../utils/last_error.h"

using mutex_t = HANDLE;

class Mutex
{
public:
	Mutex();
	explicit Mutex(std::string name);
	void lock();
	void unlock();
private:
	mutex_t m_;
};
