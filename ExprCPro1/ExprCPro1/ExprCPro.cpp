#include"Expr.h"
#include<iostream>

using namespace std;

/************************************
��Function name�� main
��Function function�� Program master function, the entrance of the application
��Function parameter�� void
��Return value�� int: Description of the exit status of the program
************************************/

int main()
{
	//Output interface
	cout << "**********���ʽ��ֵ**********" << endl;
	cout << "==============================" << endl;
	cout << "## 1 ֧����������� + - * / ##" << endl;
	cout << "## 2 ֧������()             ##" << endl;
	cout << "## 3 ֧�ָ�����             ##" << endl;
	cout << "## ��������ʽ�����س����� ##" << endl;
	cout << "==============================" << endl;
	char exit = 'y';
	while (exit == 'y')
	{
		//Input expression
		char expr[256] = { 0 };
		cout << "���ʽ��";
		cin >> expr;
		//Output results
		if (determine(expr))
			cout << "��  ����" << parse(expr) << endl;
		else
			cout << "���ʽ����" << endl;

		cout << "�Ƿ��������y:������n:�˳���" << endl;
		cin >> exit;
	}
	

	system("pause");
	return 0;
}

