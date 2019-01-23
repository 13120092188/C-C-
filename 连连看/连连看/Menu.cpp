#include "Menu.hpp"
#include "Board.hpp"
#include "Timer.hpp"
#include<thread>
#include <windows.h>
#include<graphics.h>
//#pragma comment (lib, "winmm.lib")

#define W 50
#define W1 50
Board board;
Timer tim;


int degree = 1;
int music = 0;//通知音乐开关，除了playsound()都不可以改变其值
int pause = 1;
int stop = -1;

void primaty_menu()
{
	IMAGE img;
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;
	IMAGE img5;

	loadimage(&img, _T("src/主界面/主菜单.jpg")); // 读取图片到 img 对象中
	putimage(0, 0, &img);//打印出背景图片“主菜单”

	MOUSEMSG mousemsg;//用来储存鼠标信息的结构
	while (TRUE)
	{
		mousemsg = GetMouseMsg();// 获取一个鼠标消息。如果没有，就等待
		switch (mousemsg.uMsg)
		{
		case WM_MOUSEMOVE:  //鼠标移动
		{
			FlushMouseMsgBuffer();  // 清空鼠标消息缓冲区
			if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				loadimage(&img2, _T("src/主界面/verysimple.jpg")); 
				putimage(460, 166, &img2);  
			}
			else if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				loadimage(&img3, _T("src/主界面/simple.jpg"));  
				putimage(458, 360, &img3);  
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				loadimage(&img4, _T("src/主界面/hard.jpg")); 
				putimage(690, 162, &img4); 
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				loadimage(&img5, _T("src/主界面/veryhard.jpg"));  
				putimage(686, 360, &img5); 
			}
			else
			{
				loadimage(&img1, _T("src/主界面/主菜单中.jpg"));  
				putimage(448, 156, &img1); 
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			FlushMouseMsgBuffer();  // 清空鼠标消息缓冲区
			if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				degree = 1;
				newGame();
			}
			else if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				degree = 2;
				newGame();
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				degree = 3;
				newGame();
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				degree = 4;
				newGame();
			}
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			playsound();

		}break;
		default:
			break;
		}
		Sleep(2);
	}
}

void startgif()
{
	thread t(threadShow);
	t.detach();//打开计时线程

	initgraph(1400, 787);  // 初始化图形环境
	playsound();
	//以下图片的连续播放用于实现动态效果
	IMAGE img;

	/*通过图片的连续变换形成动图*/
	{
		loadimage(&img, _T("src/主界面/开头动画1.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画2.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画3.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画4.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画5.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画6.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画7.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画8.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画9.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画10.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画11.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画12.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画13.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画14.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画15.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画16.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画17.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画18.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画19.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画20.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画21.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画22.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画23.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画24.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/主界面/开头动画25.jpg"));
		putimage(0, 0, &img);
	}
}

void LoadBackground()
{
	IMAGE img;
	switch (degree)
	{
	case 1:loadimage(&img, _T("src/主界面/背景1.jpg")); break;
	case 2:loadimage(&img, _T("src/主界面/背景2.jpg")); break;
	case 3:loadimage(&img, _T("src/主界面/背景3.jpg")); break;
	case 4:loadimage(&img, _T("src/主界面/背景4.jpg")); break;
	default:
		break;
	}
	putimage(0, 0, &img);
}

void newGame() 
{
	stop = -1;
	board.ClearBoard();
	LoadBackground();
	switch (degree)
	{
	case 1:board.SetBoard(6, 4, 4);  board.SetOriginXY(300, 250); break;
	case 2:board.SetBoard(8, 6, 2);  board.SetOriginXY(200, 150); break;
	case 3:board.SetBoard(10, 6, 4); board.SetOriginXY(110, 160); break;
	case 4:board.SetBoard(10, 6, 2); board.SetOriginXY(110, 160); break;
	default:
		break;
	}
	game();
}

void game() {
	/*以下图片为游戏界面的图片*/
	IMAGE img_restart;
	IMAGE img_suspend;
	IMAGE img_return;
	IMAGE img_tool;
	IMAGE img_prompt;

	board.Load_Image();
	board.JudgeMap();

	tim.Start();


	MOUSEMSG mousemsg;//用来储存鼠标信息的结构
	while (TRUE)
	{
		mousemsg = GetMouseMsg();// 获取一个鼠标消息。如果没有，就等待
		switch (mousemsg.uMsg)
		{
		case WM_MOUSEMOVE:  //鼠标移动
		{
			FlushMouseMsgBuffer();  // 清空鼠标消息缓冲区
			if (mousemsg.x >= 140 && mousemsg.x <= 384 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_restart, _T("src/主界面/restart.jpg")); 
				putimage(114, 0, &img_restart);
			}
			else if (mousemsg.x >= 440 && mousemsg.x <= 700 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_suspend, _T("src/主界面/suspend.jpg")); 
				putimage(414, 0, &img_suspend);
			}
			else if (mousemsg.x >= 750 && mousemsg.x <= 980 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_return, _T("src/主界面/return.jpg")); 
				putimage(731, 0, &img_return);
			}
			else if (mousemsg.x >= 1050 && mousemsg.x <= 1260 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_prompt, _T("src/主界面/prompt.jpg"));
				putimage(1150, 0, &img_prompt);
			}
			else
			{
				loadimage(&img_tool, _T("src/主界面/tool.jpg"));
				putimage(0, 0, &img_tool);
			}
			break;
		}
		case WM_LBUTTONDOWN:  //鼠标左键单击
		{
			FlushMouseMsgBuffer();  // 清空鼠标消息缓冲区
			if (mousemsg.x >= 140 && mousemsg.x <= 384 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				tim.Stop();
				newGame();
			}
			else if (-1 == stop && mousemsg.x >= 440 && mousemsg.x <= 700 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				if (1 == pause) {
					IMAGE img_pause;
					loadimage(&img_pause, _T("src/主界面/pause.jpg"));
					putimage(95, 145, &img_pause);
					tim.Pause();
				}
				else if (-1 == pause) {
					LoadBackground();
					board.Load_Image();
					tim.Start();
				}
				pause *= -1;
			}
			else if (mousemsg.x >= 750 && mousemsg.x <= 980 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				tim.Stop();
				primaty_menu();
			}
			else if (mousemsg.x >= 1050 && mousemsg.x <= 1260 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				int m = 0;
				for (int xx = 1; xx <= board.GetDimensionX(); xx++) {

					if (m == 1)
						break;
					for (int yy = 1; yy <= board.GetDimensionY(); yy++) {
						if (m == 1)
							break;
						if (board.map[xx][yy].get_appear() == false)
							continue;
						for (int xx2 = 1; xx2 <= board.GetDimensionX(); xx2++) {
							for (int yy2 = 1; yy2 <= board.GetDimensionY(); yy2++) {
								if (m == 1)
									break;
								if (xx == xx2 && yy == yy2)
									continue;
								if (false == board.map[xx2][yy2].get_appear())
									continue;
								board.choices[0].i = xx;
								board.choices[0].j = yy;
								board.choices[1].i = xx2;
								board.choices[1].j = yy2;
								if (board.JudgeChoices())//这里应该判断能否消除
								{
									IMAGE img;
									int x = board.GetX0() + (board.map[xx][yy].get_x() - 1)*SIZE_OF_IMAGE;
									int y = board.GetY0() + (board.map[xx][yy].get_y() - 1)*SIZE_OF_IMAGE;
									board.LoadImageList(2, board.map[xx][yy].get_type(), img);
									putimage(x, y, &img);
									x = board.GetX0() + (board.map[xx2][yy2].get_x() - 1)*SIZE_OF_IMAGE;
									y = board.GetY0() + (board.map[xx2][yy2].get_y() - 1)*SIZE_OF_IMAGE;
									board.LoadImageList(2, board.map[xx2][yy2].get_type(), img);
									putimage(x, y, &img);//将可以消除的两个方块变暗以起到提示效果
									m = 1;
									board.ReNewChoices();
									break;
								}


							}
						}

					}

				}
			}
			else if (1 == pause && -1 == stop && mousemsg.x >= board.GetX0() && mousemsg.x <= board.GetX0() + SIZE_OF_IMAGE*board.GetDimensionX() && mousemsg.y >= board.GetY0() && mousemsg.y <= board.GetY0() + SIZE_OF_IMAGE*board.GetDimensionY())
			{
				for (int i = 1; i <= board.GetDimensionX(); i++) 
				{
					for (int j = 1; j <= board.GetDimensionY(); j++) 
					{
						IMAGE img;
						int x = board.GetX0() + (board.map[i][j].get_x()-1)*SIZE_OF_IMAGE;
						int y = board.GetY0() + (board.map[i][j].get_y()-1)*SIZE_OF_IMAGE;
						if (mousemsg.x >= x && mousemsg.x <= x+ SIZE_OF_IMAGE && mousemsg.y >= y && mousemsg.y <= y+ SIZE_OF_IMAGE)
						{
							if (-1 == board.choices[0].i && board.map[i][j].get_appear()) {
								board.LoadImageList(2, board.map[i][j].get_type(), img);
								putimage(x, y, &img);
								board.choices[0].i = i;
								board.choices[0].j = j;
							}
							else if (-1 == board.choices[1].i && board.map[i][j].get_appear()) {
								if (board.choices[0].i != i || board.choices[0].j != j)
								{
									board.LoadImageList(2, board.map[i][j].get_type(), img);
									putimage(x, y, &img);
									board.choices[1].i = i;
									board.choices[1].j = j;
									if (board.JudgeChoices())//这里应该判断能否消除
									{
										board.EliminateBlock();
										int x1 = board.GetX0() + (board.map[board.choices[0].i][board.choices[0].j].get_x()-1)*SIZE_OF_IMAGE;
										int y1 = board.GetY0() + (board.map[board.choices[0].i][board.choices[0].j].get_y()-1)*SIZE_OF_IMAGE;
										bong(x, y, x1, y1);
										if (board.IsEnd())
										{
											tim.Stop();
											stop = 1;
											IMAGE img_end;
											loadimage(&img_end, _T("src/EndTime/end.jpg"));
											putimage(0, 128, &img_end);
											loadTimeImage(tim.getShowTime() / 100, 1);
											loadTimeImage(tim.getShowTime() / 10 % 10, 2);
											loadTimeImage(tim.getShowTime() % 10, 3);
										}
										board.ReNewChoices();
										board.JudgeMap();
									}
									else {
										board.LoadImageList(1, board.map[board.choices[0].i][board.choices[0].j].get_type(), img);
										putimage(board.GetX0() + (board.map[board.choices[0].i][board.choices[0].j].get_x()-1)*SIZE_OF_IMAGE, board.GetY0() + (board.map[board.choices[0].i][board.choices[0].j].get_y()-1)*SIZE_OF_IMAGE, &img);

										board.LoadImageList(1, board.map[board.choices[1].i][board.choices[1].j].get_type(), img);
										putimage(board.GetX0() + (board.map[board.choices[1].i][board.choices[1].j].get_x()-1)*SIZE_OF_IMAGE, board.GetY0() + (board.map[board.choices[1].i][board.choices[1].j].get_y()-1)*SIZE_OF_IMAGE, &img);

										board.ReNewChoices();
									}
								}
							}
							
						}
					}
				}
			}
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			playsound();

		}break;
		default:
			break;
		}
		Sleep(2);
	}
}

void playsound()
{
	if (music == 0) {
		mciSendString(_T("play 讲真的.mp3 repeat"), NULL, 0, NULL);
		music = 1;
	}
	else if (music == 1)
		mciSendString(_T("resume 讲真的.mp3"), NULL, 0, NULL);
	else if (music == -1)
		mciSendString(_T("pause 讲真的.mp3"), NULL, 0, NULL); 
	music *= -1;
}

void threadShow()
{
	while (true)
	{
		if(!tim.isStop() && !tim.isPause())
			tim.show();
		Sleep(100);
	}
}

void bong(int x, int y, int x1, int y1)
{
	IMAGE img;
	loadimage(&img, _T("src/bong/bong1.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong2.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong3.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong4.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong5.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong6.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong7.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong8.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong9.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong10.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong11.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
	Sleep(W1);
	loadimage(&img, _T("src/bong/bong12.jpg"));
	putimage(x, y, &img);
	putimage(x1, y1, &img);
}

void loadTimeImage(int figure, int digit)
{
	IMAGE img;
	switch (figure)
	{
	case 0:loadimage(&img, _T("src/EndTime/0.jpg")); break;
	case 1:loadimage(&img, _T("src/EndTime/1.jpg")); break;
	case 2:loadimage(&img, _T("src/EndTime/2.jpg")); break;
	case 3:loadimage(&img, _T("src/EndTime/3.jpg")); break;
	case 4:loadimage(&img, _T("src/EndTime/4.jpg")); break;
	case 5:loadimage(&img, _T("src/EndTime/5.jpg")); break;
	case 6:loadimage(&img, _T("src/EndTime/6.jpg")); break;
	case 7:loadimage(&img, _T("src/EndTime/7.jpg")); break;
	case 8:loadimage(&img, _T("src/EndTime/8.jpg")); break;
	case 9:loadimage(&img, _T("src/EndTime/9.jpg")); break;
	default:
		break;
	}
	switch (digit)
	{
	case 1:putimage(637, 366, &img); break;
	case 2:putimage(708, 366, &img); break;
	case 3:putimage(780, 366, &img); break;
	default:
		break;
	}
}
