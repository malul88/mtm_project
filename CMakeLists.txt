cmake_minimum_required(VERSION 3.16)
project(Gcalc)

set(CMAKE_CXX_STANDARD 11)

add_executable(Gcalc main.cpp Graph.cpp Graph.h Vertex.cpp Vertex.h Edges.cpp Edges.h Gcalc.cpp Gcalc.h Parser.cpp Parser.h Exeptions.cpp Exeptions.h)