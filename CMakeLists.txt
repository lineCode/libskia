cmake_minimum_required(VERSION 3.5)
project(HelloSkia)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-stdlib=libc++ ")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h src/*.mm src/*.m)

function(find_include_dirs out)
    file(GLOB_RECURSE headers ${ARGN})
    foreach (path ${headers})
        get_filename_component(dir ${path} PATH)
        list(APPEND include_dirs ${dir})
    endforeach ()
    list(REMOVE_DUPLICATES include_dirs)
    set(${out} ${include_dirs} PARENT_SCOPE)
endfunction()

find_include_dirs(includes third_party/skia/include/*.h)
include_directories(${includes} src)

set(OS_ARCH darwin-x64)
#if (CMAKE_BUILD_TYPE STREQUAL Release)
#    set(LIB_TYPE static)
#else ()
set(LIB_TYPE shared)
#endif ()

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices REQUIRED)
list(APPEND libs ${APPLICATION_SERVICES_FRAMEWORK})
find_library(A_G_L AGL REQUIRED)
list(APPEND libs ${A_G_L})
find_library(OPENGL OpenGL REQUIRED)
list(APPEND libs ${OPENGL})
find_library(QUARTZ_CORE QuartzCore REQUIRED)
list(APPEND libs ${QUARTZ_CORE})
find_library(COCOA Cocoa REQUIRED)
list(APPEND libs ${COCOA})
find_library(FOUNDATION Foundation REQUIRED)
list(APPEND libs ${FOUNDATION})

set(RESOURCE_FILES)
function(copy_file from to)
    list(APPEND RESOURCE_FILES ${to})
    set(RESOURCE_FILES ${RESOURCE_FILES} PARENT_SCOPE)
    add_custom_command(OUTPUT ${to}
            COMMAND ${CMAKE_COMMAND} -E copy ${from} ${to}
            MAIN_DEPENDENCY ${from})
endfunction()

set(skia_lib)
if (LIB_TYPE STREQUAL static)
    file(GLOB_RECURSE skia_lib third_party/skia/${OS_ARCH}-${LIB_TYPE}/*.a)
else ()
    file(GLOB_RECURSE skia_lib third_party/skia/${OS_ARCH}-${LIB_TYPE}/*.dylib third_party/skia/${OS_ARCH}-${LIB_TYPE}/*.so)
    foreach (path ${skia_lib})
        get_filename_component(fileName ${path} NAME)
        copy_file(${path} ${CMAKE_BINARY_DIR}/${fileName})
    endforeach ()
endif ()

copy_file(${CMAKE_SOURCE_DIR}/assets/test.png ${CMAKE_BINARY_DIR}/assets/test.png)
add_custom_target(Resources ALL DEPENDS ${RESOURCE_FILES})

link_directories(${CMAKE_BINARY_DIR})

add_executable(Main ${SOURCE_FILES})
target_link_libraries(Main ${skia_lib} ${libs})

