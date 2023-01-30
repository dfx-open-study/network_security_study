#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32")
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

//TCP 속도 테스트 클라이언트 만들기

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

    printf("WSAStartup() 성공!\n");

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //소켓 생성   SOCK_STREAM : TCP 타입의 소켓

    if (sock == INVALID_SOCKET)
        return 1;

    //connect
    SOCKADDR_IN serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));     //0으로 초기화
    serveraddr.sin_family = AF_INET;     //IPv4
    serveraddr.sin_port = htons(SERVERPORT);   //포트 할당 
    InetPton(AF_INET, SERVERIP, &serveraddr.sin_addr);

    retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));  //server와 연결

    if (retval == SOCKET_ERROR)
        return 1;

    printf("connect 성공!\n");

    //1초에 1번씩 보낸 패킷의 크기 LOG 출력
    //패킷 데이터는 원하는 데이터 아무거나 보내면 됨
    //상기 public IP주소로 send 테스트 진행 
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
            //printf("메시지를 보냅니다.\n");
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