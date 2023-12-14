project(wpilibjs)

set(CMAKE_CXX_STANDARD 20)

add_library(wpilibjs OBJECT src/wpilibjs.cpp)

target_link_libraries(wpilibjs wpimath wpiutil)
target_include_directories(wpilibjs PUBLIC src/include)