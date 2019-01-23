#pragma once
#include<thread>
#include <iostream>  
#include <cstdlib>  
#include <ctime>  
#include <conio.h>  
#include <iomanip>  
#include <windows.h>  
#include<graphics.h>
#pragma comment (lib, "winmm.lib")

using namespace std;

class Timer
{
private:
	long start_time;
	long pause_time;
	long show_time;
	//����boolֵ�������״̬   
	bool is_pause; //��¼��ʱ����״̬ ���Ƿ�����ͣ״̬��  
	bool is_stop;//�Ƿ���ֹͣ״̬   
public:
	Timer();
	bool isPause(); //���ؼ�ʱ��״̬   
	bool isStop();
	//��ʱ�������ֶ��������ܣ�   
	void Start();
	void Pause();
	void Stop();
	inline long getStartTime() { return start_time; }
	void show();
	long getShowTime() { return show_time; }
private:
	void LoadFigureImage(int figure, int digit);
};

Timer::Timer()
{
	is_pause = false; //��ʼ����ʱ��״̬   
	is_stop = true;
}


bool Timer::isPause()
{
	if (is_pause)
		return true;
	else
		return false;
}

bool Timer::isStop()
{
	if (is_stop)
		return true;
	return false;
}

void Timer::Start() //��ʼ   
{
	if (is_stop)
	{
		start_time = time(0);
		is_stop = false;
	}
	else if (is_pause)
	{
		is_pause = false;
		start_time += time(0) - pause_time; //���¿�ʼʱ�䣺�ô�ʱ��ʱ�� - ��ͣʱ���õ�ʱ�� + ��һ�ο�ʼ��ʱ�� = ��ʱ�Ŀ�ʼʱ��   
	}
}

void Timer::Pause() //��ͣ   
{
	if (is_stop || is_pause) //�������ֹͣ/��ͣ״̬,�˶��������κδ���ֱ�ӷ���   
		return;
	else    //�������Ϊ��ͣ״̬  
	{
		is_pause = true;
		pause_time = time(0); //��ȡ��ͣʱ��   
	}
}
void Timer::Stop()  //ֹͣ   
{
	if (is_stop) //���������ֹͣ״̬��������ͣ״̬���������κδ���   
		return;
	else if (is_pause) //�ı��ʱ��״̬   
	{
		is_pause = false;
		is_stop = true;
	}
	else if (!is_stop)
	{
		is_stop = true;
	}
}

void Timer::show()
{
	show_time = time(0) - start_time;
	LoadFigureImage(show_time / 100, 3);
	LoadFigureImage(show_time / 10 % 10, 2);
	LoadFigureImage(show_time % 10, 1);
}

inline void Timer::LoadFigureImage(int figure, int digit)
{
	IMAGE img;
	switch (figure)
	{
	case 0:loadimage(&img, _T("src/Timer/0.jpg")); break;
	case 1:loadimage(&img, _T("src/Timer/1.jpg")); break;
	case 2:loadimage(&img, _T("src/Timer/2.jpg")); break;
	case 3:loadimage(&img, _T("src/Timer/3.jpg")); break;
	case 4:loadimage(&img, _T("src/Timer/4.jpg")); break;
	case 5:loadimage(&img, _T("src/Timer/5.jpg")); break;
	case 6:loadimage(&img, _T("src/Timer/6.jpg")); break;
	case 7:loadimage(&img, _T("src/Timer/7.jpg")); break;
	case 8:loadimage(&img, _T("src/Timer/8.jpg")); break;
	case 9:loadimage(&img, _T("src/Timer/9.jpg")); break;
	default:
		break;
	}
	switch (digit)
	{
	case 1:putimage(1302, 227, &img); break;
	case 2:putimage(1271, 227, &img); break;
	case 3:putimage(1240, 227, &img); break;
	default:
		break;
	}
}
