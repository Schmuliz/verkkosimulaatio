cmake_policy(SET CMP0048 NEW) 

set(CMAKE_AUTORCC ON)

project(verkkosimu VERSION 0.0.1)

cmake_minimum_required(VERSION 3.15)

add_subdirectory(src)

#add_custom_target(copy_assets
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
#)
#add_dependencies(verkkosimu copy_assets)



