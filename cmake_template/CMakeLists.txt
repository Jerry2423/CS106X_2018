cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")
project(app)

include_directories(lib/
    lib/graphics/
    lib/util/
    lib/collections/
    lib/system/
    lib/private/
    lib/io/)
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

#add multiple files to the executable target
#group files in src together, when add_executable(), even without #include or definition in bogglegui.cpp, bollgegui.cpp can still find definition for the function defined in bogglesearch.cpp!
# file(GLOB app_SOURCES "src/*.cpp" "src/*.h")

# add single file
set(app_SOURCES src/main.cpp)
link_libraries(stanford)

# example: add more libraries (e.g there are some files in the src/prep)
# order matters! This should be done before add_executable()
#part: include + file + add_library + link
# include_directories(src/prep)
# file(GLOB work_files
#     "src/prep/*.h"
#     "src/prep/*.cpp")
# add_library(work ${work_files})
# link_libraries(work)

add_executable(app ${app_SOURCES})

# copy the java spl.jar to the buiding directory
file(COPY lib/spl.jar DESTINATION "${CMAKE_BINARY_DIR}")

# add stuff from res to target build directory
add_custom_command(TARGET app PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:app>)

