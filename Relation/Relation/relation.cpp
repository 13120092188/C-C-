#include "stdio.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "relation.h"
using namespace std;

//---------------------------------------------------------------------------------------------------

Relation::Relation(int d)
{
	//构造一个维数为d的空关系
	dimension = d;
	Matrix = new int[dimension * dimension];
	memset(Matrix, 0, sizeof(int)*dimension * dimension);
}

Relation::Relation(int d, const int *M)
{
	//由关系矩阵的维数和一个关系矩阵的值的数组构造关系
	dimension = d;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, M, sizeof(int)*dimension * dimension);
}

Relation::Relation(const string filename)
{
	//从文件中读入一个关系的矩阵

	ifstream readfile(filename);
	if (!readfile)
	{
		printf("Fail to open.\n");
		exit(1);
	}
	else
	{
		int row, column;
		readfile >> dimension;
		Matrix = new int[dimension * dimension];
		for (row = 0; row < dimension; row++)
			for (column = 0; column < dimension; column++)
				readfile >> Matrix[row * dimension + column];
	}
	readfile.close();
}

Relation::~Relation()
{
	//析构函数
	delete[]Matrix;
}

Relation::Relation(const Relation &r)
{
	dimension = r.dimension;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, r.Matrix, sizeof(int)*dimension * dimension);
}

Relation &Relation::operator =(const Relation &r)
{
	dimension = r.dimension;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, r.Matrix, sizeof(int)*dimension * dimension);
	return *this;
}

//---------------------------------------------------------------------------------------------------

int Relation::GetDimension() const
{
	//得到关系矩阵的维数
	return dimension;
}

int Relation::GetatPosition(int row, int column) const
{
	//得到关系矩阵的第row行第column列的值，如果越界则返回-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
	else
		return -1;
}

int Relation::operator()(int row, int column) const
{
	//可以使用R(i,j)来得到关系矩阵的第row行第column列的值，如果越界则返回-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
	else
		return -1;
}

bool Relation::GetMatrix(int *result) const
{
	//得到关系矩阵的值
	if (result != NULL)
	{
		memcpy(result, Matrix, sizeof(int)*dimension * dimension);
		return true;
	}
	return false;
}

void Relation::Output() const
{
	//在屏幕显示该关系的关系矩阵
	int row, column;
	cout << dimension << endl;
	for (row = 0; row < dimension; row++)
	{
		for (column = 0; column < dimension; column++)
		{
			cout << (*this)(row, column) << " ";
		}
		cout << "\n";
	}
}

bool Relation::OutputtoFile(const char *filename) const
{
	//将该关系写入文件，文件格式和读入的文件相同

	ofstream writefile(filename);
	if (!writefile)
	{
		cout << "Fail to open.\n";
		return false;
	}
	else
	{
		int row, column;
		writefile << dimension << endl;
		for (row = 0; row < dimension; row++)
		{
			for (column = 0; column < dimension; column++)
				writefile << Matrix[row * dimension + column] << ' ';
			writefile << endl;
		}
	}
	writefile.flush();
	writefile.close();
	return true;
}
