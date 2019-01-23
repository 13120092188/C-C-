#include "RiverToVillage.h"
using namespace std;
void test()
{
	ifstream file("data.txt");
	RiverToVillage minPath = RiverToVillage(&file);
	file.close();
	minPath.Part1B();

	minPath.Part1C();

	minPath.Part1D(10, 11);

	minPath.Part2B();

	int villages[] = { 1,2,3,4,5,6};
	minPath.Part2D(villages, 6);

	minPath.Part2E();

	int villages1[] = { 13,14,15 };
	Edge edges[] = { {12,14},{12,15} };
	minPath.Part2F(villages1, 3, edges, 2);
}


int main()
{
	test();

	system("pause");
	return 0;
}