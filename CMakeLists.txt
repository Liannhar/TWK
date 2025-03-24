cmake_minimum_required(VERSION 3.5)
project(TWK)
set(CMAKE_CXX_STANDARD 17)
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2-2.26.0")
list(APPEND CMAKE_PREFIX_PATH "${SDL2_PATH}")

set(SDL2_ttf_PATH "${CMAKE_SOURCE_DIR}/SDL2_ttf-2.24.0")
list(APPEND CMAKE_PREFIX_PATH "${SDL2_ttf_PATH}")

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Define source files
set(MY_FILES
        main.cpp
        Game/GameMode.cpp
        Figure/BaseFigure.cpp
        CoreTypes.h
        Figure/Rectangle.cpp
        Figure/Rectangle.h
        Figure/Circle.cpp
        Figure/Circle.h
        Figure/Triangle.cpp
        Figure/Triangle.h
        Buttons/Button.cpp
        Buttons/Button.h
        Random/Random.cpp
        Random/Random.h
)
add_executable(TWK ${MY_FILES})
target_link_libraries(TWK  PRIVATE ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf)
