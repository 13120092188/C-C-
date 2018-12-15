#pragma once
typedef int DataType;

struct LinkNode      //节点类
{
	LinkNode(const DataType x);
	DataType _data;    //节点的数据
	LinkNode* _next;    //后继指针
	LinkNode* _prev;      //前驱指针
};

class List    //链表类
{
public:
	List();         //构造函数
	List(const List& s);        //拷贝构造
	List &operator=(List& s);    //赋值运算符的重载
	~List();

	void PrintSList();   //打印链表
	void PushBack(const DataType& x);    //在尾部插入一个节点
	void Clear();         //链表置空
	void PopBack();
	void PushFront(DataType x);  //头插
	void PopFront();    //删除首节点
	void Insert(LinkNode* pos, DataType x);//固定位置插入一个节点
	void Erase(LinkNode* pos);        //删除某一节点
	LinkNode* Find(DataType x);       //查找节点并返回这个节点的地址
	void Remove(DataType x);     //查找某节点并删除

private:
	LinkNode* _head;    //指向头结点
	LinkNode* _tail;    //指向尾节点
};
