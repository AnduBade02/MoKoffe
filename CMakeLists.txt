cmake_minimum_required(VERSION 3.31)
project(MoKoffe)

set(CMAKE_CXX_STANDARD 17)

add_executable(MoKoffe main.cpp
        GestionareAngajati.h
        GestionareAngajati.cpp
        GestionareProduse.h
        GestionareProduse.cpp
        GestionareFinante.h
        GestionareFinante.cpp)
