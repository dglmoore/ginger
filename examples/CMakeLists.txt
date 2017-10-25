link_libraries(${PROJECT_NAME}_static)
if (UNIX)
    link_libraries(m)
endif()

add_subdirectory(vector)
add_subdirectory(unit)
