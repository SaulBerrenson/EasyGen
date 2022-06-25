cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME EasyGen)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Устанавливаем точные пути по которым будут сложены собраные файлы
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>$<0:>)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>$<0:>)


add_definitions(-DBOOST_ALL_NO_LIB )

find_package(mstch CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)


FILE(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/easygen/*.hpp)
FILE(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
${HPP_FILES} 
${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/easygen
${CMAKE_CURRENT_SOURCE_DIR}/easygen/generators
)
target_link_libraries(${PROJECT_NAME}
mstch::mstch
yaml-cpp
Boost::boost
Boost::filesystem
)

#copy templates
foreach(_build_types ${CMAKE_CONFIGURATION_TYPES})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share/templates DESTINATION ${CMAKE_BINARY_DIR}/bin/${_build_types})
endforeach(_build_types)

