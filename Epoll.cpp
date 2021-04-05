//
// Created by yb on 4/5/21.
//
#include "Epoll.h"

/*
* @Description: Epoll构造函数
* @Param: 事件最大数
* @return: 类指针
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
Epoll::Epoll() : _epollFd(::epoll_create(1024)), _events(1024) {
    assert(_epollFd >= 0);
}

/*
* @Description: Epoll析构函数
* @Param: 无
* @return:
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
Epoll::~Epoll() {
//    ::close(_epollFd);
}

/*
* @Description: 在文件描述符epollFd所引用的epoll实例上注册目标文件描述符fd，并将事件事件与内部文件链接到fd。
* @Param: 文件描述符，tcp句柄管理类，epoll events
* @return:添加结果
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Epoll::add(int fd, Tcptool *tool, int events) {
    struct epoll_event epollEvent;
    epollEvent.data.ptr = (void *) tool;
    epollEvent.events = events;

    int ret = ::epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &epollEvent);
    return ret;
}

/*
* @Description: 在文件描述符epollFd所引用的epoll实例上更改目标文件描述符fd，并将事件事件与内部文件更改链接到fd。
* @Param: 文件描述符，tcp句柄管理类，epoll events
* @return:更改结果
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Epoll::mod(int fd, Tcptool *tool, int events) {
    struct epoll_event epollEvent;
    epollEvent.data.ptr = (void *) tool;
    epollEvent.events = events;

    int ret = ::epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &epollEvent);
    return ret;
}

/*
* @Description: 在文件描述符epollFd所引用的epoll实例上删除目标文件描述符fd，并将事件事件与内部文件链接到fd删除。
* @Param: 文件描述符，tcp句柄管理类，epoll events
* @return:删除结果
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Epoll::del(int fd, Tcptool *tool, int events) {
    struct epoll_event epollEvent;
    epollEvent.data.ptr = (void *) tool;
    epollEvent.events = events;

    int ret = ::epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, &epollEvent);
    return ret;
}

/*
* @Description: 定时机制
* @Param: 超时事件
* @return: 剩余事件
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Epoll::wait(int timeouts) {
    int eventsNum = ::epoll_wait(_epollFd, &*_events.begin(), static_cast<int>(_events.size()), timeouts);
    return eventsNum;
}

/*
* @Description: 处理
* @Param: 监听获得的文件描述符，超时时间
* @return:
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
void Epoll::handleEvents(int listenFd, int eventsNum) {
    assert(eventsNum > 0);
    for (int i = 0; i < eventsNum; ++i) {
        Tcptool *tcptool = (Tcptool *) (_events[i].data.ptr);//原本转换成为void指针存进epoll事件队列，然后转成Tcptool型读取
        int fd = tcptool->getFd();
        if (fd == listenFd)
            _connectionCb();
        else if (_events[i].events & EPOLLIN)
            _readCb(tcptool);
        else if (_events[i].events & EPOLLOUT)
            _writeCb(tcptool);
    }
    return;
}
