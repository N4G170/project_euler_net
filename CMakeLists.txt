cmake_minimum_required(VERSION 3.8.2)

#project name and cpp standard (c++11)
project("Project Euler Server" CXX)
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(app_name "euler_server")

#include_directories(src)#will search inside all directories inside src
add_subdirectory(src)

#Get include directories from sub folders
set(INCLUDE_DIRECTORIES "")
get_directory_property(INCLUDE_DIRECTORIES DIRECTORY src DEFINITION INCLUDE_DIRECTORIES)
#Add include directories
include_directories(${INCLUDE_DIRECTORIES})

#Get Source files paths from subfolders
set(SOURCE_FILES "")
get_directory_property(SOURCE_FILES DIRECTORY src DEFINITION SOURCE_FILES)

#Get Header files paths
set(HEADER_FILES "")
get_directory_property(HEADER_FILES DIRECTORY src DEFINITION HEADER_FILES)


# includes cmake_modules/FindSDL2*.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (UNIX)
#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
#SDL2 net
find_package(SDL2_net REQUIRED)
include_directories(${SDL2_NET_INCLUDE_DIR})

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIR})

endif (UNIX)


if (WIN32)
#SDL2
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/sdl2/include)
include_directories(${SDL2_INCLUDE_DIR})
set(SDL2_LIBRARY ${CMAKE_SOURCE_DIR}/external/sdl2/lib/sdl2.lib ${CMAKE_SOURCE_DIR}/external/sdl2/lib/sdl2main.lib)
#SDL2 net
set(SDL2_NET_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/sdl2_net/include)
include_directories(${SDL2_NET_INCLUDE_DIR})
set(SDL2_NET_LIBRARY ${CMAKE_SOURCE_DIR}/external/sdl2_net/lib/sdl2_net.lib)

set(GMP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/mpir/include)
include_directories(${GMP_INCLUDE_DIR})
set(GMP_LIBRARIES ${CMAKE_SOURCE_DIR}/external/mpir/lib/mpir.lib)
endif (WIN32)


add_executable(${app_name} ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${app_name} PROPERTIES LINK_FLAGS "-Wl,-rpath,./data/lib")#add local folder as relative path

target_link_libraries(${app_name} ${SDL2_NET_LIBRARY} ${GMP_LIBRARIES} ${SDL2_LIBRARY})

#copy contents of root folder "data" to folder "data" next to executable, if build is succeeds(POST_BUILD)
add_custom_command(TARGET ${app_name} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${app_name}>/data)

if(WIN32)
add_custom_command(TARGET ${app_name} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll"
                   $<TARGET_FILE_DIR:${app_name}>)
add_custom_command(TARGET ${app_name} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "${PROJECT_SOURCE_DIR}/external/dlls/mpir.dll"
                   $<TARGET_FILE_DIR:${app_name}>)
add_custom_command(TARGET ${app_name} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "${PROJECT_SOURCE_DIR}/external/dlls/SDL2_net.dll"
                   $<TARGET_FILE_DIR:${app_name}>)
endif(WIN32)
