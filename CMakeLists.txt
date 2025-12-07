cmake_minimum_required(VERSION 3.16)
project(GhsotSpace VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()



set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})
list(PREPEND CMAKE_PREFIX_PATH 
"D:/GameDevelopmentLibrary/SDL3_3.3.3/build"
"D:/GameDevelopmentLibrary/SDL3_image-3.2.4/cmake"
"D:/GameDevelopmentLibrary/SDL_mixer-3.0.0/build"
"D:/GameDevelopmentLibrary/SDL3_ttf-3.2.2/cmake"
"D:/GameDevelopmentLibrary/glm-1.0.2/build"
)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)



if(WIN32)
    list(APPEND SOURCES resources.rc)
endif()
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/**/*.cpp
    src/*.h
    src/**/*.h
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
    ${SDL3_LIBRARIES}
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)
