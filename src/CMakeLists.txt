
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(Qwt_DIR /usr/local/qwt-6.1.3/)

include_directories(${CMAKE_SOURCE_DIR}/asterix
    ${CMAKE_SOURCE_DIR}/assessment
    ${CMAKE_SOURCE_DIR}/db
    ${CMAKE_BINARY_DIR}/src)

include_directories(../CuteReport-1.3.2-lgpl/cutereport_resources/include)
include_directories(${Qwt_DIR}/include)

find_package(Qt5 COMPONENTS Widgets Network Charts REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(PROTOCOL REQUIRED libmsprotocol)

aux_source_directory(. SRC_SOURCES)

add_definitions(-DHAVE_GITVERSION_H)
add_executable(showidea ${SRC_SOURCES})

add_custom_target(gitversion.h
  ${CMAKE_SOURCE_DIR}/src/version.sh
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src VERBATIM)

target_link_libraries(showidea Qt5::Widgets Qt5::Network Qt5::Charts)

target_include_directories(showidea PUBLIC ${PROTOCOL_INCLUDE_DIRS})
target_link_libraries(showidea ${PROTOCOL_LIBRARIES})

add_dependencies(showidea gitversion.h)

