project(verkkosimutests LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

include_directories("../src")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(verkkosimutests tst_networktest.cpp)
add_test(NAME verkkosimutests COMMAND verkkosimutests)

target_link_libraries(verkkosimutests PRIVATE Qt::Test Qt::Widgets)
