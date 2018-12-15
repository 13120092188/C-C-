#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define SIZE 20
#define INF 1000000

typedef struct Vex {
	int num;        //Spot Number
	string name;    //Spot Name
	string desc;    //Spot Instruction
}Vex;

typedef struct Edge {
	int vex1;        //The first vertex of the edge
	int vex2;        //The second vertex of the edge
	int weight;      //Weight
}Edge;

class CGraph
{
private:
	int m_aAdjMatrix[20][20] = {0};
	Vex m_aVexs[20];
	int m_nVexNum;
	Edge m_aEdges[30];
	int m_nEdgeNum;
public:
	CGraph();
	~CGraph();
	void CreateGraph();
	void DisplayGraph(); //显示地图信息
	void QuerySpot();
	Vex GetVex(int nVex);
	int FindEdge(int nVex, Edge aEdge[]);
	void QueryPath();
	void DFSTraverse(int nVex, string path[], int &numOfPath);
	void DFS(int *visit, int nVex, string path[], int &numOfPath, string &path_tmp);//深度优先搜索核心算法
	void FindShortestPath();
	int DIJ(int numOfOrigin, int numOfDes, string & shortestPath);
	void CircuitPlanning();
	int PRIM(Edge *edge, int &numberOfEdge);
};

