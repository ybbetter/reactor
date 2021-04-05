#include "Tcptool.h"

/*
* @Description: 从socket句柄中读取数据
* @Param: 无
* @return: 返回从socket文件描述符中读取的字符个数
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Tcptool::read() {
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    int ret=recv(_fd,buffer, sizeof(buffer),0);
    if (ret==0)
        std::cout << "断开连接 ！" <<std::endl;
    else if (ret>0)
        std::cout << "read from socket ：" << buffer <<std::endl;
    else if (ret<0){
        std::cout << "recv error " << std::endl;
//        std::cout<<stderr<<std::endl;
    }
    return ret;
}
/*
* @Description: 通过socket句柄发送数据
* @Param: 无
* @return: 写入缓冲区的字符个数
* @data: 4/5/21
* @author: Bin Yin
* @version:
*/
int Tcptool::write() {
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    const char * str="This is yb server";
    memcpy(buffer,str, sizeof(str));
    int ret=send(_fd,buffer,sizeof(buffer),0);
    if (ret>0)
        std::cout<<"发送成功 "<<std::endl;
    else if(ret==-1)
        std::cout<<"发送失败" <<std::endl;
    return ret;
}

