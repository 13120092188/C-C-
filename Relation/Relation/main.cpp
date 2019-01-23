#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "relation.h"
using namespace std;

void test(string fileName)
{
	Relation r(fileName);
	cout << "原矩阵为：" << endl;
	r.Output();
	cout << "对称闭包为：" << endl;
	r.SymmetricClosure().Output();
	cout << "反对称闭包为：" << endl;
	r.AntisymmetricClosure().Output();
	cout << "传递闭包为：" << endl;
	r.TransitiveClosure().Output();
	cout << "等价闭包为：" << endl;
	r.EquiClosure().Output();
	cout << "偏序闭包为：" << endl;
	r.PartialClosure().Output();
	cout << "Hasse为：" << endl;
	r.PartialClosure().Hasse().Output();
	cout << "TopologicalSort为：" << endl;
	r.PartialClosure().Hasse().TopologicalSort().Output();
}

void main()
{
	bool finish = true;
	while (finish)
	{
		cout << "1.test1" << endl;
		cout << "2.test2" << endl;
		cout << "3.test3" << endl;
		cout << "4.test4" << endl;
		cout << "5.test5" << endl;
		cout << "6.test6" << endl;
		cout << "7.Exit" << endl;
		int choice;
		cout << "请选择测试序号：";
		cin >> choice;
		system("cls");
		cout << "你选择的测试是：" << choice << endl;
		switch (choice)
		{
		case 1:test("test1.txt"); break;
		case 2:test("test2.txt"); break;
		case 3:test("test3.txt"); break;
		case 4:test("test4.txt"); break;
		case 5:test("test5.txt"); break;
		case 6:test("test6.txt"); break;
		case 7:finish = false; break;
		default:
			break;
		}
		getchar();
		getchar();
		system("cls");
	}
	
	system("pause");
}


