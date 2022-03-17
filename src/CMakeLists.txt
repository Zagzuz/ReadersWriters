add_executable(Main "main.cpp")
add_library(Mutex STATIC "mutex.cpp" "mutex.h")
target_link_libraries(Main PUBLIC Mutex)
