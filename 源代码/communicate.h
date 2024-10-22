#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<string>
#pragma comment(lib, "ws2_32.lib")
std::string getIP();
void communicate();
#endif COMMUNICATE_H
