cmake_minimum_required(VERSION 2.8)

project(TrailEngine)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(OpenGL REQUIRED)

if(WIN32)
        set(SDL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third-party/include/Windows)
        set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third-party/include/Windows)
	set(SDL_LIBRARY mingw32 ${CMAKE_SOURCE_DIR}/third-party/lib/x86/libSDLmain.a ${CMAKE_SOURCE_DIR}/third-party/lib/x86/libSDL.dll.a)
	set(GLEW_LIBRARY ${CMAKE_SOURCE_DIR}/third-party/lib/x86/libglew32.dll.a)

	set(DLL_BINARIES ${CMAKE_SOURCE_DIR}/third-party/lib/x86/glew32.dll ${CMAKE_SOURCE_DIR}/third-party/lib/x86/SDL.dll)

else(WIN32)
	find_package(SDL REQUIRED)
	find_package(GLEW REQUIRED)
endif(WIN32)

if(UPEMLV)
    # Flag a activer pour compilation à la FAC
    set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
endif(UPEMLV)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

# Add the glimac library
add_subdirectory(glimac)

# A macro to add a directory containing shaders. Each file ".glsl" is considered to be a shader and a target
# is added to the Makefile in order to copy the shader in the build directory when it is modified
macro(ADD_SHADER_DIRECTORY directory)
    file(GLOB_RECURSE relative_files RELATIVE ${directory} ${directory}/*.glsl)
    file(GLOB_RECURSE files ${directory}/*.glsl)

    if(files)
        list(LENGTH files file_count)
        math(EXPR range_end "${file_count} - 1")

        foreach(idx RANGE ${range_end})
            list(GET files ${idx} file)
            list(GET relative_files ${idx} relative_file)

            add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/${relative_file}
                             COMMAND ${CMAKE_COMMAND} -E copy ${file} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${relative_file}
                             MAIN_DEPENDENCY ${file})
        endforeach()
    endif()
endmacro()

# A macro that the CMakeLists.txt of every TP should call for correct build
macro(ADD_TP_DIRECTORY)
    file(GLOB HEADER_FILES *.hpp) # get all headers
    file(GLOB SRC_FILES *.cpp) # get all sources files
    file(GLOB_RECURSE SHADER_FILES *.glsl) # get all shaders

    # compile each source file as an independant executable
    foreach(SRC_FILE ${SRC_FILES})
        get_filename_component(FILE ${SRC_FILE} NAME_WE) # get the name of the source file without extension
        get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME) # get the name of the directory of the TP
        set(OUTPUT ${DIR}_${FILE}) # set the name of the ouput executable
        add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES}) # add the executable
        target_link_libraries(${OUTPUT} ${ALL_LIBRARIES}) # and link  to the libraries
    endforeach()

    ADD_SHADER_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/shaders)

    if(WIN32)
        # on windows, copy dll files to the executable directory
        file(COPY ${DLL_BINARIES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif(WIN32)
endmacro()

# All directory starting with "TP" are considered as individual TP
file(GLOB TP_DIRECTORIES "TP*")
foreach(TP ${TP_DIRECTORIES})
    add_subdirectory(${TP})
endforeach()
