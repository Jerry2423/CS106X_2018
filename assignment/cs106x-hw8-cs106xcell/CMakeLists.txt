cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")
project(app)

include_directories(lib/StanfordCPPLib/
    lib/StanfordCPPLib/graphics/
    lib/StanfordCPPLib/util/
    lib/StanfordCPPLib/collections/
    lib/StanfordCPPLib/system/
    lib/StanfordCPPLib/io/
    src/)
file(GLOB stanford_files
        "lib/StanfordCPPLib/graphics/*.h"
        "lib/StanfordCPPLib/graphics/*.cpp"
        "lib/StanfordCPPLib/util/*.h"
        "lib/StanfordCPPLib/util/*.cpp"
        "lib/StanfordCPPLib/system/*.h"
        "lib/StanfordCPPLib/system/*.cpp"
        "lib/StanfordCPPLib/collections/*.h"
        "lib/StanfordCPPLib/collections/*.cpp"
        "lib/StanfordCPPLib/private/*.h"
        "lib/StanfordCPPLib/private/*.cpp"
        "lib/StanfordCPPLib/io/*.h"
        "lib/StanfordCPPLib/io/*.cpp"
        )
add_library(stanford ${stanford_files})

#add multiple files to the executable target
#group files in src together, when add_executable(), even without #include or definition in bogglegui.cpp, bollgegui.cpp can still find definition for the function defined in bogglesearch.cpp!
file(GLOB app_SOURCES "src/*.cpp" "src/*.h") 
link_libraries(stanford)

# add single file
# set(app_SOURCES src/main.cpp)
# link_libraries(stanford)

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

