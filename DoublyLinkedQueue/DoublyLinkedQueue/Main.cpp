#include "DoublyLinkedQueue.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

void Test1()
{
	List list1;
	list1.PushBack(1);
	list1.PushBack(2);
	list1.PushBack(3);
	list1.PushBack(4);
	list1.PushBack(5);
	list1.PushBack(6);
	list1.PrintSList();
	//ɾβ�ڵ�
	list1.PopBack();
	list1.PrintSList();
	//ɾͷ���
	list1.PopFront();
	list1.PrintSList();
	//��ӵ�ͷ���
	list1.PushFront(1);
	list1.PrintSList();
	//��ӵ�β�ڵ�
	list1.PushBack(6);
	list1.PrintSList();
	//ɾ���ض����
	list1.Erase(list1.Find(3));
	list1.PrintSList();
	//����ض����
	list1.Insert(list1.Find(2), 3);
	list1.PrintSList();
	//ɾ���ض����ݽ��
	list1.Remove(5);
	list1.PrintSList();

}

int main()
{
	Test1();
	system("pause");
}
