cmake_minimum_required(VERSION 3.17)
project(reactor)

set(CMAKE_CXX_STANDARD 14)

add_executable(reactor Tcptool.cpp Epoll.cpp Epoll.h TcpServer.cpp TcpServer.h)