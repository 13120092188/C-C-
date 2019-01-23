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
	//两个bool值标记四种状态   
	bool is_pause; //记录计时器的状态 （是否处于暂停状态）  
	bool is_stop;//是否处于停止状态   
public:
	Timer();
	bool isPause(); //返回计时器状态   
	bool isStop();
	//计时器的三种动作（功能）   
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
	is_pause = false; //初始化计时器状态   
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

void Timer::Start() //开始   
{
	if (is_stop)
	{
		start_time = time(0);
		is_stop = false;
	}
	else if (is_pause)
	{
		is_pause = false;
		start_time += time(0) - pause_time; //更新开始时间：用此时的时间 - 暂停时所用的时间 + 上一次开始的时间 = 此时的开始时间   
	}
}

void Timer::Pause() //暂停   
{
	if (is_stop || is_pause) //如果处于停止/暂停状态,此动作不做任何处理，直接返回   
		return;
	else    //否则调制为暂停状态  
	{
		is_pause = true;
		pause_time = time(0); //获取暂停时间   
	}
}
void Timer::Stop()  //停止   
{
	if (is_stop) //如果正处于停止状态（不是暂停状态），不做任何处理   
		return;
	else if (is_pause) //改变计时器状态   
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
