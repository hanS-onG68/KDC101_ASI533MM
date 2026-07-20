#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "server.h"
#include "tlmc_func.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

// 保障函数：循环发送，确保所有数据都被送出
int send_all(SOCKET sock, const char *buf, int len) {
    int total_sent = 0;
    int bytes_sent;
    
    while (total_sent < len) {
        bytes_sent = send(sock, buf + total_sent, len - total_sent, 0);
        if (bytes_sent <= 0) {
            if (bytes_sent == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) {
                // 非阻塞模式下缓冲区满，可稍后重试
                continue;
            }
            return -1; // 出错或连接关闭
        }
        total_sent += bytes_sent;
    }
    return total_sent;
}

// 保障函数：循环接收，确保收满指定长度的数据
int recv_all(SOCKET sock, char *buf, int len) {
    int total_received = 0;
    int bytes_received;
    
    while (total_received < len) {
        bytes_received = recv(sock, buf + total_received, len - total_received, 0);
        if (bytes_received <= 0) {
            if (bytes_received == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) {
                // 非阻塞模式下无数据，可稍后重试
                continue;
            }
            return -1; // 出错或连接关闭
        }
        total_received += bytes_received;
    }
    return total_received;
}

void HandleClient(SOCKET clientSocket) {
    printf("Client connected. Socket: %llu\n", clientSocket);
    
    int32_t receivedNumber;
    int32_t responseNumber;
    char buffer[4]; // 用于收发4字节的整数
    
    // while (1) {
        // 1. 接收整数 (4字节)
        if (recv_all(clientSocket, buffer, 4) != 4) {
            printf("[Fail]Receive failed or connection closed. Socket: %llu\n", clientSocket);
            // break;
        }
        
        // 2. 将网络字节序转换为主机字节序，得到真正的整数
        memcpy(&receivedNumber, buffer, 4);
        receivedNumber = ntohl(receivedNumber);
        
        printf("[Success]Server received from client %llu: %d\n", clientSocket, receivedNumber);
        
        // 3. 业务处理
        printf("[Success]Server sending response: %d\n", receivedNumber);
        int res = TlmcCtrl(receivedNumber);

        
        // 4. 将响应转换为网络字节序
        responseNumber = htonl(res);
        memcpy(buffer, &responseNumber, 4);
        
        // 5. 发送响应整数 (4字节)
        if (send_all(clientSocket, buffer, 4) != 4) {
            printf("[Fail]Server send failed. Socket: %llu\n", clientSocket);
            // break;
        }
        
        // 简单协议：如果客户端发送0，则结束会话
        if (receivedNumber == 0) {
            printf("Client %llu requested to end session.\n", clientSocket);
            // break;
        }
    // }
}

int Server() {
    WSADATA wsaData;
    int result;

    // 初始化 Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *resultPtr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;       // Use IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol
    hints.ai_flags = AI_PASSIVE;     // Bind to any available IP address

    // Resolve the local address and port to be used by the server
    result = getaddrinfo("127.0.0.1", "8080", &hints, &resultPtr);  // 获取一个符合 IPv4、TCP 协议要求，且适用于在所有网络接口（0.0.0.0）的 8080 端口上进行绑定操作的地址信息结构。
    if (result != 0) {
        printf("getaddrinfo failed: %d\n", result);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(resultPtr->ai_family, resultPtr->ai_socktype, resultPtr->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(resultPtr);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    result = bind(ListenSocket, resultPtr->ai_addr, (int)resultPtr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(resultPtr);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(resultPtr);

    // Listen for incoming connections
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    HandleClient(ClientSocket);

    // Cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}