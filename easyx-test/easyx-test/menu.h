#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include <graphics.h> //ͼ�ο�
#include "game_sock.h"

class menu_set
{
public:
	~menu_set();
	menu_set();
	int mode_select();
protected:
	int select_menu;
};

#endif // !_MENU_H_
