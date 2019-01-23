#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "relation.h"
using namespace std;

void test(string fileName)
{
	Relation r(fileName);
	cout << "ԭ����Ϊ��" << endl;
	r.Output();
	cout << "�ԳƱհ�Ϊ��" << endl;
	r.SymmetricClosure().Output();
	cout << "���ԳƱհ�Ϊ��" << endl;
	r.AntisymmetricClosure().Output();
	cout << "���ݱհ�Ϊ��" << endl;
	r.TransitiveClosure().Output();
	cout << "�ȼ۱հ�Ϊ��" << endl;
	r.EquiClosure().Output();
	cout << "ƫ��հ�Ϊ��" << endl;
	r.PartialClosure().Output();
	cout << "HasseΪ��" << endl;
	r.PartialClosure().Hasse().Output();
	cout << "TopologicalSortΪ��" << endl;
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
		cout << "��ѡ�������ţ�";
		cin >> choice;
		system("cls");
		cout << "��ѡ��Ĳ����ǣ�" << choice << endl;
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


