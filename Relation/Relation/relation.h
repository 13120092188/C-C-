#pragma once
#include<iostream>
using namespace std;

class Relation
{
protected:
	int dimension;
	int *Matrix;
public:
	Relation(int d = 1);											//构造一个维数为d（如不指定，默认为d=1）的空关系
	Relation(int d, const int *M);									//由关系矩阵的维数和一个关系矩阵的值的数组构造关系
	Relation(const string filename);								//从文件中读入一个关系的矩阵
	Relation(const Relation &r);									//拷贝构造函数
	Relation &operator =(const Relation &r);						//赋值运算符重载
	~Relation();													//析构函数
																	
	int GetDimension() const;										//返回关系矩阵的维数
	int GetatPosition(int row, int column) const;					//得到关系矩阵的第row行第column列的值，如果越界则返回-1
	int operator() (int row, int column) const;						//可以使用R(i,j)来得到关系矩阵的第row行第column列的值，
																	//如果越界则返回-1
	bool GetMatrix(int *result) const;								//得到关系矩阵的值
																	
	void Output() const;											//在屏幕显示该关系的关系矩阵
	bool OutputtoFile(const char *filename) const;					//输出到文件
																	
	bool IsReflexive() const;										//判断该关系的性质
	bool IsIrreflexive() const;										//判断该关系的性质
	bool IsSymmetric() const;										//判断该关系的性质
	bool IsAsymmetric() const;										//判断该关系的性质
	bool IsAntisymmetric() const;									//判断该关系的性质
	bool IsTransitive() const;										//判断该关系的性质
																	
	Relation ReflexiveClosure() const;								//返回自反闭包的关系矩阵
	Relation SymmetricClosure() const;								//返回对称闭包的关系矩阵
	Relation AntisymmetricClosure() const;						    //返回反对称闭包的关系矩阵
	Relation TransitiveClosure() const;								//返回传递闭包的关系矩阵
	Relation EquiClosure() const;                                   //返回等价闭包的关系矩阵
	Relation PartialClosure() const;                                //返回偏序闭包的关系矩阵
	Relation Hasse() const;											//返回Hasse的关系矩阵
	Relation TopologicalSort() const;
																	
	bool IsEquivalence() const;										//判断该关系是否是一个等价关系
																
	bool EquiClasses(int *result) const;							//result是一个大小为dimension的数组，如果当前关系
																	
};
