#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "client.h"
#include <iostream>
#include <cmath>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

// int GetInput(int *inputNum)
// {
//     char buffer[100]; // 一个足够大的输入缓冲区

//     printf("Please enter your degrees data(tips:10000 == 5.2093 degrees): ");
//     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//         // 成功读取一行，现在尝试从这行字符串中解析数据
//         if (sscanf(buffer, "%d %f", inputNum) != 1) {
//             printf("[Error][%s]Invalid input format!\n", __func__);
//             return 1;
//         }
//         printf("[Success][%s]input data: %d\n", __func__, *inputNum);
//     }
//     return 0;
// }

// 保障函数：循环发送
int ClientSendAll(SOCKET sock, const char *buf, int len)
{
    int total_sent = 0;
    int bytes_sent;
    
    while (total_sent < len) {
        bytes_sent = send(sock, buf + total_sent, len - total_sent, 0);
        if (bytes_sent <= 0) {
            return -1;
        }
        total_sent += bytes_sent;
    }
    return total_sent;
}

// 保障函数：循环接收
int ClientRecvAll(SOCKET sock, char *buf, int len)
{
    int total_received = 0;
    int bytes_received;
    
    while (total_received < len) {
        bytes_received = recv(sock, buf + total_received, len - total_received, 0);
        if (bytes_received == SOCKET_ERROR) {
            printf("recv failed: %d\n", WSAGetLastError());
            return -1;
        } else if (bytes_received == 0) {
            printf("Connection closed by peer. Total bytes received: %d\n", total_received);
            return -1;
        }
        total_received += bytes_received;
    }
    return total_received;
}

/* WSAStartup -> (getaddrinfo) -> socket -> connect -> send/recv -> closesocket -> WSACleanup */
int Client(double *inputNum) {
    WSADATA wsaData;

    // 初始化Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("[Fail]WSAStartup failed: %d\n", result);
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo hints;

    // 配置地址信息
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol

    struct addrinfo *resultPtr = NULL;  // 用于接收函数返回的结果链表。使用完毕后，必须调用 freeaddrinfo() 释放该链表
    // 解析服务器地址和端口
    result = getaddrinfo("127.0.0.1", "8080", &hints, &resultPtr);
    if (result != 0) {
        printf("[Fail]getaddrinfo failed: %d\n", result);
        WSACleanup();
        return 1;
    }

    // 遍历 getaddrinfo 返回的所有可能地址，直到连接成功。这是连接冗余的良好实践。
    for(struct addrinfo *ptr = resultPtr; ptr != NULL; ptr = ptr->ai_next) {
        // 创建套接字
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("[Fail]Error at socket(): %d\n", WSAGetLastError());
            freeaddrinfo(resultPtr);
            WSACleanup();
            return 1;
        }

        //  连接到服务器
        result = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;  // 连接成功
    }
    freeaddrinfo(resultPtr);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("[Fail]Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    printf("[Success]Connected to server\n");

    char buffer[BUFFER_SIZE] = {0};

    // 主收发循环
    // while (1) {
        int response_number;

        // 1.用户输入获取整数
        // GetInput(&number_to_send);
        double temp = (*inputNum) * 1919.6450;  // 输入的角度值inputNum转换成步进电机的脉冲数
        int number_to_send = static_cast<int>(std::round(temp)); 
        printf("[Info]number_to_send = %d\n", number_to_send);

        // 2. 转换为网络字节序并准备发送
        int network_number = htonl(number_to_send);
        memcpy(buffer, &network_number, 4);
        
        // 3. 发送整数 (4字节)
        if (ClientSendAll(ConnectSocket, buffer, 4) != 4) {
            printf("[Fail]Clilent send data failed.\n");
            // break;
        }
        
        printf("[Success]Client send to Server, data: %d\n", number_to_send);
        
        // 4. 接收服务端响应 (4字节)
        if (ClientRecvAll(ConnectSocket, buffer, 4) != 4) {
            printf("[Fail]Client receive data from Server failed.\n");
            //break;
        }
        
        // 5. 将网络字节序转换为主机字节序
        memcpy(&response_number, buffer, 4);
        response_number = ntohl(response_number);
        
        printf("[Success]Response from Server: %d, KDC101 control is %s\n", response_number, response_number ? "Fail" : "Success");
        
        // 6. 简单协议：如果客户端发送0，则结束会话
        if (number_to_send == 0) {
            printf("Ending session.\n");
            //break;
        }
    //}

    // Cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
