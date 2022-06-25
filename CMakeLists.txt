cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME EasyGen)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Устанавливаем точные пути по которым будут сложены собраные файлы
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>$<0:>)

if(WIN32)
    # pdb files setup for release builds:
    include(MSVCMultipleProcessCompile) # Корректно подключает многопоточную сборку в MSVC
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " /Zi /O2 /Ot /GL")
    string(APPEND CMAKE_EXE_LINKER_FLAGS_RELEASE " /INCREMENTAL:NO /DEBUG /OPT:REF /LTCG")
    string(APPEND CMAKE_SHARED_LINKER_FLAGS_RELEASE " /INCREMENTAL:NO /DEBUG /OPT:REF")

    if(HIVE_USE_SANITIZER)
        string(APPEND CMAKE_CXX_FLAGS " /fsanitize=address")
    endif()
    add_definitions(-DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0602)

elseif (CMAKE_COMPILER_IS_GNUCXX OR MINGW OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wno-parentheses -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-unknown-pragmas -lpthread -ldl")
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " -g")

    if (NOT MINGW)
        string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fno-omit-frame-pointer")

        if(HIVE_USE_SANITIZER)
            # add address sanitazer check to debug build, and leave release build clean for check (for running under valgrind)
            string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
            string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address")
            string(APPEND CMAKE_SHARED_LINKER_FLAGS_DEBUG " -fsanitize=address")
        endif()
    endif()
endif()


add_definitions(-DBOOST_ALL_NO_LIB )

find_package(mstch CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem program_options)


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
Boost::program_options
)

#copy templates
foreach(_build_types ${CMAKE_CONFIGURATION_TYPES})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share/templates DESTINATION ${CMAKE_BINARY_DIR}/bin/${_build_types})
endforeach(_build_types)

#copy example config
foreach(_build_types ${CMAKE_CONFIGURATION_TYPES})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share/example/test.yaml DESTINATION ${CMAKE_BINARY_DIR}/bin/${_build_types})
endforeach(_build_types)