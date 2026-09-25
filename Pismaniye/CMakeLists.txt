cmake_minimum_required(VERSION 3.15)

# projenin ismi
project(DonenBazlama)

# cmake degiskenleri tanimlaniyor

# c++ versiyonu ayarlaniyor
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# kutuphane yolu
option(tekproje "kutuphaneler cmakelist in yaninda" OFF)
option(altproje "kutuphaneler bir ust klasor icinde" ON)

if(tekproje)
    set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
elseif(altproje)
    set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs")
endif()

#====================LIBS=============================================#
#=====================================================================#

# header only
add_library(baku INTERFACE)
target_include_directories(baku INTERFACE ${LIBS_DIR}/baku)

#=====================================================================#
#=====================================================================#

# supurge teknigi ile proje dosyalari MY_SOURCES icerisine atiliyor
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MY_SOURCES})

#=====================================================================#
#=====================================================================#

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${LIBS_DIR}
	
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    baku
)

target_compile_definitions(${PROJECT_NAME}  PUBLIC cmake_PROJECT_RES="${CMAKE_CURRENT_SOURCE_DIR}/res/")
