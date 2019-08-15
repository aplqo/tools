cmake_minimum_required (VERSION 3.8)

find_package(Boost COMPONENT property_tree REQUIRED)
include_directories(${Boost_INCLUD_DIRS})

add_executable (ir-eeprom "ir-eeprom.cpp")
target_link_libraries(ir-eeprom ${Boost_LIBRARIES})