
#include "../include/network.h"
#include <netinet/tcp.h> //TCP_NODELAY
#include "../course_d/include/print_debug_information.h"

MyServerTCP::MyServerTCP()
{
    server_fd = -1;
    client_fd = -1;
    bAcceptFlag = false;
    domain = 0;
}

MyServerTCP::~MyServerTCP()
{
    if (!CloseServerFd())
    {
        PRINTF_ERR_MESSAGE("close server_fd error!");
    }
    if (!CloseClientFd())
    {
        PRINTF_ERR_MESSAGE("close server_fd error!");
    }
    server_fd = -1;
    client_fd = -1;
    bAcceptFlag = false;
    domain = 0;
}

bool MyServerTCP::MySocket(int domain, int type, int protocol)
{
    this->domain = domain;
    server_fd = socket(domain, type, protocol);
    if (server_fd == -1)
    {
        PRINTF_ERR_MESSAGE("socket error !");
        return false;
    }
    return true;
}

bool MyServerTCP::CloseServerFd()
{
    if( -1 == close(server_fd))
    {
        return false;
    }
    return true;
}

bool MyServerTCP::CloseClientFd()
{
    if( -1 == close(client_fd))
    {
        return false;
    }
    return true;
}

bool  MyServerTCP::MyBind(uint16_t port)
{
    struct sockaddr_in native_addr;
    native_addr.sin_family = domain;//指定引用IPV4的协议
    native_addr.sin_port = htons(port);//指定端口号
    native_addr.sin_addr.s_addr = htonl(INADDR_ANY);//将所有的IP地址转化为二进制的网络字节序的数据进行绑定,自动获取ip地址

    if (-1 == bind(server_fd, (struct sockaddr *)&native_addr, sizeof(native_addr)))
    {
        PRINTF_ERR_MESSAGE("bind error!");
        return false;
    }
    return true;
}

bool MyServerTCP::MySetsockopt() //地址复用
{
    int opt=1;
    int ret=0;
    //地址复用
    ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    if (ret < 0)
    {
        PRINTF_ERR_MESSAGE("setsockopt error!");
        return false;
    }

    int on = 1;
    //设置 TCP 通信实时性
    ret = setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(int));
    //ret = setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(int));
    if (ret < 0)
    {
        PRINTF_ERR_MESSAGE("setsockopt error!");
        return false;
    }
    return true;
}

bool MyServerTCP::MyListen(int backlog)
{
    if(-1 == listen(server_fd, backlog))
    {
        PRINTF_ERR_MESSAGE("listen error");
        return false;
    }
    return true;
}

bool MyServerTCP::MyAccept()
{
    /**************************
     * accept
     * 等待客户端链接，链接成功后返回一个代表客户端通信的文件描述符,具备阻塞特性
     * skt_fd：代表套接字接口
     * client_addr：链接成功后客户端的地址信息会存放到这里面
     * sklen：代表结构体的长度
     **************************/
    struct sockaddr_in client_addr;
    socklen_t  addrlen = sizeof(sockaddr_in);
    memset(&client_addr, 0, addrlen);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
    if (-1 == client_fd)
    {
        PRINTF_ERR_MESSAGE("accept error");
        return false;
    }
    std::printf("服务器：客户端连接成功\n");
    std::printf("客户端信息：\n客户端IP为%s，端口号为%hu\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return true;
}

//MyRead 返回-1 数据异常  、返回 0 代表客户端断开连接 、返回正常、读取到的字节数
ssize_t MyServerTCP::MyRead(void *buffer, size_t buflen)
{
    ssize_t recv_size;
    recv_size = read(client_fd, buffer, buflen);
    if (recv_size == -1)
    {
        PRINTF_ERR_MESSAGE("接受数据异常");
    }
    return 	recv_size;
}
ssize_t MyServerTCP::MyWrite(void *buffer, size_t buflen)
{
    int recv_size;
    recv_size = write(client_fd, buffer, buflen);
    if ( -1 == recv_size)
    {
        PRINTF_ERR_MESSAGE("write error!");
    }
    return recv_size;
}

//接收文件
bool MyServerTCP::ReceiveFile(const char *fileName, int File_Size)
{
    char buff[8192];
    int fd;
    int Sum_Receive_Size = 0;
    fd = open(fileName, O_RDWR| O_CREAT| O_TRUNC, 0644);//打开文件
    if ( fd < 0 )
    {
        PRINTF_ERR_MESSAGE("open error!");
        return false;
    }

    while(1)
    {
        int Receive_Size = 0;
        memset(buff, 0, 8192);
        Receive_Size = read(client_fd, buff, 8192);//从tcp中获取文件内容
        if (-1 == Receive_Size)
        {
            PRINTF_ERR_MESSAGE("read error!");
            return false;
        }
        cout << "Receive_Size=" << Receive_Size <<endl;
        write(fd,buff,Receive_Size);//将内容写进文件中

        Sum_Receive_Size += Receive_Size;
        cout << "Sum_Receive_Size=" << Sum_Receive_Size<<endl;
        if (Sum_Receive_Size == File_Size)
        {
            break;
        }
        else if(Sum_Receive_Size>File_Size)
        {
         return false;
        }

    }
    if(-1 == close(fd))
    {
        PRINTF_ERR_MESSAGE("close error!");
    }
    return true;
}

bool MyServerTCP::MyWrite(string data)
{
    if (-1 != server_fd)
    {
        size_t len = data.length();
        if (write(client_fd, data.c_str(), len) <0)
        {
             PRINTF_ERR_MESSAGE("send failed !");
             return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool MyServerTCP::MyReadSizeData(void *buff, size_t buflen)
{
    size_t recv_size = 0;
    size_t recv_size_sum = 0;
    size_t pre_recv_size = 0;
    char *recv_buf = (char *)malloc(buflen);
    char *recv_buf_sum = (char *)malloc(buflen);

    for(;;)
    {
        recv_size = read(client_fd, recv_buf, buflen-recv_size);
        std::printf("read size == %ld\n",recv_size);
        if(recv_size == 0 || recv_size == -1)
        {
            PRINTF_ERR_MESSAGE("read fail");
            free(recv_buf);
            free(recv_buf_sum);
            return false;
        }

        recv_size_sum += recv_size;

        size_t i;
        for (i = 0; i < recv_size; i++)
        {
            recv_buf_sum[i + pre_recv_size] = recv_buf[i];
        }

        if(recv_size_sum == buflen || recv_size_sum == 0)
        {
            break;
        }
        else
        {
            pre_recv_size = recv_size;
        }
    }

    memcpy(buff,recv_buf_sum,buflen);

    free(recv_buf);
    free(recv_buf_sum);

    return true;
}



int uncompressFile(char *fileName, char *file_path)
{
    char cmdBuf[128] = {0};
    sprintf(cmdBuf,"mv %s %s", fileName, file_path);
    system(cmdBuf);
    memset(cmdBuf, 0, sizeof (cmdBuf));
    sprintf(cmdBuf, "cd %s &&tar -xf %s/%s &&rm %s/%s", file_path, file_path, fileName, file_path, fileName);
    system(cmdBuf);  
}
