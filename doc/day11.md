# 11일차 STUDY & TASK
* TASK
    > TCP 속도 테스트 클라이언트 만들기   
    ```cpp
    #pragma comment(lib, "ws2_32")
    #include <WS2tcpip.h>
    #include <WinSock2.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define SERVERIP L"20.214.110.87"
    #define SERVERPORT 9000
    #define BUFSIZE 512

    int main()
    {
        int retval;

        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return 1;

        printf("WSAStartup() 성공!\n");

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock == INVALID_SOCKET)
            return 1;

        SOCKADDR_IN serveraddr;
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(SERVERPORT);
        InetPton(AF_INET, SERVERIP, &serveraddr.sin_addr);

        retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
        
        if (retval == SOCKET_ERROR)
            return 1;

        printf("connect 성공!\n");

        //코드 작성
        //1초에 1번씩 보낸 패킷의 크기 LOG 출력
        //패킷 데이터는 원하는 데이터 아무거나 보내면 됨
        //상기 public IP주소로 send 테스트 진행 

        closesocket(sock);
        WSACleanup();
        return 0;
    }
    ```
    > 위 코드를 참고하여 TCP 속도 테스트 클라이언트 작성   
    > [실행파일](/task_data/TCP_speed_test_client_server.zip)

[To main](/README.md)