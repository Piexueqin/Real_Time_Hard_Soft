#ifndef NETWORK_H
#define NETWORK_H

#include<iostream>
using namespace std;

#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "../course_d/include/print_debug_information.h"

#define  File_Name_Size 128
struct file_attr
{	
	char File_Name[File_Name_Size];
    int File_Size;
};

struct Send_Ctrl_Info //上位指令控制信息
{
    unsigned int key;
    unsigned int value;
};

//TCP服务器类
class MyServerTCP
{
private:
    int domain;
    int server_fd;      //服务器套接字
    int client_fd;      //客户端套接字

public:
    bool bAcceptFlag;  //判断是不是第一次连接

    /*************************************
     * 函数名：           MyServerTCP
     * 函数作用：         初始化参数
     * AF_INET：         IPV4的协议
     * SOCK_STREAM：     指定TCP协议
     * 0：               代表不变化协议内部（ip手册中指定的参数）
     **************************************/
    MyServerTCP();
    ~MyServerTCP();

    //tcp socket
    bool MySocket(int dom = AF_INET, int ty = SOCK_STREAM, int pro = 0);
    
    bool CloseServerFd();
    
    bool CloseClientFd();

    //绑定 默认端口号为6000
    bool MyBind(uint16_t  port=6000);

    //地址复用
    bool MySetsockopt();

    //监听
    bool MyListen(int backlog=10);
    //等待连接
    bool MyAccept();

    //MyRead 返回-1 数据异常  、返回 0 代表客户端断开连接 、返回正常、读取到的字节数
    ssize_t MyRead(void *buffer,size_t buflen) ;

    //发送数据 返回write 的返回值
    ssize_t MyWrite(void *buffer,size_t buflen);

    //接收数据  传入参数 文件名，文件大小
    bool ReceiveFile(const char *fileName,int File_Size);

    bool MyWrite(string data);

    bool MyReadSizeData(void *buff, size_t buflen);
    
};

//解压文件到到指定的位置
int uncompressFile(char *fileName,char *file_path);
#endif
