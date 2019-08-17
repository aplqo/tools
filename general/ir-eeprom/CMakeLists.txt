cmake_minimum_required (VERSION 3.8)
cmake_policy(SET CMP0074 NEW)

aux_source_directory(. src)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable (ir-eeprom ${src})
target_link_libraries(ir-eeprom ${Boost_LIBRARIES})