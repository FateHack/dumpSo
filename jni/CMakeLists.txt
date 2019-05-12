cmake_minimum_required(VERSION 3.13)
project(jni)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(jni
        Android.mk
        Application.mk
        Log.cpp
        Log.h
        Main.cpp
        Main.h
        public.cpp
        public.h)
