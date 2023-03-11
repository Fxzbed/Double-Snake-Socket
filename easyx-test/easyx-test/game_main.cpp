#include "game_main.h"

player::player()
{
	player_location_x.clear();
	player_location_y.clear();
	player_name.clear();
	head_angle = 'a';
}

player::~player()
{
	player_location_x.clear();
	player_location_y.clear();
	player_name.clear();
}

void player::player_spawn()
{
	int x_player;
	int y_player;
	x_player = rand_get(80);
	y_player = rand_get(50);
	player_location_x.push_back(x_player);
	player_location_y.push_back(y_player);
	for (int i = 1; i < 3; i++)
	{
		player_location_x.push_back(player_location_x[i - 1] + 1);
		player_location_y.push_back(player_location_y[i - 1]);
	}
	return;
}

bool player::player_judge()
{
	char tmp = ' ';
	//if (GetAsyncKeyState(tmp))
	//{

	if (KEY_DOWN(65) && head_angle != 'd')
		tmp = 'a';
	if (KEY_DOWN(68) && head_angle != 'a')
		tmp = 'd';
	if (KEY_DOWN(87) && head_angle != 's')
		tmp = 'w';
	if (KEY_DOWN(83) && head_angle != 'w')
		tmp = 's';
	switch (tmp)
	{
	case 'w':
		player_location_y[0] --;			//----------------------------------->x
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		head_angle = 'w';					//|
		break;								//|
	case 'a':								//|
		player_location_x[0] --;			//|
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		head_angle = 'a';					//y
		break;
	case 's':
		player_location_y[0] ++;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		head_angle = 's';
		break;
	case 'd':
		player_location_x[0] ++;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		head_angle = 'd';
		break;
	default:							//玩家按键未按下，保持先前的移动方向
		switch (this->head_angle)
		{
		case 'w':
			player_location_y[0] --;
			for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
			{
				if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
				{
					player_location_x.push_back(player_location_x.back());
					player_location_y.push_back(player_location_y.back());
					food_spawn.map_spawn_x[i] = -1;
					food_spawn.map_spawn_y[i] = -1;
				}
			}
			break;
		case 'a':
			player_location_x[0] --;
			for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
			{
				if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
				{
					player_location_x.push_back(player_location_x.back());
					player_location_y.push_back(player_location_y.back());
					food_spawn.map_spawn_x[i] = -1;
					food_spawn.map_spawn_y[i] = -1;
				}
			}
			break;
		case 's':
			player_location_y[0] ++;
			for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
			{
				if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
				{
					player_location_x.push_back(player_location_x.back());
					player_location_y.push_back(player_location_y.back());
					food_spawn.map_spawn_x[i] = -1;
					food_spawn.map_spawn_y[i] = -1;
				}
			}
			break;
		case 'd':
			player_location_x[0] ++;
			for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
			{
				if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
				{
					player_location_x.push_back(player_location_x.back());
					player_location_y.push_back(player_location_y.back());
					food_spawn.map_spawn_x[i] = -1;
					food_spawn.map_spawn_y[i] = -1;
				}
			}
			break;
		}
	}				//在此完成头的移动
	switch (this->head_angle)
	{
	case 'a':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_x[1] = player_location_x[0] + 1;
		player_location_y[1] = player_location_y[0];
		break;
	case 'd':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_x[1] = player_location_x[0] - 1;
		player_location_y[1] = player_location_y[0];
 		break;
	case 'w':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_y[1] = player_location_y[0] + 1;
		player_location_x[1] = player_location_x[0];
		break;
	case 's':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}
		player_location_y[1] = player_location_y[0] - 1;
		player_location_x[1] = player_location_x[0];
	}
	//while (1)
	//{
	//	if (player_location_x[x] == player_location_x[0] && player_location_x[y] == player_location_y[0])
	//	{
	//		this->player_death();
	//		return false;
	//	}
	//	player_location_x[x] = player_location_x[x--];
	//	player_location_y[y] = player_location_y[y--];
	//	x++;
	//	y++;
	//	if (player_location_x[x] == player_location_x.back())
	//	{
	//		break;
	//	}
	//}
	if (player_location_x[0] == -1)
	{
		player_location_x[0] = 79;
	}
	else if (player_location_x[0] == 80)
	{
		player_location_x[0] = 0;
	}

	if (player_location_y[0] == -1)
	{
		player_location_y[0] = 48;
	}
	else if (player_location_y[0] == 50)
	{
		player_location_y[0] = 1;
	}

	return true;
}

bool player::player_judge_mulity()
{
	switch (this->head_angle)
	{
	case 'w':
		player_location_y[0] --;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		break;
	case 'a':
		player_location_x[0] --;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		break;
	case 's':
		player_location_y[0] ++;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		break;
	case 'd':
		player_location_x[0] ++;
		for (int i = 0; i < food_spawn.map_spawn_x.size(); i++)
		{
			if (player_location_x[0] == food_spawn.map_spawn_x[i] && player_location_y[0] == food_spawn.map_spawn_y[i])
			{
				player_location_x.push_back(player_location_x.back());
				player_location_y.push_back(player_location_y.back());
				food_spawn.map_spawn_x[i] = -1;
				food_spawn.map_spawn_y[i] = -1;
			}
		}
		break;
	}			//在此完成头的移动
	switch (this->head_angle)
	{
	case 'a':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_x[1] = player_location_x[0] + 1;
		player_location_y[1] = player_location_y[0];
		break;
	case 'd':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_x[1] = player_location_x[0] - 1;
		player_location_y[1] = player_location_y[0];
		break;
	case 'w':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}

		player_location_y[1] = player_location_y[0] + 1;
		player_location_x[1] = player_location_x[0];
		break;
	case 's':
		for (int index = this->player_location_x.size() - 1; index > 1; index--)
		{
			player_location_x[index] = player_location_x[index - 1];
			player_location_y[index] = player_location_y[index - 1];
			if (player_location_x[0] == player_location_x[index] && player_location_y[0] == player_location_y[index])
				return false;
		}
		player_location_y[1] = player_location_y[0] - 1;
		player_location_x[1] = player_location_x[0];
	}
	//while (1)
	//{
	//	if (player_location_x[x] == player_location_x[0] && player_location_x[y] == player_location_y[0])
	//	{
	//		this->player_death();
	//		return false;
	//	}
	//	player_location_x[x] = player_location_x[x--];
	//	player_location_y[y] = player_location_y[y--];
	//	x++;
	//	y++;
	//	if (player_location_x[x] == player_location_x.back())
	//	{
	//		break;
	//	}
	//}
	if (player_location_x[0] == -1)
	{
		player_location_x[0] = 79;
	}
	else if (player_location_x[0] == 80)
	{
		player_location_x[0] = 0;
	}

	if (player_location_y[0] == -1)
	{
		player_location_y[0] = 48;
	}
	else if (player_location_y[0] == 50)
	{
		player_location_y[0] = 1;
	}

	return true;
}

gamemap::gamemap()
{
	this->map_spawn_x.clear();
	this->map_spawn_y.clear();
}

gamemap::~gamemap()
{

}

void gamemap::spawn_food(int mode)
{
	int x = 0;
	switch (mode)
	{
	case 1: //初始
		while (x != 15)
		{
			map_spawn_x.push_back(rand_get(80));
			map_spawn_y.push_back(rand_get(50));
			x++;
		}
		break;
	case 2: //补
		while (x!= 5)
		{
			map_spawn_x.push_back(rand_get(80));
			map_spawn_y.push_back(rand_get(50));
			x++;
		}
		break;
	}
}

void gamemap::food_undata()
{
	int x = 5;
	while (x != 5)
	{
		map_spawn_x.push_back(rand_get(80));
		map_spawn_y.push_back(rand_get(50));
	}
}


int rand_get(int num)
{
	std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
	std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
	std::uniform_int_distribution<unsigned long long> distr(1, num);// distribution in range [1, num]
	return distr(eng);
}

void put_death_msg()
{
}

bool mulity_judge_contect()
{
	for (int index = 0; index < mulity_2->player_location_x.size(); index++)
	{
		if (mulity_1->player_location_x[0] == mulity_2->player_location_x[index] && mulity_1->player_location_y[0] == mulity_2->player_location_y[index])
			return false;
	}
	for (int index = 0; index < mulity_1->player_location_x.size(); index++)
	{
		if (mulity_2->player_location_x[0] == mulity_1->player_location_x[index] && mulity_2->player_location_y[0] == mulity_1->player_location_y[index])
			return false;
	}
	return true;
}
