# Copyright 2020 Hal@shurabaP.  All rights reserved.
# Use of this source code is governed by a MIT style
# license that can be found in the LICENSE file.
cmake_minimum_required(VERSION 3.9)
project(uzume_utau)

add_library(uzume_utau STATIC)
target_compile_features(uzume_utau
        PRIVATE
        cxx_std_11)
target_compile_options(uzume_utau
        PRIVATE
        -Wall -Wextra -Wno-long-long -pedantic)
target_sources(uzume_utau
        PRIVATE
        Affix.cpp
        Character.cpp
        Voicebank.cpp
        WaveLabel.cpp)
set_property(TARGET uzume_utau
        PROPERTY PUBLIC_HEADER
        Affix.hpp
        Character.hpp
        Voicebank.hpp
        WaveLabel.hpp)
target_include_directories(uzume_utau
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>)
install(TARGETS uzume_utau
        EXPORT libuzume_utau
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
