#include "game_sock.h"

std::mutex lock_;

msg_body_socket::msg_body_socket()
{
	this->magic_number[0] = 1; magic_number[1] = 1; magic_number[2] = 4; magic_number[3] = 5;
	this->data_length[0] = -1;
	this->data_type[0] = 5;
}

msg_body_socket::~msg_body_socket()
{
}


socket_server_body::socket_server_body()
{
	this->server_socket = NULL;
	WSAData wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		putMsg_error("WSAStartup");
	}
	else
	{
		std::cout << "WSAStartup sussess" << std::endl;
	}
}

socket_server_body::~socket_server_body()
{
	if (0 != WSACleanup())
	{
		putMsg_error("WSASCleanup");
	}
	else
	{
		std::cout << "WSACleanup success" << std::endl;
	}
}

bool socket_server_body::createsocket_server(std::string& ip_)
{
	this->server_socket;        //空的socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		putMsg_error("socket");
		return false;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);											//绑定端口25565
	addr.sin_addr.S_un.S_addr = inet_addr(ip_.c_str());
	if (SOCKET_ERROR == bind(server_socket, (sockaddr*)&addr, sizeof(addr)))
	{
		putMsg_error("bind");
		return false;
	}
	listen(server_socket, 10);
	return true;
}
//
//DWORD WINAPI serverthread(LPVOID lp)
//{
//	std::cout << "thread " << "created!" << std::endl;
//	SOCKET* thread_connect = (SOCKET*)lp;
//	msg_body_socket recv_send_body;
//	recv_send_body.tmp_malloc();
//	recv_send_body.get_buffer(mulity_2);
//	while (1)
//	{
//		if (recv_send_body.recv_data_head(thread_connect))
//		{
//			switch (recv_send_body.data_type)
//			{
//			case 1:
//				recv_send_body.recv_data_sub_1(thread_connect);
//				break;					//无动作类型
//			case 2:
//				recv_send_body.recv_data_sub_2(thread_connect);
//				break;					//动作同步类型
//			case 3:
//				recv_send_body.recv_data_sub_3(thread_connect);
//				break;					//玩家同步类型
//			case 4:						
//				recv_send_body.recv_data_sub_4(thread_connect);
//										//食物同步类型
//			}
//		}
//	}
//
//	
//	return 0;
//}

bool msg_body_socket::send_recv_data_head(SOCKET* sock, const int mode)
{
	recv(*sock, this->magic_number, 4, 0);
	recv(*sock, this->data_type, 1, 0);
	if (mode == 0)
	{
		send(*sock, this->data_length, 1, 0);
		return true;
	}
	else if (mode == 1)
	{
		this->data_length[0] = 3;//head angle spawn_x spawn_y
		recv(*sock, this->data_length, 1, 0);
		return true;
	}
	else if (mode == 3)
	{
		this->data_length[0] = 40;//food_spawn_x | food_spawn_y
		send(*sock, this->data_length, 1, 0);
		return true;
	}
	else if (mode == 4)
	{
		this->data_length[0] = 40;
		recv(*sock, this->data_length, 1, 0);
	}
	else if (mode == 5)
	{

	}
}

bool msg_body_socket::send_recv_data_sub(SOCKET* sock, const int mode)
{
	int length;
	if (mode == 1)				//send
	{
		send(*sock, &this->buffer_save_body.location_tmp_x, 1, 0);
		send(*sock, &this->buffer_save_body.location_tmp_y, 1, 0);
	}
	else if (mode == 0)                //recv
	{
		recv(*sock, &this->buffer_save_body.location_tmp_x, 1, 0);
		recv(*sock, &this->buffer_save_body.location_tmp_y, 1, 0);
	}
	else if (mode == 3)
	{
		send(*sock, this->buffer_save_body.food_spawn_x, 15, 0);
		send(*sock, this->buffer_save_body.food_spawn_y, 15, 0);
	}
	else if (mode == 4)
	{
		recv(*sock, this->buffer_save_body.food_spawn_x, 15, 0);
		recv(*sock, this->buffer_save_body.food_spawn_y, 15, 0);
	}
	else if (mode == 5)
	{
		send(*sock, &this->buffer_save_body.head_angle, 1, 0);
	}
	else if (mode == 6)
	{
		recv(*sock, &this->buffer_save_body.head_angle, 1, 0);
	}
	return true;
}

void msg_body_socket::player_initialize(player& mulity_recv)
{
	mulity_recv.head_angle = 'a';
	mulity_recv.player_location_x.push_back(this->buffer_save_body.location_tmp_x);
	mulity_recv.player_location_y.push_back(this->buffer_save_body.location_tmp_y);
	for (int tmp = 1; tmp < 3; tmp++)
	{
		mulity_recv.player_location_x.push_back(mulity_recv.player_location_x[tmp - 1] + 1);
		mulity_recv.player_location_y.push_back(mulity_recv.player_location_y[tmp - 1]);
	}
}

void msg_body_socket::map_initialize(gamemap& map_data)
{
	for (int i = 0; i < 15; i++)
	{
		map_data.map_spawn_x.push_back(this->buffer_save_body.food_spawn_x[i]);
		map_data.map_spawn_y.push_back(this->buffer_save_body.food_spawn_y[i]);
	}
}

void msg_body_socket::move_buff_synchor(player& mulity_recv)
{
	mulity_recv.head_angle = this->buffer_save_body.head_angle;
}

//bool msg_body_socket::tmp_malloc()
//{
//	if (!((this->buffer_save_body.location_tmp_x = new int) || (this->buffer_save_body.location_tmp_y = new int)))
//		return false;
//	else
//		return true;
//}

void msg_body_socket::get_buffer(player* mulity)
{
	this->buffer_save_body.location_tmp_x = mulity->player_location_x[0];
	this->buffer_save_body.location_tmp_y = mulity->player_location_y[0];
	for (int index = 0; index < food_spawn.map_spawn_x.size(); index++)
	{
		this->buffer_save_body.food_spawn_x[index] = food_spawn.map_spawn_x[index];
		this->buffer_save_body.food_spawn_y[index] = food_spawn.map_spawn_y[index];
	}
	return;
}

void msg_body_socket::get_buffer_playeronly(player* mulity)
{
	this->buffer_save_body.location_tmp_x = mulity->player_location_x[0];
	this->buffer_save_body.location_tmp_y = mulity->player_location_y[0];
	this->buffer_save_body.head_angle = mulity->head_angle;
	return;
}

bool socket_server_body::createsocket_client(std::string& ip_)
{
	this->server_socket;        //空的socket
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		putMsg_error("socket");
		return false;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);											//绑定端口25565
	addr.sin_addr.S_un.S_addr = inet_addr(ip_.c_str());
	if (SOCKET_ERROR == connect(server_socket, (sockaddr*)&addr, sizeof(addr)))
	{
		putMsg_error("connect");
		return false;
	}
	return true;
}