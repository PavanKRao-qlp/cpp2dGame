# CMakeList.txt : CMake project for 2dcppGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("2dcppGame" VERSION 1.0)

#---------git---------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(SFML_STATIC)

add_subdirectory("vendor/sfml")
add_subdirectory("vendor/entt")
add_subdirectory("vendor/box2d")
add_subdirectory("vendor/sdl2")

set(INCLUDE_DIRS 
"vendor/sfml/include";
"vendor/sfml/extlibs/headers";
"vendor/entt/src";
"vendor/mini/src";
"vendor/box2d/include";
"vendor/sdl2/include";
"src/"
)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
     ${PROJECT_SOURCE_DIR}/src/*.cpp 
     ${PROJECT_SOURCE_DIR}/src/*.h
    )
else()
    file(GLOB SOURCE_FILES
      ${PROJECT_SOURCE_DIR}/src/*.cpp
      ${PROJECT_SOURCE_DIR}/src/*.h
      ${PROJECT_SOURCE_DIR}/src/*/*.h
      ${PROJECT_SOURCE_DIR}/src/*/*.cpp
      )
endif()


set(EXT_LIBRARY 
#box2d
box2d;
#sfml
debug sfml-system-s-d optimized  sfml-system-s;
debug sfml-window-s-d optimized sfml-window-s;
debug sfml-audio-s-d optimized sfml-audio-s;
debug sfml-network-s-d optimized sfml-network-s;
debug sfml-graphics-s-d optimized sfml-graphics-s;
opengl32;
freetype;
openal32;
flac;
vorbisenc;
vorbisfile;
vorbis;
ogg;
ws2_32;
winmm;
#sdl2
SDL2maind
)

set(EXT_LIBRARY_DIR
${PROJECT_SOURCE_DIR}/libs;
${PROJECT_SOURCE_DIR}/vendor/box2d/bin;
${PROJECT_SOURCE_DIR}/vendor/sfml/extlibs/libs-msvc/x64;
${PROJECT_BINARY_DIR}/vendor/sfml/lib;
${PROJECT_BINARY_DIR}/vendor/sdl2;

)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${EXT_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXT_LIBRARY})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#copy assets 
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        ${PROJECT_BINARY_DIR}/assets
        COMMENT "Copying resources into binary directory")

add_dependencies(${PROJECT_NAME} copy_resources)

install(TARGETS  ${PROJECT_NAME})
include(CPack)
# TODO: Add tests and install targets if needed.
