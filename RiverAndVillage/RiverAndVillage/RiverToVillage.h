#pragma once
#include <iostream>
#include <fstream>
//#include <iosfwd>
#define NUMBER_OF_VILLAGE 20
#define NUMBER_OF_EDGE 30
using namespace std;

typedef struct villageCoordinate {
	int index;
	int x;
	int y;
}Vil;

struct Edge {
	int preVallige;
	int postVallige;
};

class RiverToVillage
{
public:
	RiverToVillage(ifstream *file);//根据文件数据初始化类
	~RiverToVillage();
	void Part1B();
	void Part1C();
	void Part1D(int village1, int village2);
	void Part2B();
	void Part2D(int * villagesCanotToRiver, int number);
	void Part2E();
	void Part2F(int * villagesCanotToRiver,int number1, Edge * edgesCannotConnect, int number2);
private:
	void Delete(Vil *vallige, int index, int &num);//删除一个Vil数组中下标为index的数据，num减一
	int getNearestVallige(Vil *vallige, int num);//返回离河岸X最近的村庄的下标
	int getNearestVallige(Vil *vallige, int num, bool &xOry);//返回离河岸X或Y最近的村庄的下标，如果离河岸X更近则isX为true，否则为false
	void addEdge(int pre, int post);//增加一条连接村庄pre和村庄post的线路
	bool isBelongTo(int index, int * indics, int number);//判断indics中是否存在与index相等的值
	bool isProhibitionEdge(int pre, int post, Edge * edges, int number2);//判断边pre-post是否存在于edges
	int Min(int x, int y);//返回x和y的最小值
	void OutputFile(string filename);//输出结果文件
private:
	//图上村庄的总数
	int numberOfValliges;
	//已连线的总数
	int numberOfEdges = 0;
	//储存村庄的结构体数组
	Vil valliges[NUMBER_OF_VILLAGE];
	//储存线的结构体数组
	Edge edges[NUMBER_OF_EDGE];
};

