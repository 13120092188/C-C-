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
	RiverToVillage(ifstream *file);//�����ļ����ݳ�ʼ����
	~RiverToVillage();
	void Part1B();
	void Part1C();
	void Part1D(int village1, int village2);
	void Part2B();
	void Part2D(int * villagesCanotToRiver, int number);
	void Part2E();
	void Part2F(int * villagesCanotToRiver,int number1, Edge * edgesCannotConnect, int number2);
private:
	void Delete(Vil *vallige, int index, int &num);//ɾ��һ��Vil�������±�Ϊindex�����ݣ�num��һ
	int getNearestVallige(Vil *vallige, int num);//������Ӱ�X����Ĵ�ׯ���±�
	int getNearestVallige(Vil *vallige, int num, bool &xOry);//������Ӱ�X��Y����Ĵ�ׯ���±꣬�����Ӱ�X������isXΪtrue������Ϊfalse
	void addEdge(int pre, int post);//����һ�����Ӵ�ׯpre�ʹ�ׯpost����·
	bool isBelongTo(int index, int * indics, int number);//�ж�indics���Ƿ������index��ȵ�ֵ
	bool isProhibitionEdge(int pre, int post, Edge * edges, int number2);//�жϱ�pre-post�Ƿ������edges
	int Min(int x, int y);//����x��y����Сֵ
	void OutputFile(string filename);//�������ļ�
private:
	//ͼ�ϴ�ׯ������
	int numberOfValliges;
	//�����ߵ�����
	int numberOfEdges = 0;
	//�����ׯ�Ľṹ������
	Vil valliges[NUMBER_OF_VILLAGE];
	//�����ߵĽṹ������
	Edge edges[NUMBER_OF_EDGE];
};

