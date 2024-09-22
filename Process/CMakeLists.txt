cmake_minimum_required(VERSION 3.10.2)

file(GLOB PROCESS_SOURCES *.cpp *.c)

foreach(SOURCE_FILE ${PROCESS_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION Process)
endforeach()

set_target_properties(countdown PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")