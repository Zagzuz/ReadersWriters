#ifndef CONFIG_H
#define CONFIG_H

constexpr std::size_t N_REPEAT = 2;
constexpr std::size_t N_WRITERS = 10;
constexpr std::size_t N_READERS = 20;
constexpr std::size_t SLEEP_TIME = 0'000;
constexpr std::size_t N_THREADS = N_WRITERS + N_READERS;
static const std::string r_mutex_name = "ReadMutex";
static const std::string w_mutex_name = "WriteMutex";
static const std::string w_event_name = "WriteCompleted";
static const std::string data_path = "../../../../data/personas.txt";

#endif // CONFIG_H
