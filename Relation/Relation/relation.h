#pragma once
#include<iostream>
using namespace std;

class Relation
{
protected:
	int dimension;
	int *Matrix;
public:
	Relation(int d = 1);											//����һ��ά��Ϊd���粻ָ����Ĭ��Ϊd=1���Ŀչ�ϵ
	Relation(int d, const int *M);									//�ɹ�ϵ�����ά����һ����ϵ�����ֵ�����鹹���ϵ
	Relation(const string filename);								//���ļ��ж���һ����ϵ�ľ���
	Relation(const Relation &r);									//�������캯��
	Relation &operator =(const Relation &r);						//��ֵ���������
	~Relation();													//��������
																	
	int GetDimension() const;										//���ع�ϵ�����ά��
	int GetatPosition(int row, int column) const;					//�õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
	int operator() (int row, int column) const;						//����ʹ��R(i,j)���õ���ϵ����ĵ�row�е�column�е�ֵ��
																	//���Խ���򷵻�-1
	bool GetMatrix(int *result) const;								//�õ���ϵ�����ֵ
																	
	void Output() const;											//����Ļ��ʾ�ù�ϵ�Ĺ�ϵ����
	bool OutputtoFile(const char *filename) const;					//������ļ�
																	
	bool IsReflexive() const;										//�жϸù�ϵ������
	bool IsIrreflexive() const;										//�жϸù�ϵ������
	bool IsSymmetric() const;										//�жϸù�ϵ������
	bool IsAsymmetric() const;										//�жϸù�ϵ������
	bool IsAntisymmetric() const;									//�жϸù�ϵ������
	bool IsTransitive() const;										//�жϸù�ϵ������
																	
	Relation ReflexiveClosure() const;								//�����Է��հ��Ĺ�ϵ����
	Relation SymmetricClosure() const;								//���ضԳƱհ��Ĺ�ϵ����
	Relation AntisymmetricClosure() const;						    //���ط��ԳƱհ��Ĺ�ϵ����
	Relation TransitiveClosure() const;								//���ش��ݱհ��Ĺ�ϵ����
	Relation EquiClosure() const;                                   //���صȼ۱հ��Ĺ�ϵ����
	Relation PartialClosure() const;                                //����ƫ��հ��Ĺ�ϵ����
	Relation Hasse() const;											//����Hasse�Ĺ�ϵ����
	Relation TopologicalSort() const;
																	
	bool IsEquivalence() const;										//�жϸù�ϵ�Ƿ���һ���ȼ۹�ϵ
																
	bool EquiClasses(int *result) const;							//result��һ����СΪdimension�����飬�����ǰ��ϵ
																	
};
