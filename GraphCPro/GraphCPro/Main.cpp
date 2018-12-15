#include "Graph.h"
using namespace std;

void test() {
	CGraph minPath = CGraph();
	minPath.CreateGraph();
	bool finish = true;
	while (finish)
	{
		cout << "1. Display the graph" << endl;
		cout << "2. Query sport information" << endl;
		cout << "3. Navigate tourism spot" << endl;
		cout << "4. Search shortest path" << endl;
		cout << "5. Lay circuit planning" << endl;
		cout << "6. Exit" << endl;
		cout << "Please choose:";
		int chiose;
		cin >> chiose;
		switch (chiose)
		{
			case 1:minPath.DisplayGraph(); break;
			case 2:minPath.QuerySpot(); break;
			case 3:minPath.QueryPath(); break;
			case 4:minPath.FindShortestPath(); break;
			case 5:minPath.CircuitPlanning(); break;
			case 6:finish = false; break;
			default:
				break;
		}

		getchar();
		getchar();
		system("cls");
	}
}

int main() {
	test();

	system("pause");
	return 0;
}