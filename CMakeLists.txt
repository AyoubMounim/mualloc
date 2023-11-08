
cmake_minimum_required(VERSION 3.25)

project(mualloc VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_library(${CMAKE_PROJECT_NAME} STATIC)

set(namespace mualloc)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/)

include(GNUInstallDirs)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/allocator.c
        ${PROJECT_SOURCE_DIR}/src/heap_allocator.c
        ${PROJECT_SOURCE_DIR}/src/static_allocator.c
        ${PROJECT_SOURCE_DIR}/src/stack_allocator.c
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/mu_allocator/allocator.h
    ${PROJECT_SOURCE_DIR}/include/mu_allocator/heap_allocator.h
    ${PROJECT_SOURCE_DIR}/include/mu_allocator/static_allocator.h
    ${PROJECT_SOURCE_DIR}/include/mu_allocator/stack_allocator.h
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT "${CMAKE_PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mu_allocator
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT "${CMAKE_PROJECT_NAME}Targets"
    FILE "${CMAKE_PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${CMAKE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
    DESTINATION cmake
)

export(EXPORT "${CMAKE_PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${CMAKE_PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
)

