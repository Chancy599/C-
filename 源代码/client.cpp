#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // for inet_pton
#include<string>
#pragma comment(lib, "ws2_32.lib")
int main() 
{
    std::cout << "Hello World!\n";
    std::string IP;
    std::cout << "�������������IP��ַ��";
    std::getline(std::cin, IP); // ʹ�� std::getline ��ȡIP��ַ
    WSADATA wsdata;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata)) 
    {
        std::cout << "init socket failed!" << std::endl;
        WSACleanup();
        return FALSE;
    }

    SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == INVALID_SOCKET) 
    {
        std::cout << "create socket fail" << std::endl;
        WSACleanup();
        return FALSE;
    }

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8226);

    // ʹ�� inet_pton �滻 inet_addr
    if (inet_pton(AF_INET, IP.c_str(), &server_addr.sin_addr) <= 0)
    {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        closesocket(client);
        WSACleanup();
        return FALSE;
    }

    if (connect(client, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        std::cout << "Error: connect server failed !" << std::endl;
        closesocket(client);
        WSACleanup();
        return -1;
    }
    std::cout << "�ɹ����ӵ�������" << std::endl;

    char temp[1024] = { 0 };
    char recv_buf[8192] = { 0 };

    while (true) 
    {
        std::cout << "����Ҫ���͵�����: ";
        std::cin.getline(temp, sizeof(temp));
        std::cout << "�ȴ��������˷��������С���" << std::endl;
        int send_len = send(client, temp, strlen(temp), 0);
        if (send_len == SOCKET_ERROR)
        {
            std::cout << "Error: send info to server failed!" << std::endl;
            closesocket(client);
            WSACleanup();
            return -1;
        }

        int recv_len = recv(client, recv_buf, sizeof(recv_buf) - 1, 0);
        if (recv_len == SOCKET_ERROR || recv_len == 0)
        {
            std::cout << "Error: receive info from server failed or connection closed!" << std::endl;
            closesocket(client);
            WSACleanup();
            return -1;
        }
        recv_buf[recv_len] = '\0'; // ȷ�����յ���������NULL��β
        std::cout << "�յ��˷��������ص���Ϣ �����ǣ�" << recv_buf << std::endl;
    }
    closesocket(client);
    WSACleanup();
    return 0;
}
