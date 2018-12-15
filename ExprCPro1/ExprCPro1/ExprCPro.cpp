#include"Expr.h"
#include<iostream>

using namespace std;

/************************************
【Function name】 main
【Function function】 Program master function, the entrance of the application
【Function parameter】 void
【Return value】 int: Description of the exit status of the program
************************************/

int main()
{
	//Output interface
	cout << "**********表达式求值**********" << endl;
	cout << "==============================" << endl;
	cout << "## 1 支持四则运算符 + - * / ##" << endl;
	cout << "## 2 支持括号()             ##" << endl;
	cout << "## 3 支持浮点数             ##" << endl;
	cout << "## 请输入表达式，按回车结束 ##" << endl;
	cout << "==============================" << endl;
	char exit = 'y';
	while (exit == 'y')
	{
		//Input expression
		char expr[256] = { 0 };
		cout << "表达式：";
		cin >> expr;
		//Output results
		if (determine(expr))
			cout << "结  果：" << parse(expr) << endl;
		else
			cout << "表达式有误！" << endl;

		cout << "是否继续？（y:继续，n:退出）" << endl;
		cin >> exit;
	}
	

	system("pause");
	return 0;
}

