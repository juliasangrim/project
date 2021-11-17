cmake_minimum_required(VERSION 3.16)
project(layout_domino)

set(CMAKE_CXX_STANDARD 17)

add_executable(layout_domino main.cpp field/Field.cpp field/Field.h runner/Runner.cpp runner/Runner.h cell/Cell.h template/Template.cpp template/Template.h)
