// ServerSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <Winsock2.h>

#pragma comment(lib,"ws2_32.lib")


int main()
{
	WSADATA wsaData;
	SOCKET socketServer;
	SOCKADDR_IN addrServer;
	SOCKET sockClient;
	SOCKADDR_IN addrClient;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);
	bind(socketServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	//Listen监听端
	listen(socketServer, 20);//20为等待连接数目
	printf("服务器已启动：\n监听中...\n");
	int len = sizeof(SOCKADDR);
	char sendBuf[100];
	char recvBuf[100];
	//阻塞进程，直到有客户端连接上来为止
	sockClient = accept(socketServer, (SOCKADDR*)&addrClient, &len);
	//接收并打印客户端数据
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

	char message[20] = "Hello Client!";
	send(sockClient, message, strlen(message) + 1, 0);
	//关闭socket
	closesocket(sockClient);
	closesocket(socketServer);
	WSACleanup();
	return 0;
}

