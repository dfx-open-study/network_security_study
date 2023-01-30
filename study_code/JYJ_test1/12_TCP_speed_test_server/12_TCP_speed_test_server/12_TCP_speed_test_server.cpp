#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE 512
#define LOGTIME 1000

int main()
{
    int retval;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    printf("WSAStartup() ����!\n");
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_sock == INVALID_SOCKET)
        return 1;

    printf("listen socket ���� ����!\n");

    SOCKADDR_IN serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

    if (retval == SOCKET_ERROR)
        return 1;

    printf("socket bind ����!\n");

    retval = listen(listen_sock, SOMAXCONN);

    if (retval == SOCKET_ERROR)
        return 1;

    printf("socket listen ����!\n");

    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE + 1];
    unsigned long long priv_tick;
    unsigned long long now_tick;
    unsigned int recv_size;
    unsigned int total_recv_size = 0;

    while (1)
    {
        addrlen = sizeof(clientaddr);
        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET)
        {
            printf("accept ���!!\n");
        }
        printf("accept ����!!\n");

        priv_tick = GetTickCount64();
        while (1)
        {
            recv_size = recv(client_sock, buf, BUFSIZE, 0);

            total_recv_size += recv_size;

            now_tick = GetTickCount64();
  
            if(recv_size < 0)
            {
                printf("Ŭ���̾�Ʈ�� ������ ������!\n");
            }
            if (now_tick - priv_tick >= 1000)
            {
                printf("���� ������ ������ : %d\n", total_recv_size);
                total_recv_size = 0;
                priv_tick = GetTickCount64();
            }
        }
        closesocket(client_sock);
    }
    
    closesocket(listen_sock);
    WSACleanup();
    return 0;
}