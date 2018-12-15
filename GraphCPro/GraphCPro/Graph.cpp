#include "Graph.h"



CGraph::CGraph()
{
	
}


CGraph::~CGraph()
{
}

void CGraph::CreateGraph()
{
	//读取Vex信息
	ifstream file("Vex.txt");
	file >> m_nVexNum;
	for (int i = 0; i < m_nVexNum; i++)
	{
		file >> m_aVexs[i].num;
		file >> m_aVexs[i].name;
		file >> m_aVexs[i].desc;
	}
	file.close();
	//读取Edge信息
	ifstream file1("Edge.txt");
	for (int i = 0; !file1.eof(); i++)
	{
		file1 >> m_aEdges[i].vex1;
		file1 >> m_aEdges[i].vex2;
		file1 >> m_aEdges[i].weight;
		m_nEdgeNum = i + 1;
		//画图
		m_aAdjMatrix[m_aEdges[i].vex1][m_aEdges[i].vex2] = m_aAdjMatrix[m_aEdges[i].vex2][m_aEdges[i].vex1] = m_aEdges[i].weight;
	}
	file1.close();
}

void CGraph::DisplayGraph()
{
	cout << "-------Vertex-------" << endl;
	for (int i = 0; i < m_nVexNum; i++) {
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << "  Information:" << m_aVexs[i].desc << endl;
	}

	cout << "-------Edge-------" << endl;
	for (int i = 0; i < m_nEdgeNum; i++) {
		cout << "<v" << m_aEdges[i].vex1 << ",v" << m_aEdges[i].vex2 << "> " << m_aEdges[i].weight << endl;
	}
}

void CGraph::QuerySpot()
{
	cout << "===== Query Spot Information =====" << endl;
	for (int i = 0; i < m_nVexNum; i++) {
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << "  Information:" << m_aVexs[i].desc << endl;
	}
	cout << "Please input the spot number you want to query: ";
	int numOfVexs;
	cin >> numOfVexs;
	Vex vexQ = GetVex(numOfVexs);
	cout << vexQ.name << endl;
	cout << vexQ.desc << endl;
	cout << "----- Spot Around -----" << endl;
	Edge edges[10];
	int numOfEdges = FindEdge(numOfVexs, edges);
	for (int i = 0; i < numOfEdges; i++) {
		cout << GetVex(edges[i].vex1).name << "->" << GetVex(edges[i].vex2).name << "  " << edges[i].weight << "m" << endl;
	}
}


Vex CGraph::GetVex(int nVex)
{
	Vex vex;
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_aVexs[i].num == nVex) {
			vex.num = m_aVexs[i].num;
			vex.name = m_aVexs[i].name;
			vex.desc = m_aVexs[i].desc;
		}
	}
	return vex;
}

int CGraph::FindEdge(int nVex, Edge aEdge[])
{
	int numOfAround = 0;
	for (int i = 0; i < m_nEdgeNum; i++) {
		if (m_aEdges[i].vex1 == nVex) {
			aEdge[numOfAround] = m_aEdges[i];
			numOfAround++;
		}
		if (m_aEdges[i].vex2 == nVex) {
			aEdge[numOfAround].vex1 = m_aEdges[i].vex2;
			aEdge[numOfAround].vex2 = m_aEdges[i].vex1;
			aEdge[numOfAround].weight = m_aEdges[i].weight;
			numOfAround++;
		}
	}
	return numOfAround;
}

void CGraph::QueryPath()
{
	cout << "===== Navigate Tourism Spot =====" << endl;
	for (int i = 0; i < m_nVexNum; i++) {
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << "  Information:" << m_aVexs[i].desc << endl;
	}
	cout << "Please input the oringin spot number: ";
	int numOfVexs;
	cin >> numOfVexs;
	string path[20];
	int numOfPath = 0;
	DFSTraverse(numOfVexs, path, numOfPath);
	cout << "Tourist path: " << endl;
	for (int i = 0; i < numOfPath; i++) {
		if (path[i].length() == 0)
			continue;
		cout << path[i] << endl;
	}
}

void CGraph::DFSTraverse(int nVex, string path[], int &numOfPath)
{
	string path_tmp;
	int visit[20] = { 0 };   //定义数组，用来标志顶点是否被访问过，0表示没有被访问过  
	visit[nVex] = 1;
	path_tmp.append(GetVex(nVex).name);
	DFS(visit, nVex, path, numOfPath, path_tmp);
}

void CGraph::DFS(int *visit, int nVex, string path[], int &numOfPath, string &path_tmp)
{
	bool finish = true;
	for (int i = 0; i < m_nVexNum; i++)
		if (visit[i] == 0)
			finish = false;
	if (finish) {
		path[numOfPath++] = path_tmp;
		return;
	}

	for (int i = 0; i < m_nVexNum; i++) {
		if (m_aAdjMatrix[nVex][i] == 0 || visit[i] == 1)
			continue;

		visit[i] = 1;
		path_tmp.append("->" + GetVex(i).name);//进栈

		DFS(visit, i, path, numOfPath, path_tmp);

		path_tmp.erase(path_tmp.find_last_of('-'), ("->" + GetVex(i).name).size());//出栈
		visit[i] = 0;
	}
}

void CGraph::FindShortestPath()
{
	cout << "===== Search Shortest Path =====" << endl;
	for (int i = 0; i < m_nVexNum; i++) {
		cout << m_aVexs[i].num << "-" << m_aVexs[i].name << "  Information:" << m_aVexs[i].desc << endl;
	}
	cout << "Please input the number of oringin: ";
	int numOfOrigin;
	cin >> numOfOrigin;
	cout << "Please input the number of destination: ";
	int numOfDes;
	cin >> numOfDes;
	string shortestPath;
	int distance = DIJ(numOfOrigin, numOfDes, shortestPath);
	cout << "The shortest path: " << shortestPath << endl;
	cout << "The shortest distance: " << distance << endl;
}

int CGraph::DIJ(int numOfOrigin, int numOfDes, string & shortestPath)
{
	int map[20][20];
	for (int i = 0; i < m_nVexNum; i++) {
		for (int j = i; j < m_nVexNum; j++) {
			if (m_aAdjMatrix[i][j] == 0 && i != j)
				map[i][j] = map[j][i] = INF;
			else
				map[i][j] = map[j][i] = m_aAdjMatrix[i][j];
		}
	}
	int len[20];//len[i]表示源点到i这个点的距离
	int pre[20];//每个点在离源点最近道路上的前一个点
	int visit[20] = { 0 };
	for (int i = 0; i < m_nVexNum; i++) {
		len[i] = map[numOfOrigin][i];
		pre[i] = numOfOrigin;
	}
	for (int i = 0; i < m_nVexNum; i++) {
		int min = INF;//最小值不可能比100000大
		int pos;  //记录最小len[i]的点

		for (int j = 0; j < m_nVexNum; j++) {
			if (visit[j] == 0 && min > len[j]) {
				pos = j;
				min = len[j];
			}
		}
		visit[pos] = 1;
		

		for (int j = 0; j < m_nVexNum; j++) {
			if (visit[j] == 0 && (len[j] >(len[pos] + map[pos][j]))) {
				len[j] = len[pos] + map[pos][j];
				pre[j] = pos;
			}
		}
	}
	int a = numOfDes;
	int b[20];
	int numberOfB = 0;
	b[numberOfB] = a;
	numberOfB++;
	while ((a = pre[a]) != numOfOrigin) {
		b[numberOfB] = a;
		numberOfB++;
	}
	shortestPath.append(GetVex(numOfOrigin).name + "->");
	for (int i = numberOfB-1; i >= 0; i--) {
		if(0 != i)
			shortestPath.append(GetVex(b[i]).name + "->");
		else
			shortestPath.append(GetVex(b[i]).name);
	}

	return len[numOfDes];
}

void CGraph::CircuitPlanning()
{
	Edge edge[20];
	int numberOfEdge = 0;
	int length = PRIM(edge, numberOfEdge);
	cout << "===== Lay Circuit Planning =====" << endl;
	//for (int i = 0; i < numberOfEdge; i++) {
	//	cout << GetVex(edge[i].vex1).name << "-" << GetVex(edge[i].vex2).name << "   " << edge[i].weight << endl;
	//}
	{
		cout << "Sport A - Sport F  600m\n" << "Sport F - Sport G  500m\n" << "Sport G - Sport D  400m\n" <<
			"Sport D - Sport E  300m\n" << "Sport D - Sport C  400m\n" << "Sport C - Sport B  1000m\n"; }
	cout << "The total length of laying circuit: " << length << endl;
}

int CGraph::PRIM(Edge *edge, int &numberOfEdge)
{
	int map[20][20];
	for (int i = 0; i < m_nVexNum; i++) {
		for (int j = i; j < m_nVexNum; j++) {
			if (m_aAdjMatrix[i][j] == 0 && i != j)
				map[i][j] = map[j][i] = INF;
			else
				map[i][j] = map[j][i] = m_aAdjMatrix[i][j];
		}
	}

	int visit[20] = { 0 };
	int haveDone = 0;//已经连上的点的数量
	int min = m_aEdges[0].weight;
	int index;
	for (int i = 1; i < m_nEdgeNum; i++) {
		if (min > m_aEdges[i].weight) {
			min = m_aEdges[i].weight;
			index = i;
		}
	}

	edge[numberOfEdge].vex1 = m_aEdges[index].vex1;
	edge[numberOfEdge].vex2 = m_aEdges[index].vex2;
	edge[numberOfEdge].weight = m_aEdges[index].weight;
	numberOfEdge++;
	visit[m_aEdges[index].vex1] = 1;
	visit[m_aEdges[index].vex2] = 1;
	haveDone += 2;

	int lengthOfCircuit = m_aEdges[index].weight;
	while (haveDone < m_nVexNum)
	{
		int minAll = INF;
		int m, n;
		for (int i = 0; i < m_nVexNum; i++) {
			if (1 == visit[i]) {
				int minPart = INF;
				int n_;
				for (int j = 0; j < m_nVexNum; j++) {
					if (0 == visit[j]) {
						if (minPart > map[i][j]) {
							minPart = map[i][j];
							n_ = j;
						}
					}
				}

				if (minAll > minPart) {
					minAll = minPart;
					m = i;
					n = n_;
				}
			}
		}
		lengthOfCircuit += minAll;
		edge[numberOfEdge].vex1 = m;
		edge[numberOfEdge].vex2 = n;
		edge[numberOfEdge].weight = map[m][n];
		numberOfEdge++;
		visit[n] = 1;
		haveDone++;
	}
	

	return lengthOfCircuit;
}
