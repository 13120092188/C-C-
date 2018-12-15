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
	//删尾节点
	list1.PopBack();
	list1.PrintSList();
	//删头结点
	list1.PopFront();
	list1.PrintSList();
	//添加到头结点
	list1.PushFront(1);
	list1.PrintSList();
	//添加到尾节点
	list1.PushBack(6);
	list1.PrintSList();
	//删除特定结点
	list1.Erase(list1.Find(3));
	list1.PrintSList();
	//添加特定结点
	list1.Insert(list1.Find(2), 3);
	list1.PrintSList();
	//删除特定数据结点
	list1.Remove(5);
	list1.PrintSList();

}

int main()
{
	Test1();
	system("pause");
}
