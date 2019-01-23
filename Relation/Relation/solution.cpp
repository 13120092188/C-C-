#include "stdio.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "relation.h"
using namespace std;


bool Relation::IsReflexive() const
{
	//ToDo���жϸù�ϵ������
	for (int i = 0; i < dimension; i++)
		if (0 == Matrix[i*dimension + i])
			return false;
	return true;
}

bool Relation::IsIrreflexive() const
{
	//ToDo���жϸù�ϵ������
	for (int i = 0; i < dimension; i++)
		if (1 == Matrix[i*dimension + i])
			return false;
	return true;
}

bool Relation::IsSymmetric() const
{
	//ToDo���жϸù�ϵ������
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] != Matrix[column*dimension + row])
				return false;
	return true;
}

bool Relation::IsAsymmetric() const
{
	//ToDo���жϸù�ϵ������
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] == Matrix[column*dimension + row] == 1)
				return false;
	return true;
}

bool Relation::IsAntisymmetric() const
{
	//ToDo���жϸù�ϵ������
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] == Matrix[column*dimension + row] == 1 && !(column == row))
				return false;
	return true;
}

bool Relation::IsTransitive() const
{
	//ToDo���жϸù�ϵ������
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = 0; column < dimension; column++) {
			if (1 == Matrix[row*dimension + column]) {
				int row1 = column, column1;
				for (column1 = 0; column1 < dimension; column1++) {
					if (column1 == row) {
						if ((0 == Matrix[row*dimension + column1]) && (0 == Matrix[row1*dimension + column]))
							return false;
					}
					else if (1 == Matrix[row1*dimension + column1])
						if (0 == Matrix[row*dimension + column1])
							return false;
				}
			}
		}
	return true;
}

bool Relation::IsEquivalence() const
{
	//ToDo���жϸù�ϵ�Ƿ���һ���ȼ۹�ϵ
	if (IsReflexive() && IsSymmetric() && IsTransitive())
		return true;
	return false;
}

Relation Relation::ReflexiveClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ��Է��հ��Ĺ�ϵ������֮�������r������
	*/
	for (int i = 0; i < dimension; i++)
		m[i*dimension + i] = 1;


	Relation r(dimension, m);
	return r;
}

Relation Relation::SymmetricClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ��ԳƱհ��Ĺ�ϵ������֮�������r������
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] != m[column*dimension + row])
				m[row*dimension + column] = m[column*dimension + row] = 1;

	Relation r(dimension, m);
	return r;
}

Relation Relation::AntisymmetricClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ����ԳƱհ��Ĺ�ϵ������֮�������r������
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] == m[column*dimension + row] == 1 && row != column)
				m[row*dimension + column] = 0;

	Relation r(dimension, m);
	return r;
}

Relation Relation::TransitiveClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ����ݱհ��Ĺ�ϵ������֮�������r������
	*/
	int i, column, row;
	for (i = 0; i < dimension; i++)
		for (column = 0; column < dimension; column++)
			if (1 == m[i*dimension + column])
				for (row = 0; row < dimension; row++)
					if (1 == m[row*dimension + i])
						m[row*dimension + column] = 1;

	Relation r(dimension, m);
	return r;
}

Relation Relation::EquiClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ��Է��հ��Ĺ�ϵ����
	*/
	for (int i = 0; i < dimension; i++)
		m[i*dimension + i] = 1;

	/*
	ToDo: �޸�*m���õ��ԳƱհ��Ĺ�ϵ����
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] != m[column*dimension + row])
				m[row*dimension + column] = m[column*dimension + row] = 1;

	/*
	ToDo: �޸�*m���õ����ݱհ��Ĺ�ϵ����
	*/
	int i, column1, row1;
	for (i = 0; i < dimension; i++)
		for (column = 0; column < dimension; column++)
			if (1 == m[i*dimension + column])
				for (row = 0; row < dimension; row++)
					if (1 == m[row*dimension + i])
						m[row*dimension + column] = 1;

	Relation r(dimension, m);
	return r;
}

Relation Relation::PartialClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: �޸�*m���õ��Է��հ��Ĺ�ϵ����
	*/
	for (int i = 0; i < dimension; i++)
		m[i*dimension + i] = 1;

	/*
	ToDo: �޸�*m���õ����ԳƱհ��Ĺ�ϵ����
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] == m[column*dimension + row] == 1 && row != column)
				m[row*dimension + column] = 0;

	/*
	ToDo: �޸�*m���õ����ݱհ��Ĺ�ϵ����
	*/
	int i, column1, row1;
	for (i = 0; i < dimension; i++)
		for (column = 0; column < dimension; column++)
			if (1 == m[i*dimension + column])
				for (row = 0; row < dimension; row++)
					if (1 == m[row*dimension + i])
						m[row*dimension + column] = 1;

	Relation r(dimension, m);
	return r;
}

Relation Relation::Hasse() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	int i, column, row;

	for (row = 0; row < dimension; row++) {
		m[row*dimension + row] = 0;
	}
	for (i = 0; i < dimension; i++) {
		for (row = 0; row < dimension; row++) {
			for (column = 0; column < dimension; column++) {
				if (m[row*dimension + i] == 1 && m[i*dimension + column] == 1 && m[row*dimension + column] == 1) {
					m[row*dimension + column] = 0;
				}
			}
		}
	}

	Relation r(dimension, m);
	return r;
}

Relation Relation::TopologicalSort() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	int i, column, row;

	for (row = 0; row < dimension; row++) {
		m[row*dimension + row] = 0;
	}
	for (i = 0; i < dimension; i++) {
		for (row = 0; row < dimension; row++) {
			for (column = 0; column < dimension; column++) {
				if (m[row*dimension + i] == 1 && m[i*dimension + column] == 1 && m[row*dimension + column] == 1) {
					m[row*dimension + column] = 0;
				}
			}
		}
	}
	cout << "��������Ϊ��";
	for (column = 0; column < dimension; column++) {
		if (m[0 * dimension + column] == 0 && m[1 * dimension + column] == 0 && m[2 * dimension + column] == 0 && m[3 * dimension + column] == 0) {
			cout << column + 1;
		}
	}

	for (column = 0; column < dimension; column++) {
		for (row = 0; row < dimension; row++) {
			if (m[row*dimension + column] == 1) {
				cout << "->" << column + 1;
				continue;
			}
		}
	}
	cout << endl;

	Relation r(dimension, m);
	return r;
}

bool Relation::EquiClasses(int *result) const
{
	/*
	ToDo: result��һ����СΪdimension�����飬�����ǰ��ϵ�ǵȼ۹�ϵ����result�д�ŵ��ǵ�ǰ��ϵ�ĸ���Ԫ��
	���ڵȼ���ı�ţ���Ŵ�0��ʼ��������true������result��������һ���ֵ����-1��������false��
	ʾ��������������ע�͡�
	*/
	if (IsEquivalence()) {
		int row, column, i = 0;
		for (row = 0; row < dimension; row++) {
			for (column = 0; column < dimension; column++) {
				if (1 == Matrix[row*dimension + column]) {
					result[column] = row;
					i++;
					if (i == dimension)
						break;
				}
			}
			if (i == dimension)
				break;
		}
		return true;
	}
	else
		memset(result, 255, sizeof(int) * dimension);
	return false;
}
