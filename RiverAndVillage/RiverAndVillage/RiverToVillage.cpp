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

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for ( ; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//��X��ĺӿ���һ������Ĵ�ׯ���뵽��ׯ������
	Vil valligeDone[NUMBER_OF_VILLAGE];//�Ѿ������ߵĴ�ׯ
	//Ѱ���������Ĵ�ׯ��Ϊ��һ����ʼ���ߵĴ�ׯ
	int numberOfWaited = numberOfValliges + 1;//��û�������ߵĴ�ׯ��Ŀ
	int y = getNearestVallige(valligeWaited, numberOfWaited);//��������ׯ���±�
	valligeDone[0] = valligeWaited[y];//���������Ĵ�ׯ��ʼ����
	int numberOfDone = 1;//�Ѿ������ߵĴ�ׯ
	//addEdge(RIVER_X, valligeWaited[y].index);
	Delete(valligeWaited, y, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ

	double Distance = 0;
	int dddd = 1;
	while (0 != numberOfWaited)//��û�������ߵĴ�ׯ��Ϊ0ʱ����
	{
		int preIndexOfMin = -1;//�����������ׯ�ı��
		int postIndexOfMin = -1;//�����������ׯ�ı��
		double minAll = valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)].y;//���ڴ������ѭ���е���Сֵ
		for (int k = 1; k < numberOfDone; k++)
		{
			double min = minAll + 1;//�����ڲ�ѭ���е���Сֵ
			int m = 0;//��ׯ�����Ϣ
			int n = 0;//��ׯ�����Ϣ
			for (int j = 0; j < numberOfWaited; j++)
			{
				if (sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2)) < min)//Ѱ����Сmin
				{
					n = valligeDone[k].index;
					m = j;
					min = sqrt(pow(valligeWaited[j].x - valligeDone[k].x, 2) + pow(valligeWaited[j].y - valligeDone[k].y, 2));
				}
			}
			if (min < minAll)//Ѱ����СminAll
			{
				minAll = min;
				postIndexOfMin = m;
				preIndexOfMin = n;
			}
		}
		Distance += minAll;
		if (-1 == postIndexOfMin)//�״θ�ֵ��֮����жϻ�ֵ
		{
			addEdge(RIVER_X, valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)].index);
			valligeDone[numberOfDone] = valligeWaited[getNearestVallige(valligeWaited, numberOfWaited)];
			numberOfDone++;//������ׯ����һ
			Delete(valligeWaited, getNearestVallige(valligeWaited, numberOfWaited), numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;//������ׯ����һ
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
		}
		
	}
	cout << "��̵����߾����ǣ�" << Distance << endl;
	OutputFile("result1b.txt");
}

void RiverToVillage::Part1C()
{
	numberOfEdges = 0;
	

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for ( ; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//��X��ĺӿ���һ������Ĵ�ׯ���뵽��ׯ������
	valligeWaited[++i] = Vil{ RIVER_Y, 0, 0 };//��X��ĺӿ���һ������Ĵ�ׯ���뵽��ׯ������
	Vil valligeDone[NUMBER_OF_VILLAGE];//�Ѿ������ߵĴ�ׯ
									   //Ѱ���������Ĵ�ׯ��Ϊ��һ����ʼ���ߵĴ�ׯ
	int numberOfWaited = numberOfValliges + 2;//��û�������ߵĴ�ׯ��Ŀ
	bool isX = true;
	//int y = getNearestVallige(valligeWaited, numberOfVallige, isX);//��������ׯ���±�
	valligeDone[0] = valligeWaited[16];//���������Ĵ�ׯ��ʼ����
	valligeDone[1] = valligeWaited[17];//���������Ĵ�ׯ��ʼ����
	int numberOfDone = 2;//�Ѿ������ߵĴ�ׯ
	
	Delete(valligeWaited, 16, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	Delete(valligeWaited, 17, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ

	double Distance = 0;
	while (0 != numberOfWaited)//��û�������ߵĴ�ׯ��Ϊ0ʱ����
	{
		int preIndexOfMin = -1;//�����������ׯ�ı��
		int postIndexOfMin = -1;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);
		double minAll;
		if(isX)//����X�����
			minAll = valligeWaited[index].y;
		else//����Y�����
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

		if (-1 == postIndexOfMin)//�״θ�ֵ��֮����жϻ�ֵ
		{
			if (isX)
			{
				addEdge(RIVER_X, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;//������ׯ����һ
				Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			}
			else
			{
				addEdge(RIVER_Y, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;//������ׯ����һ
				Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			}
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
		}
	}

	cout << "��������̾���Ϊ��" << Distance << endl;
	OutputFile("result1c.txt");
}

void RiverToVillage::Part1D(int village1, int village2)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	valligeWaited[i] = Vil{ RIVER_X, 0, 0 };//��X��ĺӿ���һ������Ĵ�ׯ���뵽��ׯ������
	valligeWaited[++i] = Vil{ RIVER_Y, 0, 0 };//��X��ĺӿ���һ������Ĵ�ׯ���뵽��ׯ������
	Vil valligeDone[NUMBER_OF_VILLAGE];//�Ѿ������ߵĴ�ׯ
	int numberOfWaited = numberOfValliges + 2;//��û�������ߵĴ�ׯ��Ŀ
	bool isX = true;
	valligeDone[0] = valligeWaited[16];//���������Ĵ�ׯ��ʼ����
	valligeDone[1] = valligeWaited[17];//���������Ĵ�ׯ��ʼ����
	int numberOfDone = 2;//�Ѿ������ߵĴ�ׯ
	Delete(valligeWaited, 16, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	Delete(valligeWaited, 17, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ

	
	double Distance = 0;
	while (0 != numberOfWaited)//��û�������ߵĴ�ׯ��Ϊ0ʱ����
	{
		int preIndexOfMin = -1;//�����������ׯ�ı��
		int postIndexOfMin = -1; //�����������ׯ�ı��
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);
		double minAll;
		if (isX)//����X�����
			minAll = valligeWaited[index].y;
		else//����Y�����
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
			//����������ũ������
			valligeDone[numberOfDone] = valligeWaited[village2];//��ӵ�����ũ����
			numberOfDone++;
			int i2 = 0;
			for ( ; i2 < numberOfWaited; i2++) {
				if (valligeWaited[i2].index == village2)
					break;
			}
			Delete(valligeWaited, i2, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			addEdge(village1, village2);
		}
		else if (village2 == valligeWaited[postIndexOfMin].index || village2 == valligeWaited[index].index)
		{
			//����������ũ������
			valligeDone[numberOfDone] = valligeWaited[village1];//��ӵ�����ũ����
			numberOfDone++;
			int i2 = 0;
			for (; i2 < numberOfWaited; i2++) {
				if (valligeWaited[i2].index == village1)
					break;
			}
			Delete(valligeWaited, i2, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			addEdge(village1, village2);
		}

		if (-1 == postIndexOfMin)//�״θ�ֵ��֮����жϻ�ֵ
		{
			if (isX)
			{
				addEdge(RIVER_X, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;
				Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			}
			else
			{
				addEdge(RIVER_Y, valligeWaited[index].index);
				valligeDone[numberOfDone] = valligeWaited[index];
				numberOfDone++;
				Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
			}
		}
		else {
			addEdge(preIndexOfMin, valligeWaited[postIndexOfMin].index);
			valligeDone[numberOfDone] = valligeWaited[postIndexOfMin];
			numberOfDone++;
			Delete(valligeWaited, postIndexOfMin, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
		}
	}

	Distance += sqrt(pow(valliges[village1].x - valliges[village2].x, 2) + pow(valliges[village1].y - valliges[village2].y, 2));
	cout << "���������̾���Ϊ��" << Distance << endl;
	OutputFile("result1d.txt");
}

void RiverToVillage::Part2B()
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//��û�������ߵĴ�ׯ��Ŀ
	double totalCost = 0;//�ܳɱ�
	while (0 != numberOfWaited)
	{
		int index = getNearestVallige(valligeWaited, numberOfWaited);//��������ׯ���±�
		totalCost += valligeWaited[index].y;
		addEdge(RIVER_X, valligeWaited[index].index);
		Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	}
	cout << "һ�����������ܳɱ���" << totalCost << endl;
	OutputFile("result2b.txt");
}

void RiverToVillage::Part2D(int * villagesCanotToRiver, int number)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//��û�������ߵĴ�ׯ��Ŀ
	Vil valligeDone[NUMBER_OF_VILLAGE];//�Ѿ������ߵĴ�ׯ
	int numberOfDone = 0;//�Ѿ������ߵĴ�ׯ
	Vil villagesCannot[NUMBER_OF_VILLAGE];//������������Ĵ�ׯ
	int numberOfCannot = 0;//����������Ĵ�ׯ��
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
	double totalCost = 0;//�ܳɱ�
	while (0 != numberOfWaited)
	{
		int index = getNearestVallige(valligeWaited, numberOfWaited);//��������ׯ���±�
		totalCost += valligeWaited[index].y;
		addEdge(RIVER_X, valligeWaited[index].index);
		valligeDone[numberOfDone] = valligeWaited[index];
		numberOfDone++;
		Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	}

	while (0 != numberOfCannot)//���������ƵĴ�ׯ
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
				if (sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + valligeDone[j].y < min || -1 == min)//Ѱ����Сmin
				{
					tag = valligeDone[j].index;
					min = sqrt(pow(villagesCannot[x].x - valligeDone[j].x, 2) + pow(villagesCannot[x].y - valligeDone[j].y, 2)) + valligeDone[j].y;
				}
			}
			if (min < minAll || -1 == minAll) {//Ѱ����СminAll
				minAll = min;
				n = tag;
				m = x;
			}
		}
		totalCost += minAll;

		addEdge(n, villagesCannot[m].index);
		Delete(villagesCannot, m, numberOfCannot);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
		
	}

	cout << "һ�����������ܳɱ���" << totalCost << endl;
	OutputFile("result2d.txt");
}

void RiverToVillage::Part2E()
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//��û�������ߵĴ�ׯ��Ŀ
	double totalCost = 0;//�ܳɱ�
	while (0 != numberOfWaited)
	{
		bool isX = true;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);//��������ׯ���±�
		if (isX) {
			totalCost += valligeWaited[index].y;
			addEdge(RIVER_X, valligeWaited[index].index);
		}
		else {
			totalCost += valligeWaited[index].x;
			addEdge(RIVER_Y, valligeWaited[index].index);
		}
			
		Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	}

	cout << "�������������ܳɱ���" << totalCost << endl;
	OutputFile("result2e.txt");
}

void RiverToVillage::Part2F(int * villagesCanotToRiver,int number1, Edge * edgesCannotConnect, int number2)
{
	numberOfEdges = 0;

	Vil valligeWaited[NUMBER_OF_VILLAGE];//�ȴ����ߵĴ�ׯ����ʼ�����Ϊ���д�ׯ
	int i = 0;
	for (; i < numberOfValliges; i++)
		valligeWaited[i] = valliges[i];
	int numberOfWaited = numberOfValliges;//��û�������ߵĴ�ׯ��Ŀ
	Vil valligeDone[NUMBER_OF_VILLAGE];//�Ѿ������ߵĴ�ׯ
	int numberOfDone = 0;//�Ѿ������ߵĴ�ׯ
	Vil villagesCannot[NUMBER_OF_VILLAGE];//������������Ĵ�ׯ
	int numberOfCannot = 0;//����������Ĵ�ׯ��
	for (int k = 0; k < number1; k++) {//�������ƵĴ峤�洢��villagesCannot��
		for (int j = 0; j < numberOfWaited; j++) {
			if (villagesCanotToRiver[k] == valligeWaited[j].index) {
				villagesCannot[k] = valligeWaited[j];
				numberOfCannot++;
				Delete(valligeWaited, j, numberOfWaited);
				break;
			}
		}
	}
	double totalCost = 0;//�ܳɱ�
	while (0 != numberOfWaited)//�Ƚ��������ƵĴ�ׯֱ������ý��ĺ�����
	{
		bool isX = true;
		int index = getNearestVallige(valligeWaited, numberOfWaited, isX);//��������ׯ���±�
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
		Delete(valligeWaited, index, numberOfWaited);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ
	}

	while (0 != numberOfCannot)//���������ƵĴ�ׯ���ҵ�������·��
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
		Delete(villagesCannot, m, numberOfCannot);//���Ѿ������ߵĴ�ׯ�ӵȴ����ߵĴ�ׯ����ȥ

	}

	cout << "�������������ܳɱ���" << totalCost << endl;
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
