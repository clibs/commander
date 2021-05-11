cmake_minimum_required(VERSION 2.8)
project(commander)
aux_source_directory(${PROJECT_SOURCE_DIR}/src commander_source)
add_library(commander SHARED ${commander_source})