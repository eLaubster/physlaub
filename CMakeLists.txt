cmake_minimum_required(VERSION 3.23)
project(physlaub)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES World.cpp physlaub.h Vec2D.cpp Vec2D.h Body.cpp Body.h Fixture.cpp Fixture.h Shape.cpp Shape.h CircleShape.cpp CircleShape.h RectShape.cpp RectShape.h)

add_library(physlaub ${SOURCE_FILES})
