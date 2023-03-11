#pragma once
#ifndef _GAME_SOCK_H_
#define _GAME_SOCK_H_

#include "game_main.h"
#include<WinSock2.h>
#include <string>
#include <vector>
#include <mutex>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#define putMsg_error(error_) std::cout << "[" << __LINE__ << "]" << " : " << "(" << error_ << ")" << "failcode is " << WSAGetLastError() << std::endl;

/*
* msg_body_socket
* -----------------------------------------------------------------------------------------------------------------------------------
* head angle - w			| snake state - 0 [ snake dead ]		| 
*			 - a			| snake state - 1 [ snake alive]		|
*			 - s			|										|
*			 - d			|										|
* 
* send_recv_data_sub
* -----------------------------------------------------------------------------------------------------------------------------------
* mode - 0 recv [ player ]
*      - 1 send [ player ] 
*	   - 2 recv [ map ]
*	   - 3 send [ map ]
* 
* 
* ----------------------------------------------------------------------------------------------------------------------------------
* 
*	head						data body(1)		data body(2)		data body(3)		data body(4)		
* ----------------------------------------------------------------------------------------------------------------------------------
* --magic_number: 1234		|--magic number		|--head angle		|--player location x  |--food location x  |
* --data_type:				|					|					|--player location y  |--food location y  |
* --data_length				|					|					|					  |					  |
* --1: no move				|					|					|					  |					  |
* --2: move synchor			|					|					|					  |					  |	
* --3: snake spawn			|					|					|					  |					  |
* --4: food spawn			|					|					|					  |					  |
* ----------------------------------------------------------------------------------------------------------------------------------
*	synchor-first
* ----------------------------------------------------------------------------------------------------------------------------------
* --5:						--magic number
*							--player location synchor
*							--food	synchor
* 
* -----------------------------------------------------------------------------------------------------------------------------------
* server -> client : head 5 synchor-first
* client -> server : head 5 synchor-first
* connect........
*/


extern std::mutex lock_;

DWORD WINAPI serverthread(LPVOID lp);

class msg_body_socket
{
public:
	msg_body_socket();
	~msg_body_socket();
	bool send_recv_data_head(SOCKET* sock, const int mode);
	bool send_recv_data_sub(SOCKET* sock, const int mode);
	void player_initialize(player& mulity_recv);
	void map_initialize(gamemap& map_data);
	void move_buff_synchor(player& mulity_recv);
	void get_buffer(player *mulity);
	void get_buffer_playeronly(player* mulity);
	struct buffer
	{
		char head_angle = ' ';
		char snake_state = ' ';
		char location_tmp_x;
		char location_tmp_y;
		char food_spawn_x[15];
		char food_spawn_y[15];

	}buffer_save_body;
	char magic_number[4];
	char data_length[4];
	char data_type[1];
};

class socket_server_body
{
public:
	socket_server_body();
	~socket_server_body();
	bool createsocket_server(std::string& ip_);
	bool createsocket_client(std::string& ip_);
	SOCKET server_socket;
};

class client
{
public:
	client();
	~client();
	bool connect_server(std::istream& in, std::string ip_);
	SOCKET client_socket;
};

#endif // _GAME_SOCK_H

