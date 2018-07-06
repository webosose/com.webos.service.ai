# @@@LICENSE
#
# Copyright (c) 2018 LG Electronics, Inc.
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)
project(aiservice)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC4)
webos_component(1 0 0)
webos_include_install_paths()

include(FindPkgConfig)

# setup for linking necessary libraries
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(JSONC REQUIRED json-c)
pkg_check_modules(LUNASERVICE2 REQUIRED luna-service2)
pkg_check_modules(PMLOGLIB REQUIRED PmLogLib)
pkg_check_modules(GOOGLEASSISTANT REQUIRED googleassistant)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -g -O3 -fpermissive ${GLIB2_CFLAGS_OTHER} ${JSONC_CFLAGS_OTHER} ${LUNASERVICE2_CFLAGS_OTHER} ${PMLOGLIB_CFLAGS_OTHER} ${GOOGLEASSISTANT_CFLAGS_OTHER}")

# add include files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/lunaApi
    ${CMAKE_SOURCE_DIR}/include/util
    ${GLIB2_INCLUDE_DIRS}
    ${JSONC_INCLUDE_DIRS}
    ${LUNASERVICE2_INCLUDE_DIRS}
    ${PMLOGLIB_INCLUDE_DIRS}
    ${GOOGLEASSISTANT_INCLUDE_DIRS}
)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(SRC_LIST
    ${SRC_DIR}/lunaApi/lunaApiBase.cpp
    ${SRC_DIR}/lunaApi/lunaApiFace.cpp
    ${SRC_DIR}/lunaApi/lunaApiGesture.cpp
    ${SRC_DIR}/lunaApi/lunaApiVoice.cpp
    ${SRC_DIR}/util/logging.cpp
    ${SRC_DIR}/main.cpp
)

# create excutable file
set(BIN_NAME aiservice)
add_executable(${BIN_NAME} ${SRC_LIST})

# link
target_link_libraries(
    ${BIN_NAME}
    ${GLIB2_LDFLAGS}
    ${LUNASERVICE2_LDFLAGS}
    ${JSONC_LDFLAGS}
    ${PMLOGLIB_LDFLAGS}
    ${GOOGLEASSISTANT_LDFLAGS}
)

# install
install(TARGETS ${BIN_NAME} DESTINATION ${WEBOS_INSTALL_SBINDIR})

# add dbus and lunaservice2 from  files/sysbus/*
webos_build_system_bus_files()
