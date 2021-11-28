cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. You can search the web about performing out-source builds with CMake.")
endif()

cmake_policy(SET CMP0074 NEW)

project(bmets VERSION 0.1)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
endif()
add_compile_definitions(UNICODE _UNICODE)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
add_executable(bmets ${SRC_FILES})

# Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Antlr
set(ANTLR4_WITH_STATIC_CRT OFF)
include(ExternalAntlr4Cpp)
find_package(ANTLR REQUIRED)
include_directories(${ANTLR4_INCLUDE_DIRS})
antlr_target(BveMapLexer ${CMAKE_SOURCE_DIR}/src/parser/BveMapLexer.g4 LEXER PACKAGE bmets::parser)
antlr_target(BveMapParser ${CMAKE_SOURCE_DIR}/src/parser/BveMapParser.g4 PARSER PACKAGE bmets::parser
    DEPENDS_ANTLR BveMapLexer COMPILE_FLAGS -lib ${ANTLR_BveMapLexer_OUTPUT_DIR} VISITOR)
target_sources(bmets PUBLIC ${ANTLR_BveMapLexer_CXX_OUTPUTS} ${ANTLR_BveMapParser_CXX_OUTPUTS})
include_directories(${ANTLR_BveMapLexer_OUTPUT_DIR})
include_directories(${ANTLR_BveMapParser_OUTPUT_DIR})
target_link_libraries(bmets antlr4_shared)
add_custom_command(TARGET bmets POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${ANTLR4_RUNTIME_LIBRARIES} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Iconv
if(MSVC)
    set(BUILD_EXECUTABLE OFF CACHE BOOL "Don't build Win-Iconv executable" FORCE)
    add_subdirectory(lib/win-iconv)
    include_directories(./lib/win-iconv)
    target_link_libraries(bmets iconv)
else()
    find_package(Iconv REQUIRED)
    include_directories(${Iconv_INCLUDE_DIRS})
    target_link_libraries(bmets ${Iconv_LIBRARIES})
endif()

# Glfw
find_package(glfw3 REQUIRED)
target_link_libraries(bmets glfw)

# Glad
add_subdirectory(lib/glad)
include_directories(./lib/glad/include)
target_link_libraries(bmets glad)

# OpenGL
if(MSVC)
    target_link_libraries(bmets opengl32)
else()
    target_link_libraries(bmets GL GLU)
endif()

# STB
include_directories(./lib/stb)

# ImGui
add_subdirectory(lib/imgui)
include_directories(./lib/imgui)
target_link_libraries(bmets imgui)

# Assimp
find_package(assimp REQUIRED)
link_directories(${ASSIMP_LIBRARY_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})
target_link_libraries(bmets ${ASSIMP_LIBRARIES})

# External assets
add_custom_command(TARGET bmets POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)