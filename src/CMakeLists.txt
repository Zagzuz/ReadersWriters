add_subdirectory(threads)
add_subdirectory(work)
add_executable(Main "main.cpp")
target_link_libraries(Main PUBLIC Mutex Event Thread BookKeeper)
