cmake_minimum_required(VERSION 3.30)

function(print_cmake_info)
    message(STATUS "=====================================")
    message(STATUS "============== CMAKE ================")
    message(STATUS "=====================================")

    message(STATUS "CMAKE_SOURCE_DIR     = ${CMAKE_SOURCE_DIR}")
    message(STATUS "VCPKG_ROOT           = $ENV{VCPKG_ROOT}")
    message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")

    message(STATUS "=====================================")
    message(STATUS "SDL3_DIR    = ${SDL3_DIR}")
    message(STATUS "SDL3_CONFIG = ${SDL3_CONFIG}")
    message(STATUS "=====================================")
endfunction()


#CMake Tutorial EP 11 | VSCODE | VCPKG Libraries | Project Setup Basics
#https://www.youtube.com/watch?v=Y7d42_MbhKo&t=136s
#Ýleri Seviye C++ Türkçe #5 | vcpkg Kurulumu & CMake/Toolchain Entegrasyonu (CLion)
#https://www.youtube.com/watch?v=fJ2BsdV3ACk

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_PREFIX_PATH "C:\\vcpkg\\installed\\x64-windows\\share")

project(VanPeyniri VERSION 1.0)


# kutuphanelerin dosya yolu
set(LIBS_LOCAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#=====================================================================#
#===========Kutuphane ve diger zamazingo ayarlari=====================#
#=====================================================================#

# Dinamik baglantiyi kes
set(SDL_SHARED OFF CACHE BOOL "Dinamik bagla:: Dinamik zimbirti" FORCE)
# Statik baglantiyi aktif hale getir
set(SDL_STATIC ON CACHE BOOL "Statik bagla:: Statik Dolma Pilavi" FORCE)

# Add dependencies
find_package(SDL3 CONFIG REQUIRED)

# find_package(SDL3_ttf CONFIG REQUIRED)

# header only
add_library(baku INTERFACE)
target_include_directories(baku INTERFACE ${LIBS_LOCAL_DIR}/baku)

add_subdirectory(${LIBS_LOCAL_DIR}/imgui-docking imgui_build)
add_subdirectory(${LIBS_LOCAL_DIR}/tracy tracy_build)
add_subdirectory(${LIBS_LOCAL_DIR}/tiny-process tiny_process_build)

set(REPROC++ ON)
add_subdirectory(${LIBS_LOCAL_DIR}/reproc reproc_build)

#print_cmake_info()

#=====================================================================#
#=====================================================================#

# supurge teknigi ile proje dosyalari MY_SOURCES icerisine atiliyor
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MY_SOURCES})

#====================LIBS=============================================#
#=====================================================================#

target_include_directories(${PROJECT_NAME}  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}  PRIVATE
    SDL3::SDL3
    imgui
    Tracy::TracyClient
    tiny-process-library
    reproc++
    baku
)

target_compile_definitions(${PROJECT_NAME}  PUBLIC cmake_PROJECT_RES="${CMAKE_CURRENT_SOURCE_DIR}/res/")
