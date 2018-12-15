#pragma once

#define ERROR       -1         //Operation abnormality
#define OK           0         //Normal operation

//Operand stack
typedef struct StackNodeOPND
{
	double value;
	StackNodeOPND *next;
} *OPND;

//Initialization stack
int init(OPND &opnd);
//Operand entry stack
int push(OPND &opnd, const double value);
//Operand exit stack
int pop(OPND &opnd, double &value);
//Get the top operating number of the stack
int getTop(OPND &opnd, double &value);
//Get the number of stack elements
int getLength(OPND &opnd);
//Determine whether the stack is empty
int isEmpty(OPND *opnd);


//Operator stack
typedef struct StackNodeOPTR
{
	char op;
	StackNodeOPTR *next;
} *OPTR;

//Initialization stack
int init(OPTR &optr);
//Operand entry stack
int push(OPTR &optr, const char op);
//Operand exit stack
int pop(OPTR &optr, char &op);
//Get the top operating number of the stack
int getTop(OPTR &optr, char &op);
//Get the number of stack elements
int getLength(OPTR &optr);
//Determine whether the stack is empty
int isEmpty(OPTR &optr);

//Determine whether the expression is correct
bool determine(char expr[]);
//Analytic expression
double parse(char expr[]);
//Judge the priority of the operator
char precede(char a, char b);
//Calculating the value of an expression
double calc(double a, char theta, double b);
