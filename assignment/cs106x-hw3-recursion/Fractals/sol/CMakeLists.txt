cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")
project(app)

include_directories(lib/)
file(GLOB stanford_files
        "lib/graphics/*.h"
        "lib/graphics/*.cpp"
        "lib/util/*.h"
        "lib/util/*.cpp"
        "lib/system/*.h"
        "lib/system/*.cpp"
        "lib/collections/*.h"
        "lib/collections/*.cpp"
        "lib/private/*.h"
        "lib/private/*.cpp"
        "lib/io/*.h"
        "lib/io/*.cpp"
        )
add_library(stanford ${stanford_files})

set(app_SOURCES src/main.cpp)
link_libraries(stanford)

include_directories(src/prep)
file(GLOB work_files
    "src/prep/*.h"
    "src/prep/*.cpp")
add_library(work ${work_files})
link_libraries(work)

# file(GLOB my_res "res/*.png" "res/*.gif")
# file(COPY my_res DESTINATION "${CMAKE_BINARY_DIR}")
# file(COPY res/*.gif DESTINATION "${CMAKE_BINARY_DIR}")
add_executable(app ${app_SOURCES})

add_custom_command(TARGET app PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:app>)

