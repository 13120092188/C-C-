#pragma once
#include"Block.h"
#include <algorithm>
#include <iostream>
#include <vector>
//#include <windows.h>
#include<graphics.h>
//#pragma comment (lib, "winmm.lib")
using namespace std;

//#define X0 100
//#define Y0 150
#define SIZE_OF_IMAGE 100
typedef struct Map{
	int i = -1;
	int j = -1;
}MAP;

class Board
{
public:
	Board();
	~Board();
	void SetBoard(int x, int y, int repeat);
	void ClearBoard();
	void RenewBoard();
	void SetChoices(int choice);
	void Load_Image();
	int GetDimensionX() { return dimensionX; }
	int GetDimensionY() { return dimensionY; }
	int GetNumberOfImage() { return dimensionX*dimensionY; }
	void LoadImageList(int type, int n, IMAGE &img);
	bool JudgeChoices();                               //判断choices[2]中的两个Block是否能消除
	void EliminateBlock();                             //消除choices[2]中的两个Block
	void ReNewChoices();
	void SetOriginXY(int x, int y) { X0 = x; Y0 = y; }
	int GetX0() { return X0; }
	int GetY0() { return Y0; }
	void JudgeMap();                                   //判断地图有没有可以连的了，有不刷新，否则刷新
	void RefreshMap();                                 //不能连就刷新
	bool IsEnd();
private:
	//void SetDimension(int x, int y);
	void SetXY();
	void dfs(int in, int num, int x, int y, Block bl);
	bool JudgeMapLineCore(int block1, int block2);     //判断block1到block2可不可以连
public:
	Block map[20][20];
	MAP choices[2];
private:
	vector<Block> blocks;
	int dimensionX = 0;
	int dimensionY = 0;
	bool ans = 0;
	int X0 = 0;
	int Y0 = 0;
};


