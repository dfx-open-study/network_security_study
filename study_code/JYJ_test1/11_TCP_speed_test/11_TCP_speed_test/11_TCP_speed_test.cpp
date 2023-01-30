#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32")
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

//TCP �ӵ� �׽�Ʈ Ŭ���̾�Ʈ �����

//#define SERVERIP L"20.214.110.87"
#define SERVERIP L"127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

int main()
{
    int retval;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    printf("WSAStartup() ����!\n");

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //���� ����   SOCK_STREAM : TCP Ÿ���� ����

    if (sock == INVALID_SOCKET)
        return 1;

    //connect
    SOCKADDR_IN serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));     //0���� �ʱ�ȭ
    serveraddr.sin_family = AF_INET;     //IPv4
    serveraddr.sin_port = htons(SERVERPORT);   //��Ʈ �Ҵ� 
    InetPton(AF_INET, SERVERIP, &serveraddr.sin_addr);

    retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));  //server�� ����

    if (retval == SOCKET_ERROR)
        return 1;

    printf("connect ����!\n");

    //1�ʿ� 1���� ���� ��Ŷ�� ũ�� LOG ���
    //��Ŷ �����ʹ� ���ϴ� ������ �ƹ��ų� ������ ��
    //��� public IP�ּҷ� send �׽�Ʈ ���� 
    char buf[BUFSIZE + 1] = "Message from Client";
    unsigned long long privtick;
    unsigned long long nowtick;
    unsigned int send_size;
    unsigned int total_size = 0;
    unsigned int count = 0;

    privtick = GetTickCount64();

    while (1)
    {
        send_size = send(sock, buf, BUFSIZE, 0);

        if (send_size > 0) 
        {
            count++;
        }
        total_size += send_size;

        nowtick = GetTickCount64();

        if (nowtick - privtick >= 1000)
        {
            //printf("�޽����� �����ϴ�.\n");
            printf("%d Mbyte %d Time\n", total_size / 1024 / 1024, count);
            total_size = 0;
            count = 0;
            privtick = GetTickCount64();
        }
    }

    closesocket(sock);  
    WSACleanup();   //winsock end
    return 0;
}