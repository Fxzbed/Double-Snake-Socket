#pragma once
#ifndef _GAME_MAIN_H_
#define _GAME_MAIN_H_
#include <iostream>
#include <vector>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>
#include <random>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

int rand_get(int num);

void put_death_msg();

bool mulity_judge_contect();

enum food_set
{
	void_point,
	food_point
};

class player
{
public:
	player();
	~player();
	void player_spawn();
	bool player_judge();
	bool player_judge_mulity();
	std::vector<int>player_location_x;
	std::vector<int>player_location_y;
	std::string player_name;
	char head_angle;
};

class gamemap
{
public:
	gamemap();
	~gamemap();
	void spawn_food(int mode);
	void food_undata();
	std::vector<int> map_spawn_x;
	std::vector<int> map_spawn_y;
};

extern gamemap food_spawn;

extern player* mulity_1;

extern player* mulity_2;

#endif // !_GAME_MAIN_H_
