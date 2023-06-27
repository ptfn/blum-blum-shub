cmake_minimum_required(VERSION 3.22.1)
project(blum-blum-shub)

ADD_LIBRARY(BBSLib STATIC src/bbs.c)

SET(APP main)

ADD_EXECUTABLE(${APP} src/main.c) 

TARGET_LINK_LIBRARIES(${APP} BBSLib)
TARGET_LINK_LIBRARIES(${APP} m)