#include "Expr.h"
#include<stdlib.h>
#include<iostream>

using namespace std;

/*****************Operand stack**************/
int init(OPND & opnd)
{
	//Destroy the chain element
	while (opnd != NULL)
	{
		//Delete old nodes
		OPND temp = opnd;
		opnd = temp->next;
		free(temp);
	}
	opnd = NULL;
	return 0;
}

int push(OPND & opnd, const double value)
{
	//Add the new node to the top of the stack
	OPND temp = (OPND)malloc(sizeof(StackNodeOPND));
	if (!temp)
	{
		return -1;
	}
	temp->value = value;
	temp->next = opnd;
	opnd = temp;
	return 0;
}

int pop(OPND & opnd, double & value)
{
	if (opnd == NULL)//Empty stack
		return -1;
	//Pop the operand
	value = opnd->value;

	//Delete the old node
	OPND temp = opnd;
	opnd = temp->next;
	free(temp);

	return 0;
}

int getTop(OPND & opnd, double & value)
{
	if (opnd == NULL)
		return -1;
	value = opnd->value;
	return 0;
}

int getLength(OPND & opnd)
{
	OPND temp = opnd;
	int i = 0;
	for (; temp != NULL; i++)
		temp = temp->next;
	return i;
}

int isEmpty(OPND * opnd)
{
	if (opnd == NULL)
		return -1;
	else
		return 0;
	return 0;
}

/*****************Operator stack**************/
int init(OPTR & optr)
{
	//Destroy the chain element
	while (optr != NULL)
	{
		//Delete old nodes
		OPTR temp = optr;
		optr = temp->next;
		free(temp);
	}
	optr = NULL;
	return 0;
}

int push(OPTR & optr, const char op)
{
	//Add the new node to the top of the stack
	OPTR temp = (OPTR)malloc(sizeof(StackNodeOPTR));
	if (!temp)
	{
		return -1;
	}
	temp->op = op;
	temp->next = optr;
	optr = temp;
	return 0;
}

int pop(OPTR & optr, char & op)
{
	if (optr == NULL)//Empty stack
		return -1;
	//Pop the operand
	op = optr->op;

	//Delete the old node
	OPTR temp = optr;
	optr = temp->next;
	free(temp);

	return 0;
}

int getTop(OPTR & optr, char & op)
{
	if (optr == NULL)
		return -1;
	op = optr->op;
	return 0;
}

int getLength(OPTR & optr)
{
	OPTR temp = optr;
	int i = 0;
	for (; temp != NULL; i++)
		temp = temp->next;
	return i;
}

int isEmpty(OPTR & optr)
{
	if (optr == NULL)
		return -1;
	else
		return 0;
	return 0;
}

bool determine(char expr[])//When the expression is mistaken, return false. Otherwise, return true
{
	for (int i = 0; expr[i] != '\0'; i++)
	{
		if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '(' || expr[i] == '.') &&
			(expr[i + 1] == '+' || expr[i + 1] == '-' || expr[i + 1] == '*' || expr[i + 1] == '/' || expr[i+1] == ')' || expr[i + 1] == '.'))
			return false;
		if (expr[i] == '.') 
		{
			for (int j = i+1; expr[j] != '\0'; j++)
			{
				if (expr[j] == '+' || expr[j] == '-' || expr[j] == '*' || expr[j] == '/' || expr[j] == ')')
					break;
				if (expr[j] == '.' || expr[j] == '(')
					return false;
			}
		}

	}
	return true;
}

double parse(char expr[])
{
	OPND opnd = NULL;//Operand stack
	OPTR optr = NULL;//Operator stack

	//Initialization stack
	init(opnd);
	init(optr);

	for (int i = 0; expr[i] != '\0'; i++)
	{
		//Read a character
		char c = expr[i];
		if (c >= '0' && c <= '9' || c == '.')
		{
			//Processing operands
			char token[20] = { 0 };
			int j = 0;
			while (expr[i + j] >= '0' && expr[i + j] <= '9' || expr[i + j] == '.')
			{
				token[j] = expr[i + j];
				j++;
			}
			token[j] = '\0';
			i = i + j - 1;

			//Convert a into numbers,Add to the operand stack
			double value = atof(token);
			push(opnd, value);
		}
		else
		{
			//Processing operator
			if (isEmpty(optr))
				push(optr, c); 
			else
			{
				//Get the top stack operator and comparison priority
				char op = 0;
				getTop(optr, op);
				switch (precede(op, c))
				{
				case '<'://The top priority of the stack element is low
					push(optr, c);
					break;
				case '='://Pop brackets out
					pop(optr, op);
					break;
				case '>'://Exit stack and add the result of the operation to the stack
					double a = 0;
					double b = 0;
					//Pop two operands and one operator out
					pop(opnd, b);
					pop(opnd, a);
					pop(optr, op);
					//Calculation results and push to the stack
					push(opnd, calc(a, op, b));

					i--;//The key!  Continue to compare the current operator

					break;
				}//end switch
			}
		}
	}
	//Last operation
	while (!isEmpty(optr))
	{
		double a = 0;
		double b = 0;
		char op = 0;
		//Pop the operand and operator out
		pop(opnd, b);
		pop(opnd, a);
		pop(optr, op);
		//Add the calculation results to stack
		push(opnd, calc(a, op, b));
	}
	//Final result
	double value = 0;
	pop(opnd, value);
	return value;
}

char precede(char a, char b)
{
	char aPriorTable[6][6] = {         //Relations between operators
		 //+   -   *   /   (   )
		{ '>','>','<','<','<','>' },// +
		{ '>','>','<','<','<','>' },// -
		{ '>','>','>','>','<','>' },// *
		{ '>','>','>','>','<','>' },// /
		{ '<','<','<','<','<','=' },// (
		{ '>','>','>','>','>','>' } // )
	};

	int x = -1;
	int y = -1;
	char opr[] = "+-*/()";
	for (int i = 0; i < 6; i++)
	{
		if (a == opr[i])x = i;
		if (b == opr[i])y = i;
	}
	return aPriorTable[x][y];
}

double calc(double a, char theta, double b)
{
	//operation
	double value = 0;
	switch (theta)
	{
	case '+': value = a + b; break;
	case '-': value = a - b; break;
	case '*': value = a * b; break;
	case '/': value = a / b; break;
	default:
	{
		cout << "±í´ïÊ±´íÎó¡£" << endl;
		exit(0);
	}
	}
	return value;
}
