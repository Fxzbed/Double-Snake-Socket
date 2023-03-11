#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_

#include<WinSock2.h>
#include <string>
#include <fstream>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#pragma comment(lib, "ws2_32.lib")
#define putMsg_error(error_) std::cout << "[" << __LINE__ << "]" << " : " << "(" << error_ << ")" << "failcode is " << WSAGetLastError() << std::endl;

bool init_Socket();

bool close_socket();

SOCKET creatsocket_server();

DWORD WINAPI serverthread(LPVOID lp);

#endif // !_SERVER_H_
