//
// Created by yb on 4/5/21.
//
#include <sys/epoll.h>
#include "Tcptool.h"
#include <iostream>
#include <functional>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifndef REACTOR_EPOLL_H
#define REACTOR_EPOLL_H
class Epoll{
public:
    Epoll();
    ~Epoll();
    using NewconnectionCallback=std::function<void()>;
    using HandleReadCallback=std::function<void(Tcptool*)>;
    using HandleWriteCallback=std::function<void(Tcptool*)>;
    using CloseConnectionCallback = std::function<void(Tcptool*)>;
    int add(int fd,Tcptool* tool,int events);
    int mod(int fd,Tcptool* tool,int events);
    int del(int fd,Tcptool* tool,int events);
    int wait(int timeouts);

    void handleEvents(int listenFd,int eventsNum);

    void setNewConnection(const NewconnectionCallback &cb){
        _connectionCb=cb;
    }
    void setCloseConnection(const CloseConnectionCallback &cb){
        _closeCb=cb;
    }
    void setWriteCb(const HandleWriteCallback &cb){
        _writeCb=cb;
    }
    void setReadCb(const HandleReadCallback &cb){
        _readCb=cb;
    }
private:
    using eventList=std::vector<struct epoll_event>;
    int _epollFd;
    eventList _events;//一次epoll_wait调用返回的活动fd列表，大小自适应
    NewconnectionCallback _connectionCb;
    HandleReadCallback _readCb;
    HandleWriteCallback _writeCb;
    CloseConnectionCallback _closeCb;
};
#endif //REACTOR_EPOLL_H
