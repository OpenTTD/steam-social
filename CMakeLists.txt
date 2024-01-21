cmake_minimum_required(VERSION 3.16)

project(steam-social
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15)

include(RPath)
include(CompileFlags)

add_library(${PROJECT_NAME} SHARED
    src/plugin.cpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)

if(WIN32)
    if ("$ENV{Platform}" STREQUAL "arm64")
        message(FATAL_ERROR "Windows ARM64 is (currently) not supported by the Steamworks SDK")
    else()
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/win64)
            target_link_libraries(${PROJECT_NAME} PRIVATE steam_api64)
            set(LIBRARY_DEPENDENCY ${CMAKE_SOURCE_DIR}/lib/win64/steam_api64.dll)
            install(FILES ${LIBRARY_DEPENDENCY} DESTINATION .)
            target_sources(${PROJECT_NAME} PRIVATE os/windows/library_win64.manifest)
        else()
            target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/win32)
            target_link_libraries(${PROJECT_NAME} PRIVATE steam_api)
            set(LIBRARY_DEPENDENCY ${CMAKE_SOURCE_DIR}/lib/win32/steam_api.dll)
            install(FILES ${LIBRARY_DEPENDENCY} DESTINATION .)
            target_sources(${PROJECT_NAME} PRIVATE os/windows/library_win32.manifest)
        endif()
    endif()
elseif(APPLE)
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/osx)
    target_link_libraries(${PROJECT_NAME} PRIVATE steam_api)
    set(LIBRARY_DEPENDENCY ${CMAKE_SOURCE_DIR}/lib/osx/libsteam_api.dylib)
    install(FILES ${LIBRARY_DEPENDENCY} DESTINATION .)
else()
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux64)
    target_link_libraries(${PROJECT_NAME} PRIVATE steam_api)
    set(LIBRARY_DEPENDENCY ${CMAKE_SOURCE_DIR}/lib/linux64/libsteam_api.so)
    install(FILES ${LIBRARY_DEPENDENCY} DESTINATION .)
endif()

include(Version)
include(InstallAndPackage)
