cmake_minimum_required(VERSION 3.30)
project(untitled C)

set(CMAKE_C_STANDARD 90)

add_executable(untitled part1.c
        part2.c
        phypages.c
        pagetable.c)
