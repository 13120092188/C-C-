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
int music = 0;//֪ͨ���ֿ��أ�����playsound()�������Ըı���ֵ
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

	loadimage(&img, _T("src/������/���˵�.jpg")); // ��ȡͼƬ�� img ������
	putimage(0, 0, &img);//��ӡ������ͼƬ�����˵���

	MOUSEMSG mousemsg;//�������������Ϣ�Ľṹ
	while (TRUE)
	{
		mousemsg = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
		switch (mousemsg.uMsg)
		{
		case WM_MOUSEMOVE:  //����ƶ�
		{
			FlushMouseMsgBuffer();  // ��������Ϣ������
			if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				loadimage(&img2, _T("src/������/verysimple.jpg")); 
				putimage(460, 166, &img2);  
			}
			else if (mousemsg.x >= 472 && mousemsg.x <= 660 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				loadimage(&img3, _T("src/������/simple.jpg"));  
				putimage(458, 360, &img3);  
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 180 && mousemsg.y <= 330)
			{
				loadimage(&img4, _T("src/������/hard.jpg")); 
				putimage(690, 162, &img4); 
			}
			else if (mousemsg.x >= 710 && mousemsg.x <= 890 && mousemsg.y >= 380 && mousemsg.y <= 527)
			{
				loadimage(&img5, _T("src/������/veryhard.jpg"));  
				putimage(686, 360, &img5); 
			}
			else
			{
				loadimage(&img1, _T("src/������/���˵���.jpg"));  
				putimage(448, 156, &img1); 
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			FlushMouseMsgBuffer();  // ��������Ϣ������
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
	t.detach();//�򿪼�ʱ�߳�

	initgraph(1400, 787);  // ��ʼ��ͼ�λ���
	playsound();
	//����ͼƬ��������������ʵ�ֶ�̬Ч��
	IMAGE img;

	/*ͨ��ͼƬ�������任�γɶ�ͼ*/
	{
		loadimage(&img, _T("src/������/��ͷ����1.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����2.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����3.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����4.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����5.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����6.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����7.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����8.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����9.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����10.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����11.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����12.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����13.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����14.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����15.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����16.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����17.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����18.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����19.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����20.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����21.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����22.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����23.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����24.jpg"));
		putimage(0, 0, &img);
		Sleep(W);
		loadimage(&img, _T("src/������/��ͷ����25.jpg"));
		putimage(0, 0, &img);
	}
}

void LoadBackground()
{
	IMAGE img;
	switch (degree)
	{
	case 1:loadimage(&img, _T("src/������/����1.jpg")); break;
	case 2:loadimage(&img, _T("src/������/����2.jpg")); break;
	case 3:loadimage(&img, _T("src/������/����3.jpg")); break;
	case 4:loadimage(&img, _T("src/������/����4.jpg")); break;
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
	/*����ͼƬΪ��Ϸ�����ͼƬ*/
	IMAGE img_restart;
	IMAGE img_suspend;
	IMAGE img_return;
	IMAGE img_tool;
	IMAGE img_prompt;

	board.Load_Image();
	board.JudgeMap();

	tim.Start();


	MOUSEMSG mousemsg;//�������������Ϣ�Ľṹ
	while (TRUE)
	{
		mousemsg = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
		switch (mousemsg.uMsg)
		{
		case WM_MOUSEMOVE:  //����ƶ�
		{
			FlushMouseMsgBuffer();  // ��������Ϣ������
			if (mousemsg.x >= 140 && mousemsg.x <= 384 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_restart, _T("src/������/restart.jpg")); 
				putimage(114, 0, &img_restart);
			}
			else if (mousemsg.x >= 440 && mousemsg.x <= 700 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_suspend, _T("src/������/suspend.jpg")); 
				putimage(414, 0, &img_suspend);
			}
			else if (mousemsg.x >= 750 && mousemsg.x <= 980 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_return, _T("src/������/return.jpg")); 
				putimage(731, 0, &img_return);
			}
			else if (mousemsg.x >= 1050 && mousemsg.x <= 1260 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				loadimage(&img_prompt, _T("src/������/prompt.jpg"));
				putimage(1150, 0, &img_prompt);
			}
			else
			{
				loadimage(&img_tool, _T("src/������/tool.jpg"));
				putimage(0, 0, &img_tool);
			}
			break;
		}
		case WM_LBUTTONDOWN:  //����������
		{
			FlushMouseMsgBuffer();  // ��������Ϣ������
			if (mousemsg.x >= 140 && mousemsg.x <= 384 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				tim.Stop();
				newGame();
			}
			else if (-1 == stop && mousemsg.x >= 440 && mousemsg.x <= 700 && mousemsg.y >= 20 && mousemsg.y <= 85)
			{
				if (1 == pause) {
					IMAGE img_pause;
					loadimage(&img_pause, _T("src/������/pause.jpg"));
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
								if (board.JudgeChoices())//����Ӧ���ж��ܷ�����
								{
									IMAGE img;
									int x = board.GetX0() + (board.map[xx][yy].get_x() - 1)*SIZE_OF_IMAGE;
									int y = board.GetY0() + (board.map[xx][yy].get_y() - 1)*SIZE_OF_IMAGE;
									board.LoadImageList(2, board.map[xx][yy].get_type(), img);
									putimage(x, y, &img);
									x = board.GetX0() + (board.map[xx2][yy2].get_x() - 1)*SIZE_OF_IMAGE;
									y = board.GetY0() + (board.map[xx2][yy2].get_y() - 1)*SIZE_OF_IMAGE;
									board.LoadImageList(2, board.map[xx2][yy2].get_type(), img);
									putimage(x, y, &img);//��������������������䰵������ʾЧ��
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
									if (board.JudgeChoices())//����Ӧ���ж��ܷ�����
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
		mciSendString(_T("play �����.mp3 repeat"), NULL, 0, NULL);
		music = 1;
	}
	else if (music == 1)
		mciSendString(_T("resume �����.mp3"), NULL, 0, NULL);
	else if (music == -1)
		mciSendString(_T("pause �����.mp3"), NULL, 0, NULL); 
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
