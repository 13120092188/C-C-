#include "RiverToVillage.h"
#include <math.h>
//using namespace std;
#define RIVER_X 16
#define RIVER_Y 17

RiverToVillage::RiverToVillage(ifstream *file)
{
	*file >> numberOfValliges;
	for (int i = 0; i < numberOfValliges; i++)
	{
		valliges[i].index = i;
		*file >> valliges[i].x;
		*file >> valliges[i].y;
	}
}

RiverToVillage::~RiverToVillage()
{
}

void RiverToVillage::Part1B()
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for ( ; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//将X轴的河看做一个特殊的村庄加入到村庄数组中
	Vil valligeDone[NUMBER_OF_VILLAGE];//已经连上线的村庄
	//寻找离河最近的村庄作为第一个开始连线的村庄
	int numberOfWaited = numberOfValliges + 1;//还没有连上线的村庄数目
	int y = getNearestVallige(valligeWaited, numberOfWaited);//离河最近村庄的下标
	valligeDone[0] = valligeWaited[y];//从离河最近的村庄开始连线
	int numberOfDone = 1;//已经连上线的村庄
	//addEdge(RIVER_X, valligeWaited[y].index);
	Delete(valligeWaited, y, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去

	double Distance = 0;
	int dddd = 1;
	while (0 != numberOfWaited)//当没有连上线的村庄数为0时结束
	{
		int preIndexOfMin = -1;//最短线所连村庄的标号
		int postIndexOfMin = -1;//最短线所连村庄的标号
		double minAll = valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)].y;//用于储存外层循环中的最小值
		for (int k = 1; k < numberOfDone; k++)
		{
			double min = minAll + 1;//储存内层循环中的最小值
			int m = 0;//村庄编号信息
			int n = 0;//村庄编号信息
			for (int j = 0; j < numberOfWaited; j++)
			{
				if (sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2)) < min)//寻找最小min
				{
					n = valligeDone[k].index;
					m = j;
					min = sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2));
				}
			}
			if (min < minAll)//寻找最小minAll
			{
				minAll = min;
				postIndexOfMin = m;
				preIndexOfMin = n;
			}
		}
		Distance += minAll;
		if (-1 == postIndexOfMin)//首次赋值和之后的判断换值
		{
			addEdge(RIVER_X, valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)].index);
			valligeDone[numberOfDone] = valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)];
			numberOfDone++;//已连村庄数加一
			Delete(valligeWaited, getNearestVallige(valligeWaited, numberOfWaited), numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;//已连村庄数加一
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
		}
		
	}
	cout << "最短的连线距离是：" << Distance << endl;
	OutputFile("result1b.txt");
}

void RiverToVillage::Part1C()
{
	numberOfEdges = 0;
	

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for ( ; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//将X轴的河看做一个特殊的村庄加入到村庄数组中
	valligeWaited[++i] = Vil{ RIVER_Y, 0, 0 };//将X轴的河看做一个特殊的村庄加入到村庄数组中
	Vil valligeDone[NUMBER_OF_VILLAGE];//已经连上线的村庄
									   //寻找离河最近的村庄作为第一个开始连线的村庄
	int numberOfWaited = numberOfValliges + 2;//还没有连上线的村庄数目
	bool isX = true;
	//int y = getNearestVallige(valligeWaited, numberOfVallige, isX);//离河最近村庄的下标
	valligeDone[0] = valligeWaited[16];//从离河最近的村庄开始连线
	valligeDone[1] = valligeWaited[17];//从离河最近的村庄开始连线
	int numberOfDone = 2;//已经连上线的村庄
	
	Delete(valligeWaited, 16, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	Delete(valligeWaited, 17, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去

	double Distance = 0;
	while (0 != numberOfWaited)//当没有连上线的村庄数为0时结束
	{
		int preIndexOfMin = -1;//最短线所连村庄的标号
		int postIndexOfMin = -1;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);
		double minAll;
		if(isX)//距离X轴更近
			minAll = valligeWaited[index].y;
		else//距离Y轴更近
			minAll = valligeWaited[index].x;
		for (int k = 1; k < numberOfDone; k++)
		{
			double min = minAll + 1;
			int m = 0;
			int n = 0;
			for (int j = 0; j < numberOfWaited; j++)
			{
				if (sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2)) < min)
				{
					n = valligeDone[k].index;
					m = j;
					min = sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2));
				}
			}
			if (min < minAll)
			{
				minAll = min;
				postIndexOfMin = m;
				preIndexOfMin = n;
			}
		}

		Distance += minAll;

		if (-1 == postIndexOfMin)//首次赋值和之后的判断换值
		{
			if (isX)
			{
				addEdge(RIVER_X, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;//已连村庄数加一
				Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			}
			else
			{
				addEdge(RIVER_Y, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;//已连村庄数加一
				Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			}
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
		}
	}

	cout << "两条河最短距离为：" << Distance << endl;
	OutputFile("result1c.txt");
}

void RiverToVillage::Part1D(int village1, int village2)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//将X轴的河看做一个特殊的村庄加入到村庄数组中
	valligeWaited[++i] = Vil{ RIVER_Y, 0, 0 };//将X轴的河看做一个特殊的村庄加入到村庄数组中
	Vil valligeDone[NUMBER_OF_VILLAGE];//已经连上线的村庄
	int numberOfWaited = numberOfValliges + 2;//还没有连上线的村庄数目
	bool isX = true;
	valligeDone[0] = valligeWaited[16];//从离河最近的村庄开始连线
	valligeDone[1] = valligeWaited[17];//从离河最近的村庄开始连线
	int numberOfDone = 2;//已经连上线的村庄
	Delete(valligeWaited, 16, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	Delete(valligeWaited, 17, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去

	
	double Distance = 0;
	while (0 != numberOfWaited)//当没有连上线的村庄数为0时结束
	{
		int preIndexOfMin = -1;//最短线所连村庄的标号
		int postIndexOfMin = -1; //最短线所连村庄的标号
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);
		double minAll;
		if (isX)//距离X轴更近
			minAll = valligeWaited[index].y;
		else//距离Y轴更近
			minAll = valligeWaited[index].x;
		for (int k = 1; k < numberOfDone; k++)
		{
			double min = minAll + 1;
			int m = 0;
			int n = 0;
			for (int j = 0; j < numberOfWaited; j++)
			{
				if (sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2)) < min)
				{
					n = valligeDone[k].index;
					m = j;
					min = sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2));
				}
			}
			if (min < minAll)
			{
				minAll = min;
				postIndexOfMin = m;
				preIndexOfMin = n;
			}
		}
		Distance += minAll;
		if (village1 == valligeWaited[postIndexOfMin].index || village1 == valligeWaited[index].index)
		{
			//将必连的两农户相连
			valligeDone[numberOfDone] = valligeWaited[village2];//添加到已连农户中
			numberOfDone++;
			int i2 = 0;
			for ( ; i2 < numberOfWaited; i2++) {
				if (valligeWaited[i2].index == village2)
					break;
			}
			Delete(valligeWaited, i2, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			addEdge(village1, village2);
		}
		else if (village2 == valligeWaited[postIndexOfMin].index || village2 == valligeWaited[index].index)
		{
			//将必连的两农户相连
			valligeDone[numberOfDone] = valligeWaited[village1];//添加到已连农户中
			numberOfDone++;
			int i2 = 0;
			for (; i2 < numberOfWaited; i2++) {
				if (valligeWaited[i2].index == village1)
					break;
			}
			Delete(valligeWaited, i2, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			addEdge(village1, village2);
		}

		if (-1 == postIndexOfMin)//首次赋值和之后的判断换值
		{
			if (isX)
			{
				addEdge(RIVER_X, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;
				Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			}
			else
			{
				addEdge(RIVER_Y, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;
				Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
			}
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
		}
	}

	Distance += sqrt(pow(valliges[village1].x - valliges[village2].x, 2) + pow(valliges[village1].y - valliges[village2].y, 2));
	cout << "两村必连最短距离为：" << Distance << endl;
	OutputFile("result1d.txt");
}

void RiverToVillage::Part2B()
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//还没有连上线的村庄数目
	double totalCost = 0;//总成本
	while (0 != numberOfWaited)
	{
		int index = getNearestVallige(valligeWaited, numberOfWaited);//离河最近村庄的下标
		totalCost += valligeWaited[index].y;
		addEdge(RIVER_X, valligeWaited[index].index);
		Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	}
	cout << "一条河无限制总成本：" << totalCost << endl;
	OutputFile("result2b.txt");
}

void RiverToVillage::Part2D(int * villagesCanotToRiver, int number)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//还没有连上线的村庄数目
	Vil valligeDone[NUMBER_OF_VILLAGE];//已经连上线的村庄
	int numberOfDone = 0;//已经连上线的村庄
	Vil villagesCannot[NUMBER_OF_VILLAGE];//不能与河相连的村庄
	int numberOfCannot = 0;//不能与河连的村庄数
	for (int k = 0; k < number; k++) {
		for (int j = 0; j < numberOfWaited; j++) {
			if (villagesCanotToRiver[k] == valligeWaited[j].index) {
				villagesCannot[k] = valligeWaited[j];
				numberOfCannot++;
				Delete(valligeWaited, j, numberOfWaited);
				break;
			}
		}
	}
	double totalCost = 0;//总成本
	while (0 != numberOfWaited)
	{
		int index = getNearestVallige(valligeWaited, numberOfWaited);//离河最近村庄的下标
		totalCost += valligeWaited[index].y;
		addEdge(RIVER_X, valligeWaited[index].index);
		valligeDone[numberOfDone] = valligeWaited[index];
		numberOfDone++;
		Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	}

	while (0 != numberOfCannot)//处理受限制的村庄
	{
		double minAll = -1;
		int m = 0;
		int n = 0;
		for (int x = 0; x < numberOfCannot; x++)
		{
			double min = -1;
			int tag = 0;
			for (int j = 0; j < numberOfDone; j++)
			{
				if (sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + valligeDone[j].y < min || -1 == min)//寻找最小min
				{
					tag = valligeDone[j].index;
					min = sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + valligeDone[j].y;
				}
			}
			if (min < minAll || -1 == minAll) {//寻找最小minAll
				minAll = min;
				n = tag;
				m = x;
			}
		}
		totalCost += minAll;

		addEdge(n, villagesCannot[m].index);
		Delete(villagesCannot, m, numberOfCannot);//将已经连上线的村庄从等待连线的村庄中踢去
		
	}

	cout << "一条河有限制总成本：" << totalCost << endl;
	OutputFile("result2d.txt");
}

void RiverToVillage::Part2E()
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//还没有连上线的村庄数目
	double totalCost = 0;//总成本
	while (0 != numberOfWaited)
	{
		bool isX = true;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);//离河最近村庄的下标
		if (isX) {
			totalCost += valligeWaited[index].y;
			addEdge(RIVER_X, valligeWaited[index].index);
		}
		else {
			totalCost += valligeWaited[index].x;
			addEdge(RIVER_Y, valligeWaited[index].index);
		}
			
		Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	}

	cout << "两条河无限制总成本：" << totalCost << endl;
	OutputFile("result2e.txt");
}

void RiverToVillage::Part2F(int * villagesCanotToRiver,int number1, Edge * edgesCannotConnect, int number2)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//等待连线的村庄，初始情况下为所有村庄
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//还没有连上线的村庄数目
	Vil valligeDone[NUMBER_OF_VILLAGE];//已经连上线的村庄
	int numberOfDone = 0;//已经连上线的村庄
	Vil villagesCannot[NUMBER_OF_VILLAGE];//不能与河相连的村庄
	int numberOfCannot = 0;//不能与河连的村庄数
	for (int k = 0; k < number1; k++) {//将受限制的村长存储到villagesCannot中
		for (int j = 0; j < numberOfWaited; j++) {
			if (villagesCanotToRiver[k] == valligeWaited[j].index) {
				villagesCannot[k] = valligeWaited[j];
				numberOfCannot++;
				Delete(valligeWaited, j, numberOfWaited);
				break;
			}
		}
	}
	double totalCost = 0;//总成本
	while (0 != numberOfWaited)//先将不受限制的村庄直接与离得近的河相连
	{
		bool isX = true;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);//离河最近村庄的下标
		if (isX) {
			totalCost += valligeWaited[index].y;
			addEdge(RIVER_X, valligeWaited[index].index);
		}
		else {
			totalCost += valligeWaited[index].x;
			addEdge(RIVER_Y, valligeWaited[index].index);
		}
			
		valligeDone[numberOfDone] = valligeWaited[index];
		numberOfDone++;
		Delete(valligeWaited, index, numberOfWaited);//将已经连上线的村庄从等待连线的村庄中踢去
	}

	while (0 != numberOfCannot)//处理受限制的村庄，找到与河最近路径
	{
		double minAll = -1;
		int m = 0;
		int n = 0;
		for (int x = 0; x < numberOfCannot; x++)
		{
			double min = -1;
			int tag = 0;
			for (int j = 0; j < numberOfDone; j++)
			{
				if (sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + Min(valligeDone[j].x, valligeDone[j].y) < min || -1 == min)
				{
					if (!isProhibitionEdge(villagesCannot[x].index, valligeDone[j].index, edgesCannotConnect, number2))
					{
						tag = valligeDone[j].index;
						min = sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + Min(valligeDone[j].x, valligeDone[j].y);
					}
				}
			}
			if (min < minAll || -1 == minAll) {
				minAll = min;
				n = tag;
				m = x;
			}
		}
		totalCost += minAll;

		addEdge(n, villagesCannot[m].index);
		Delete(villagesCannot, m, numberOfCannot);//将已经连上线的村庄从等待连线的村庄中踢去

	}

	cout << "两条河有限制总成本：" << totalCost << endl;
	OutputFile("result2f.txt");
}


void RiverToVillage::Delete(Vil *vallige, int index, int &num)
{
	for (int i = index; i < num; i++)
		vallige[i] = vallige[i + 1];
	num--;
}


int RiverToVillage::getNearestVallige(Vil * vallige, int num)
{
	int min = vallige[0].y;
	int index = vallige[0].index;
	for (int i = 0; i < num; i++) {
		if (vallige[i].y <= min)
		{
			min = vallige[i].y;
			index = i;
		}
	}
	return index;
	
}

int RiverToVillage::getNearestVallige(Vil * vallige, int num, bool & isX)
{
	int minX = vallige[0].y;
	int minY = vallige[0].x;
	int indexX = vallige[0].index;
	int indexY = vallige[0].index;
	for (int i = 0; i < num; i++) {
		if (vallige[i].y <= minX)
		{
			minX = vallige[i].y;
			indexX = i;
		}
		if (vallige[i].x <= minY)
		{
			minY = vallige[i].x;
			indexY = i;
		}
	}
	if (minY < minX) {
		isX = false;
		return indexY;
	}
	else {
		isX = true;
		return indexX;
	}
}

void RiverToVillage::addEdge(int pre, int post)
{
	edges[numberOfEdges].preVallige = pre;
	edges[numberOfEdges].postVallige = post;
	numberOfEdges++;
}

bool RiverToVillage::isBelongTo(int index, int * indics, int number)
{
	for (int i = 0; i < number; i++) {
		if (index == indics[i])
			return true;
	}
	return false;
}

bool RiverToVillage::isProhibitionEdge(int pre, int post, Edge * edges, int number2)
{
	for (int i = 0; i < number2; i++)
	{
		if ((pre == edges[i].preVallige && post == edges[i].postVallige) || (pre == edges[i].postVallige && post == edges[i].preVallige))
			return true;
	}
	return false;
}

int RiverToVillage::Min(int x, int y)
{
	if (x > y)
		return y;
	else
		return x;
}

void RiverToVillage::OutputFile(string filename)
{
	ofstream out;
	out.open(filename, ios::trunc);
	for (int i = 0; i < numberOfEdges; i++)
	{
		out << edges[i].preVallige;
		out << ", ";
		out << edges[i].postVallige;
		out << "\n";
	}
	out.close();
}
