#include "stdio.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "relation.h"
using namespace std;


bool Relation::IsReflexive() const
{
	//ToDo：判断该关系的性质
	for (int i = 0; i < dimension; i++)
		if (0 == Matrix[i*dimension + i])
			return false;
	return true;
}

bool Relation::IsIrreflexive() const
{
	//ToDo：判断该关系的性质
	for (int i = 0; i < dimension; i++)
		if (1 == Matrix[i*dimension + i])
			return false;
	return true;
}

bool Relation::IsSymmetric() const
{
	//ToDo：判断该关系的性质
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] != Matrix[column*dimension + row])
				return false;
	return true;
}

bool Relation::IsAsymmetric() const
{
	//ToDo：判断该关系的性质
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] == Matrix[column*dimension + row] == 1)
				return false;
	return true;
}

bool Relation::IsAntisymmetric() const
{
	//ToDo：判断该关系的性质
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (Matrix[row*dimension + column] == Matrix[column*dimension + row] == 1 && !(column == row))
				return false;
	return true;
}

bool Relation::IsTransitive() const
{
	//ToDo：判断该关系的性质
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
	//ToDo：判断该关系是否是一个等价关系
	if (IsReflexive() && IsSymmetric() && IsTransitive())
		return true;
	return false;
}

Relation Relation::ReflexiveClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: 修改*m，得到自反闭包的关系矩阵，由之构造对象r并返回
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
	ToDo: 修改*m，得到对称闭包的关系矩阵，由之构造对象r并返回
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
	ToDo: 修改*m，得到反对称闭包的关系矩阵，由之构造对象r并返回
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
	ToDo: 修改*m，得到传递闭包的关系矩阵，由之构造对象r并返回
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
	ToDo: 修改*m，得到自反闭包的关系矩阵
	*/
	for (int i = 0; i < dimension; i++)
		m[i*dimension + i] = 1;

	/*
	ToDo: 修改*m，得到对称闭包的关系矩阵
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] != m[column*dimension + row])
				m[row*dimension + column] = m[column*dimension + row] = 1;

	/*
	ToDo: 修改*m，得到传递闭包的关系矩阵
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
	ToDo: 修改*m，得到自反闭包的关系矩阵
	*/
	for (int i = 0; i < dimension; i++)
		m[i*dimension + i] = 1;

	/*
	ToDo: 修改*m，得到反对称闭包的关系矩阵
	*/
	int row, column;
	for (row = 0; row < dimension; row++)
		for (column = row; column < dimension; column++)
			if (m[row*dimension + column] == m[column*dimension + row] == 1 && row != column)
				m[row*dimension + column] = 0;

	/*
	ToDo: 修改*m，得到传递闭包的关系矩阵
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
	cout << "拓扑排序为：";
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
	ToDo: result是一个大小为dimension的数组，如果当前关系是等价关系，则result中存放的是当前关系的各个元素
	所在等价类的编号（编号从0开始），返回true；否则result数组中任一项的值都是-1，并返回false。
	示例见函数声明处注释。
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
