# @@@LICENSE
#
# Copyright (c) 2018 LG Electronics, Inc.
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)
project(aiservice)
SET(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -g -O3 -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC4)
webos_component(1 0 0)

include(FindPkgConfig)

# setup for linking necessary libraries
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${GLIB2_CFLAGS_OTHER})

pkg_check_modules(LUNASERVICE2 REQUIRED luna-service2)
include_directories(${LUNASERVICE2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${LUNASERVICE2_CFLAGS_OTHER})

pkg_check_modules(JSONC REQUIRED json-c)
include_directories(${JSONC_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${JSONC_CFLAGS_OTHER})

pkg_check_modules(PMLOGLIB REQUIRED PmLogLib)
include_directories(${PMLOGLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PMLOGLIB_CFLAGS_OTHER})

# add include files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/lunaApi)
include_directories(${CMAKE_SOURCE_DIR}/include/util)

# envirenment
set(BIN_NAME aiservice)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SRC_LIST
    ${SRC_DIR}/lunaApi/lunaApiBase.cpp
    ${SRC_DIR}/lunaApi/lunaApiFace.cpp
    ${SRC_DIR}/lunaApi/lunaApiGesture.cpp
    ${SRC_DIR}/lunaApi/lunaApiVoice.cpp
    ${SRC_DIR}/util/logging.cpp
    ${SRC_DIR}/main.cpp
)

# compile (create executable binary)
add_executable(${BIN_NAME} ${SRC_LIST})

# link
target_link_libraries(
    ${BIN_NAME}
    ${GLIB2_LDFLAGS}
    ${LUNASERVICE2_LDFLAGS}
    ${JSONC_LDFLAGS}
    ${PMLOGLIB_LDFLAGS}
)

# install
#webos_build_daemon()

# add dbus and lunaservice2 from  files/sysbus/*
webos_build_system_bus_files()
