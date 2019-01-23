#include "stdio.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "relation.h"
using namespace std;

//---------------------------------------------------------------------------------------------------

Relation::Relation(int d)
{
	//����һ��ά��Ϊd�Ŀչ�ϵ
	dimension = d;
	Matrix = new int[dimension * dimension];
	memset(Matrix, 0, sizeof(int)*dimension * dimension);
}

Relation::Relation(int d, const int *M)
{
	//�ɹ�ϵ�����ά����һ����ϵ�����ֵ�����鹹���ϵ
	dimension = d;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, M, sizeof(int)*dimension * dimension);
}

Relation::Relation(const string filename)
{
	//���ļ��ж���һ����ϵ�ľ���

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
	//��������
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
	//�õ���ϵ�����ά��
	return dimension;
}

int Relation::GetatPosition(int row, int column) const
{
	//�õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
	else
		return -1;
}

int Relation::operator()(int row, int column) const
{
	//����ʹ��R(i,j)���õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
	else
		return -1;
}

bool Relation::GetMatrix(int *result) const
{
	//�õ���ϵ�����ֵ
	if (result != NULL)
	{
		memcpy(result, Matrix, sizeof(int)*dimension * dimension);
		return true;
	}
	return false;
}

void Relation::Output() const
{
	//����Ļ��ʾ�ù�ϵ�Ĺ�ϵ����
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
	//���ù�ϵд���ļ����ļ���ʽ�Ͷ�����ļ���ͬ

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
