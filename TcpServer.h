//
// Created by yb on 4/5/21.
//
#include <iostream>
#include "Tcptool.h"
#include "Epoll.h"
#include <memory>
#ifndef REACTOR_TCPSERVER_H
#define REACTOR_TCPSERVER_H
class TcpServer{
public:

    int createListenFd(int port) {
        int _listenFd = 0;
        _listenFd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        struct sockaddr_in _servAddr;
        port = ((port <= 1024) || (port >= 65536)) ? 6666 : port;
        ::memset(&_servAddr, 0, sizeof(_servAddr));
        _servAddr.sin_family = AF_INET;
        _servAddr.sin_port = ::htons((unsigned short)port);
        _servAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
        if ((::bind(_listenFd, (struct sockaddr *) &_servAddr, sizeof(_servAddr))) == -1){
            std::cout<<"listen error" <<std::endl;
            return -1;
        }
        if((::listen(_listenFd,5)) == -1){
            std::cout<<"listen error!"<<std::endl;
            return -1;
        }
        return _listenFd;
    }

public:
    TcpServer(int port):_port(port),
    _listenFd(createListenFd(_port)),
    _listenTool(new Tcptool(_listenFd)),
    _epoll(new Epoll()){
        assert(_listenFd>=0);
    }
    void run();

private:
    void _acceptConnection();
    void _closeConnection(Tcptool *tcptool);
    void _handleWrite(Tcptool *tcptool);
    void _handleRead(Tcptool *tcptool);

private:
    using EpollPtr = std::unique_ptr<Epoll>;
    using ListenTcpToolPtr = std::unique_ptr<Tcptool>;
private:
    int _port;
    int _listenFd;
    ListenTcpToolPtr _listenTool;
    EpollPtr _epoll;
};
#endif //REACTOR_TCPSERVER_H
