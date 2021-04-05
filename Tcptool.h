//
// Created by yb on 4/5/21.
//

#ifndef REACTOR_TCPTOOL_H
#define REACTOR_TCPTOOL_H
#include <sys/socket.h>
#include <iostream>
#include "assert.h"
#include <string.h>
#include <string>
/*
* @Description: reactor
* @Param:
* @return:
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/

/*
* @Description: 管理tcp连接句柄的类
* @Param:
* @return:
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
class Tcptool{
public:
    Tcptool(int fd):_fd(fd){
        assert(_fd>=0);
    }
    ~Tcptool(){}
public:
    int getFd(){return _fd;}
    int read();
    int write();
private:
    int _fd;
};
#endif //REACTOR_TCPTOOL_H
