#include "menu.h"

player* mulity_1;

player* mulity_2;

gamemap food_spawn;

menu_set::~menu_set()
{

}

menu_set::menu_set()
{
    select_menu = 0;
    MOUSEMSG msg_mouse;
    //创建一个窗口
    initgraph(1600, 1000, EW_SHOWCONSOLE);
    rectangle(520, 300, 950, 400);
    outtextxy(700, 340, "单人模式");
    rectangle(520, 500, 950, 600);
    outtextxy(700, 540, "双人模式");
    while(1)
    {
        msg_mouse = GetMouseMsg();
        Sleep(5);
        if (msg_mouse.x > 520 && msg_mouse.x < 950 && msg_mouse.y > 300 && msg_mouse.y < 400)
        {
            if (msg_mouse.uMsg == WM_LBUTTONDOWN)
            {
                select_menu = 1;
                break;
            }
        }
        if (msg_mouse.x > 520 && msg_mouse.x < 950 && msg_mouse.y > 500 && msg_mouse.y < 600)
        {
            if (msg_mouse.uMsg == WM_LBUTTONDOWN)
            {
                select_menu = 2;
                break;
            }
        }
    }
    player player_1;
    switch (mode_select())
    {
    case 1:         //single
        cleardevice();
        food_spawn.spawn_food(1);
        player_1.player_spawn();
        while (1)
        {
            BeginBatchDraw();//开始绘图
            cleardevice();
            rectangle(player_1.player_location_x[0] * 20, player_1.player_location_y[0] * 20, player_1.player_location_x[0] * 20 + 20, player_1.player_location_y[0] * 20 - 20);
            for (int times = 1; times < player_1.player_location_x.size(); times++)
            {
                rectangle(player_1.player_location_x[times] * 20, player_1.player_location_y[times] * 20, player_1.player_location_x[times] * 20 + 20, player_1.player_location_y[times] * 20 - 20);
            }
            for (int times = 0; times < food_spawn.map_spawn_x.size(); times++)
            {
                fillrectangle(food_spawn.map_spawn_x[times] * 20, food_spawn.map_spawn_y[times] * 20, food_spawn.map_spawn_x[times] * 20 + 20, food_spawn.map_spawn_y[times] * 20 - 20);
            }
            if (!player_1.player_judge())
            {
                cleardevice();
                rectangle(player_1.player_location_x[0] * 20, player_1.player_location_y[0] * 20, player_1.player_location_x[0] * 20 + 20, player_1.player_location_y[0] * 20 - 20);
                for (int times = 1; times < player_1.player_location_x.size(); times++)
                {
                    rectangle(player_1.player_location_x[times] * 20, player_1.player_location_y[times] * 20, player_1.player_location_x[times] * 20 + 20, player_1.player_location_y[times] * 20 - 20);
                }
                for (int times = 0; times < food_spawn.map_spawn_x.size(); times++)
                {
                    fillrectangle(food_spawn.map_spawn_x[times] * 20, food_spawn.map_spawn_y[times] * 20, food_spawn.map_spawn_x[times] * 20 + 20, food_spawn.map_spawn_y[times] * 20 - 20);
                }
                Sleep(60);
                break;
            }
            Sleep(60);
            FlushBatchDraw();//这里也可以用EndBatchDraw();
        }
        break;
    case 2:         //muplity  server
    {
        std::cout << "Do you want be host, choose yes or no" << std::endl;
        std::string judge;
        std::cin >> judge;
        mulity_1 = new player;
        mulity_2 = new player;
        mulity_1->player_spawn();              //初始化
        std::string* ip = new std::string;
        socket_server_body socket_snake;
        msg_body_socket recv_send_body;
        if (judge != "yes")
        {
            std::cout << "The ports has bind 25565" << std::endl;
            std::cout << "Please input connect ip: ";
            std::cin >> *ip;
            if (socket_snake.createsocket_client(*ip))
            {
            client_synchor_part:
                recv_send_body.send_recv_data_sub(&socket_snake.server_socket, 0); //player data
                recv_send_body.player_initialize(*mulity_2);             // initialize player_other
                recv_send_body.get_buffer_playeronly(mulity_1);         //get buffer of player_local
                mulity_1->head_angle = 'a';
                recv_send_body.send_recv_data_sub(&socket_snake.server_socket, 1); //player data
                recv_send_body.send_recv_data_sub(&socket_snake.server_socket, 4);  //map send
                recv_send_body.map_initialize(food_spawn);
                goto draw_mulity;
            loop_body:
                recv_send_body.send_recv_data_sub(&socket_snake.server_socket, 6);  //player data
                recv_send_body.move_buff_synchor(*mulity_2);
                recv_send_body.get_buffer_playeronly(mulity_1);
                recv_send_body.send_recv_data_sub(&socket_snake.server_socket, 5);  //player data
            draw_mulity:
                BeginBatchDraw();//开始绘图
                cleardevice();
                rectangle(mulity_1->player_location_x[0] * 20, mulity_1->player_location_y[0] * 20, mulity_1->player_location_x[0] * 20 + 20, mulity_1->player_location_y[0] * 20 - 20);
                for (int times = 1; times < mulity_1->player_location_x.size(); times++)
                {
                    rectangle(mulity_1->player_location_x[times] * 20, mulity_1->player_location_y[times] * 20, mulity_1->player_location_x[times] * 20 + 20, mulity_1->player_location_y[times] * 20 - 20);
                }
                for (int times = 0; times < food_spawn.map_spawn_x.size(); times++)
                {
                    fillrectangle(food_spawn.map_spawn_x[times] * 20, food_spawn.map_spawn_y[times] * 20, food_spawn.map_spawn_x[times] * 20 + 20, food_spawn.map_spawn_y[times] * 20 - 20);
                }
                rectangle(mulity_2->player_location_x[0] * 20, mulity_2->player_location_y[0] * 20, mulity_2->player_location_x[0] * 20 + 20, mulity_2->player_location_y[0] * 20 - 20);
                for (int times = 1; times < mulity_2->player_location_x.size(); times++)
                {
                    rectangle(mulity_2->player_location_x[times] * 20, mulity_2->player_location_y[times] * 20, mulity_2->player_location_x[times] * 20 + 20, mulity_2->player_location_y[times] * 20 - 20);
                }
                FlushBatchDraw();
                if (!mulity_1->player_judge())
                    return;
                if (!mulity_2->player_judge_mulity())
                    return;
                if (!mulity_judge_contect())
                    return;
                Sleep(50);
                goto loop_body;
            }
        }
        std::cout << "The ports has bind 25565" << std::endl;
        std::cout << "Please input connect ip: ";
        std::cin >> *ip;
        if (socket_snake.createsocket_server(*ip))
        {
            {
                food_spawn.spawn_food(1);
                recv_send_body.get_buffer(mulity_1);
                SOCKET* client = new SOCKET;
                *client = accept(socket_snake.server_socket, NULL, NULL);
                /* CreateThread(NULL, 0, &serverthread, client, 0, NULL);*/
                std::cout << "thread " << "created!" << std::endl;
                SOCKET* thread_connect = (SOCKET*)client;                                                       //first synchor
                recv_send_body.send_recv_data_sub(thread_connect, 1); //player data
                recv_send_body.send_recv_data_sub(thread_connect, 0); //player data
                recv_send_body.send_recv_data_sub(thread_connect, 3);  //map send
                recv_send_body.player_initialize(*mulity_2);
                goto draw;
            data_recv_send_part://loop body
                recv_send_body.get_buffer_playeronly(mulity_1);
                recv_send_body.send_recv_data_sub(thread_connect, 5);  //player data 
                recv_send_body.send_recv_data_sub(thread_connect, 6);  //player data
            data_buffer_write_part:
                recv_send_body.move_buff_synchor(*mulity_2);
            draw:
                BeginBatchDraw();//开始绘图
                cleardevice();
                rectangle(mulity_1->player_location_x[0] * 20, mulity_1->player_location_y[0] * 20, mulity_1->player_location_x[0] * 20 + 20, mulity_1->player_location_y[0] * 20 - 20);
                for (int times = 1; times < mulity_1->player_location_x.size(); times++)
                {
                    rectangle(mulity_1->player_location_x[times] * 20, mulity_1->player_location_y[times] * 20, mulity_1->player_location_x[times] * 20 + 20, mulity_1->player_location_y[times] * 20 - 20);
                }
                for (int times = 0; times < food_spawn.map_spawn_x.size(); times++)
                {
                    fillrectangle(food_spawn.map_spawn_x[times] * 20, food_spawn.map_spawn_y[times] * 20, food_spawn.map_spawn_x[times] * 20 + 20, food_spawn.map_spawn_y[times] * 20 - 20);
                }
                rectangle(mulity_2->player_location_x[0] * 20, mulity_2->player_location_y[0] * 20, mulity_2->player_location_x[0] * 20 + 20, mulity_2->player_location_y[0] * 20 - 20);
                for (int times = 1; times < mulity_2->player_location_x.size(); times++)
                {
                    rectangle(mulity_2->player_location_x[times] * 20, mulity_2->player_location_y[times] * 20, mulity_2->player_location_x[times] * 20 + 20, mulity_2->player_location_y[times] * 20 - 20);
                }
                FlushBatchDraw();
                if (!mulity_1->player_judge())
                    return;
                if (!mulity_2->player_judge_mulity())
                    return;
                if (!mulity_judge_contect())
                    return;
                Sleep(50);
                goto data_recv_send_part;
            }
        }
        break;
    }
    }
    return;
}

int menu_set::mode_select()
{   
    switch (select_menu)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 0:
        return 0;
    }
    return 0;
}