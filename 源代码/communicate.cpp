#include"communicate.h"
std::string getIP()
{
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        std::cerr << "WSAStartup failed." << std::endl;
        return "\0";
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
    {
        std::cerr << "Error: gethostname failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return "\0";
    }

    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;  
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* result = NULL;
    if (getaddrinfo(hostname, NULL, &hints, &result) != 0)
    {
        std::cerr << "Error: getaddrinfo failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return "\0";
    }

    for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ip_str, sizeof(ip_str));
        std::cout << "服务端IP地址为：" << ip_str << std::endl;
        return ip_str;
    }

    freeaddrinfo(result);
    WSACleanup();
    return "\0";
}

void communicate() 
{
    std::cout << "Hello World!\n";
    WSADATA wsdata;
    std::cout << "start up now ...." << std::endl;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata)) 
    {
        std::cout << "init socket failed!" << std::endl;
        WSACleanup();
        return;
    }

    SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);
    if (s_server == INVALID_SOCKET) 
    {
        std::cout << "create socket fail" << std::endl;
        WSACleanup();
        return;
    }
    std::cout << "create socket success...." << std::endl;

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8226);

    // 使用 inet_pton 替换 inet_addr
    if (inet_pton(AF_INET, getIP().c_str(), &server_addr.sin_addr) <= 0)
    {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        closesocket(s_server);
        WSACleanup();
        return;
    }

    if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) 
    {
        std::cout << "Binding Socket fail.......!" << std::endl;
        closesocket(s_server);
        WSACleanup();
        return;
    }
    std::cout << "bind socket success...." << std::endl;

    if (listen(s_server, 1) == SOCKET_ERROR) 
    {
        std::cout << "Listening Socket fail........!" << std::endl;
        closesocket(s_server);
        WSACleanup();
        return;
    }
    std::cout << "listen socket success...." << std::endl;

    sockaddr_in accept_addr;
    int len = sizeof(SOCKADDR);
    char recv_buf[8192] = { 0 };
    char send_buf[1024] = { 0 };

    std::cout << "wait accept...." << std::endl;
    SOCKET s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
    if (s_accept == INVALID_SOCKET)
    {
        std::cout << "Error: accept failed !" << std::endl;
        closesocket(s_server);
        WSACleanup();
        return;
    }
    std::cout << "建立连接成功...." << std::endl;

    while (true) 
    {
        std::cout << "等待客户端数据中...." << std::endl;
        int recv_len = recv(s_accept, recv_buf, sizeof(recv_buf) - 1, 0);
        if (recv_len == SOCKET_ERROR) 
        {
            std::cout << "Error: receive info from client failed!" << std::endl;
            closesocket(s_accept);
            break;
        }
        if (recv_len == 0) 
        {
            std::cout << "Client disconnected!" << std::endl;
            closesocket(s_accept);
            break;
        }
        recv_buf[recv_len] = '\0'; // 确保接收到的数据以NULL结尾
        std::cout << "已收到数据，客户端的数据是：" << recv_buf << std::endl;

        std::cout << "给客户端返回数据中..." << std::endl;
        std::cin.getline(send_buf, sizeof(send_buf));
        int send_len = send(s_accept, send_buf, strlen(send_buf), 0);
        if (send_len == SOCKET_ERROR) 
        {
            std::cout << "Error: send info to client failed!" << std::endl;
            closesocket(s_accept);
            break;
        }
        std::cout << "给客户端返回数据完毕" << std::endl;
    }
    closesocket(s_server);
    WSACleanup();
    return;
}