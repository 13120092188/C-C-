#include "Board.hpp"
#include <string>
#include <windows.h>
#include<graphics.h>
#include <time.h>
//#pragma comment (lib, "winmm.lib")



Board::Board()
{
}


Board::~Board()
{
}

void Board::SetBoard(int x, int y, int repeat)
{
	dimensionX = x;
	dimensionY = y;
	for (int i = 0; i < x*y/repeat; i++){
		for (int j = 0; j < repeat; j++) {
			Block block(i*repeat+j, i, "L" + to_string(i));
			blocks.push_back(block);
		}
	}
	srand((unsigned)time(NULL)); /*定义这个可以产生不同的随机数*/
	random_shuffle(blocks.begin(), blocks.end());     //将blocks随机排序
	for (int i = 0; i <= x+1; i++){
		for (int j = 0; j <= y+1; j++) {
			if (i == 0 || j == 0 || i == x + 1 || j == y + 1) {
				Block block(0, 0, "0");
				map[i][j] = block;
			}
			else {
				map[i][j] = blocks.back();
				map[i][j].disappear();
				blocks.pop_back();
			}
		}
	}

	SetXY();
}

void Board::ClearBoard()
{
	ReNewChoices();
	dimensionX = 0;
	dimensionY = 0;
	ans = 0;
}

void Board::Load_Image()
{
	for (int i = 1; i <= dimensionX; i++) {
		for (int j = 1; j <= dimensionY; j++) {
			IMAGE img;
			if (false == map[i][j].get_appear())
				loadimage(&img, _T("src/bong/bong12.jpg"));
			else
				LoadImageList(1, map[i][j].get_type(), img);
			putimage(X0 + (map[i][j].get_x()-1)*SIZE_OF_IMAGE, Y0 + (map[i][j].get_y()-1)*SIZE_OF_IMAGE, &img);
		}
	}
	
}

void Board::LoadImageList(int type, int n, IMAGE &img)
{
	switch (type)
	{
	case 1: {
		switch (n)
		{
		case 0: loadimage(&img, _T("src/彩色方块/block0.jpg")); break;
		case 1: loadimage(&img, _T("src/彩色方块/block1.jpg")); break;
		case 2: loadimage(&img, _T("src/彩色方块/block2.jpg")); break;
		case 3: loadimage(&img, _T("src/彩色方块/block3.jpg")); break;
		case 4: loadimage(&img, _T("src/彩色方块/block4.jpg")); break;
		case 5: loadimage(&img, _T("src/彩色方块/block5.jpg")); break;
		case 6: loadimage(&img, _T("src/彩色方块/block6.jpg")); break;
		case 7: loadimage(&img, _T("src/彩色方块/block7.jpg")); break;
		case 8: loadimage(&img, _T("src/彩色方块/block8.jpg")); break;
		case 9: loadimage(&img, _T("src/彩色方块/block9.jpg")); break;
		case 10: loadimage(&img, _T("src/彩色方块/block10.jpg")); break;
		case 11: loadimage(&img, _T("src/彩色方块/block11.jpg")); break;
		case 12: loadimage(&img, _T("src/彩色方块/block12.jpg")); break;
		case 13: loadimage(&img, _T("src/彩色方块/block13.jpg")); break;
		case 14: loadimage(&img, _T("src/彩色方块/block14.jpg")); break;
		case 15: loadimage(&img, _T("src/彩色方块/block15.jpg")); break;
		case 16: loadimage(&img, _T("src/彩色方块/block16.jpg")); break;
		case 17: loadimage(&img, _T("src/彩色方块/block17.jpg")); break;
		case 18: loadimage(&img, _T("src/彩色方块/block18.jpg")); break;
		case 19: loadimage(&img, _T("src/彩色方块/block19.jpg")); break;
		case 20: loadimage(&img, _T("src/彩色方块/block20.jpg")); break;
		case 21: loadimage(&img, _T("src/彩色方块/block21.jpg")); break;
		case 22: loadimage(&img, _T("src/彩色方块/block22.jpg")); break;
		case 23: loadimage(&img, _T("src/彩色方块/block23.jpg")); break;
		case 24: loadimage(&img, _T("src/彩色方块/block24.jpg")); break;
		case 25: loadimage(&img, _T("src/彩色方块/block25.jpg")); break;
		case 26: loadimage(&img, _T("src/彩色方块/block26.jpg")); break;
		case 27: loadimage(&img, _T("src/彩色方块/block27.jpg")); break;
		case 28: loadimage(&img, _T("src/彩色方块/block28.jpg")); break;
		case 29: loadimage(&img, _T("src/彩色方块/block29.jpg")); break;
		case 30: loadimage(&img, _T("src/彩色方块/block30.jpg")); break;
		case 31: loadimage(&img, _T("src/彩色方块/block31.jpg")); break;
		case 32: loadimage(&img, _T("src/彩色方块/block32.jpg")); break;
		case 33: loadimage(&img, _T("src/彩色方块/block33.jpg")); break;
		default:
			break;
		}
	}
		break;
	case 2: {
		switch (n)
		{
		case 0: loadimage(&img, _T("src/彩色方块2/block0.jpg")); break;
		case 1: loadimage(&img, _T("src/彩色方块2/block1.jpg")); break;
		case 2: loadimage(&img, _T("src/彩色方块2/block2.jpg")); break;
		case 3: loadimage(&img, _T("src/彩色方块2/block3.jpg")); break;
		case 4: loadimage(&img, _T("src/彩色方块2/block4.jpg")); break;
		case 5: loadimage(&img, _T("src/彩色方块2/block5.jpg")); break;
		case 6: loadimage(&img, _T("src/彩色方块2/block6.jpg")); break;
		case 7: loadimage(&img, _T("src/彩色方块2/block7.jpg")); break;
		case 8: loadimage(&img, _T("src/彩色方块2/block8.jpg")); break;
		case 9: loadimage(&img, _T("src/彩色方块2/block9.jpg")); break;
		case 10: loadimage(&img, _T("src/彩色方块2/block10.jpg")); break;
		case 11: loadimage(&img, _T("src/彩色方块2/block11.jpg")); break;
		case 12: loadimage(&img, _T("src/彩色方块2/block12.jpg")); break;
		case 13: loadimage(&img, _T("src/彩色方块2/block13.jpg")); break;
		case 14: loadimage(&img, _T("src/彩色方块2/block14.jpg")); break;
		case 15: loadimage(&img, _T("src/彩色方块2/block15.jpg")); break;
		case 16: loadimage(&img, _T("src/彩色方块2/block16.jpg")); break;
		case 17: loadimage(&img, _T("src/彩色方块2/block17.jpg")); break;
		case 18: loadimage(&img, _T("src/彩色方块2/block18.jpg")); break;
		case 19: loadimage(&img, _T("src/彩色方块2/block19.jpg")); break;
		case 20: loadimage(&img, _T("src/彩色方块2/block20.jpg")); break;
		case 21: loadimage(&img, _T("src/彩色方块2/block21.jpg")); break;
		case 22: loadimage(&img, _T("src/彩色方块2/block22.jpg")); break;
		case 23: loadimage(&img, _T("src/彩色方块2/block23.jpg")); break;
		case 24: loadimage(&img, _T("src/彩色方块2/block24.jpg")); break;
		case 25: loadimage(&img, _T("src/彩色方块2/block25.jpg")); break;
		case 26: loadimage(&img, _T("src/彩色方块2/block26.jpg")); break;
		case 27: loadimage(&img, _T("src/彩色方块2/block27.jpg")); break;
		case 28: loadimage(&img, _T("src/彩色方块2/block28.jpg")); break;
		case 29: loadimage(&img, _T("src/彩色方块2/block29.jpg")); break;
		case 30: loadimage(&img, _T("src/彩色方块2/block30.jpg")); break;
		case 31: loadimage(&img, _T("src/彩色方块2/block31.jpg")); break;
		case 32: loadimage(&img, _T("src/彩色方块2/block32.jpg")); break;
		case 33: loadimage(&img, _T("src/彩色方块2/block33.jpg")); break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
	
}

bool Board::JudgeChoices()
{
	if (map[choices[0].i][choices[0].j].get_type() == map[choices[1].i][choices[1].j].get_type())
	{
		ans = 0;
		map[choices[1].i][choices[1].j].disappear();
		map[choices[0].i][choices[0].j].disappear();
		dfs(-1, 0, map[choices[0].i][choices[0].j].get_x(), map[choices[0].i][choices[0].j].get_y(), map[choices[1].i][choices[1].j]);
		map[choices[1].i][choices[1].j].disappear();
		map[choices[0].i][choices[0].j].disappear();
		return ans;
	}
	else
		return false;
}

void Board::EliminateBlock()
{
	map[choices[0].i][choices[0].j].disappear();
	map[choices[1].i][choices[1].j].disappear();
}

void Board::ReNewChoices()
{
	choices[0].i = -1;
	choices[0].j = -1;
	choices[1].i = -1;
	choices[1].j = -1;
}

void Board::JudgeMap()
{
	bool b = true;
	for (int i = 1; i <= dimensionX; i++) {
		for (int j = 1; j <= dimensionY; j++) {
			if (true == map[i][j].get_appear()) {
				for (int i1 = i; i1 <= dimensionX; i1++) {
					for (int j1 = j+1; j1 <= dimensionY; j1++) {
						if (true == map[i1][j1].get_appear()) {
							if (map[i][j].get_type() == map[i1][j1].get_type())
							{
								ans = 0;
								map[i1][j1].disappear();
								map[i][j].disappear();
								dfs(-1, 0, map[i][j].get_x(), map[i][j].get_y(), map[i1][j1]);
								map[i1][j1].disappear();
								map[i][j].disappear();
								if (ans)
									b = false;
							}
						}
					}
				}
			}
		}
	}
	if (b && !IsEnd()) {
		RefreshMap();
		Load_Image();
	}
}

void Board::RefreshMap()
{
	vector<Block> blockss;
	Map position[200];
	int index = 0;
	for (int i = 1; i <= dimensionX; i++) {
		for (int j = 1; j <= dimensionY; j++) {
			if (true == map[i][j].get_appear()) {
				position[index].i = i;
				position[index].j = j;
				index++;
				blockss.push_back(map[i][j]);
			}
		}
	}
	srand((unsigned)time(NULL)); /*定义这个可以产生不同的随机数*/
	random_shuffle(blockss.begin(), blockss.end());     //将blocks随机排序
	for (int i = 0; i < index; i++) {
		map[position[i].i][position[i].j].set_type(blockss.back().get_type());
		map[position[i].i][position[i].j].set_appear(blockss.back().get_appear());
		blockss.pop_back();
	}
}

bool Board::IsEnd()
{
	for (int i = 1; i <= dimensionX; i++) {
		for (int j = 1; j <= dimensionY; j++) {
			if (true == map[i][j].get_appear())
				return false;
		}
	}
	return true;
}

void Board::SetXY()
{
	for (int i = 1; i <= dimensionX; i++) {
		for (int j = 1; j <= dimensionY; j++) {
			map[i][j].set_x(i);
			map[i][j].set_y(j);
		}
	}
}

void Board::dfs(int in, int num, int x, int y, Block bl)
{
	int x_p[4] = { 1, -1, 0, 0 };
	int y_p[4] = { 0, 0, 1, -1 };
	if (num <= 2) {
		if (x == bl.get_x() && y == bl.get_y()) ans = true;
		for (int i = 0; i < 4; i++) {
			if (map[x + x_p[i]][y + y_p[i]].get_appear() == false && x + x_p[i] >= 0 && x + x_p[i] <= dimensionX + 1 && y + y_p[i] >= 0 && y + y_p[i] <= dimensionY + 1) {
				if (i == in || in == -1) {
					map[x + x_p[i]][y + y_p[i]].disappear();
					dfs(i, num, x + x_p[i], y + y_p[i], bl);
					map[x + x_p[i]][y + y_p[i]].disappear();
				}
				else {
					map[x + x_p[i]][y + y_p[i]].disappear();
					dfs(i, num + 1, x + x_p[i], y + y_p[i], bl);
					map[x + x_p[i]][y + y_p[i]].disappear();
				}
			}
		}
	}
}

