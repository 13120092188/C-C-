#pragma once
typedef int DataType;

struct LinkNode      //�ڵ���
{
	LinkNode(const DataType x);
	DataType _data;    //�ڵ������
	LinkNode* _next;    //���ָ��
	LinkNode* _prev;      //ǰ��ָ��
};

class List    //������
{
public:
	List();         //���캯��
	List(const List& s);        //��������
	List &operator=(List& s);    //��ֵ�����������
	~List();

	void PrintSList();   //��ӡ����
	void PushBack(const DataType& x);    //��β������һ���ڵ�
	void Clear();         //�����ÿ�
	void PopBack();
	void PushFront(DataType x);  //ͷ��
	void PopFront();    //ɾ���׽ڵ�
	void Insert(LinkNode* pos, DataType x);//�̶�λ�ò���һ���ڵ�
	void Erase(LinkNode* pos);        //ɾ��ĳһ�ڵ�
	LinkNode* Find(DataType x);       //���ҽڵ㲢��������ڵ�ĵ�ַ
	void Remove(DataType x);     //����ĳ�ڵ㲢ɾ��

private:
	LinkNode* _head;    //ָ��ͷ���
	LinkNode* _tail;    //ָ��β�ڵ�
};
