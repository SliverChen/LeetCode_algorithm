/*
Author: SLiverChen
Date: 2021/3/21
Title:反转链表

Request:

the array is a linkedlist

In: [1,2,3,4,5] left:2 right: 4    1->2->3->4->5
Out:[1,4,3,2,5]                    1->4->3->2->5

In: [1] left:1 right:1
Out:[1]


解法1：时间复杂度O(n^2)
从left位置i开始，将第i个节点的值与第i+1个节点的值对换，直到i==right为止
随后将第i+1个节点的值与第i+2个节点的值对换，直到i+1==right-1为止
按照上面的遍历依次进行直到将第right-1个节点的值与第right个节点的值对换后，循环结束 

解法2：时间复杂度O(n)
设置三个临时指针 pre cur temp
首先将pre指向null，cur指向head(头指针)  temp指向cur.next
将cur.next = pre 即完成反转操作
之后pre = cur  cur = temp 再重复上面的两个操作 
*/

#include <iostream>
#include <list>
using namespace std;

//链表的节点结构
template <class T>
struct LinkNode
{
	T val;
	LinkNode *next;
	LinkNode(T va)
	{
		val = va;
		next = NULL;
	}
	LinkNode()
	{
		val = T();
		next = NULL;
	}
};

//获取数组长度
template<class T>
int getLen(const T *array)
{
	return sizeof(array) / sizeof(array[0]);
}

template <class T>
class myList
{
public:
	//构造函数(无参)
	myList()
	{
		head->next = NULL;
		size = 0;
	}
	
	myList<T>& operator=(const myList<T> &list2)
	{
		LinkNode<T> *CopyNode = list2.getHead()->next;
		LinkNode<T> *curNode = this->head;
		while(CopyNode)
		{
			LinkNode<T> *NewNode = new LinkNode<T>(CopyNode->val);
			curNode->next = NewNode;
			CopyNode = CopyNode->next;
			curNode = curNode->next;
			this->size++;
		}
		return *this;
	}
	

	myList<T>& operator=(const T array)
	{
		int arrLen = getLen(array);
		printf("array len is %d\n",arrLen);
		if(arrLen == 0) return *this;
		LinkNode<T> *curNode = this->head;
		for(int i=0;i<arrLen;i++)
		{
			LinkNode<T> *NewNode = new LinkNode<T>(array[i]);
			curNode->next = NewNode;
			curNode = curNode->next;
			this->size++;
		}
		return *this;
	}

	//获取链表头节点
	LinkNode<T> *getHead()
	{
		return head;
	}

	//将元素插入到链表的最后的位置
	void push_back(T element)
	{
		LinkNode<T> *temp = head;
		LinkNode<T> *next = new LinkNode<T>(element);
		for (int i = 0; i < size; i++)
		{
			temp = temp->next;
		}
		temp->next = next;
		size++;
	}

	//删除链表的最后一个节点
	void pop_back()
	{
		LinkNode<T> *temp = head;
		for (int i = 0; i < size; i++)
		{
			temp = temp->next;
		}
		temp = NULL;
		size--;
	}

	//打印链表
	void printList()
	{
		LinkNode<T> *temp = head;
		for (int i = 0; i < size; i++)
		{
			temp = temp->next;
			cout << temp->val << " -> ";
		}
		cout << endl;
	}

	//在对应索引之前插入节点
	bool Insert(T element, int index)
	{
		LinkNode<T> *preNode = head;
		if (index <= 0 || index > size)
		{
			printf("index out of range,which index is %d, size is %d \n", index, size);
			return false;
		}
		for (int i = 0; i < index - 1; i++)
		{
			preNode = preNode->next;
		}
		LinkNode<T> *newNode = new LinkNode<T>(element);
		newNode->next = preNode->next;
		preNode->next = newNode;
		size++;
		return true;
	}

	//删除索引对应的节点
	bool Remove(int index)
	{
		LinkNode<T> *preNode = head;
		if (index <= 0 || index > size)
		{
			printf("index out of range, which index is %d, size is %d \n", index, size);
			return false;
		}
		for (int i = 0; i < index - 1; i++)
		{
			preNode = preNode->next;
		}
		LinkNode<T> *RemoveNode = preNode->next;
		preNode->next = RemoveNode->next;
		delete RemoveNode;
		size--;
		return true;
	}

	//清空链表操作
	bool Clear()
	{
		delete head->next;
		head->next = new LinkNode<T>();
		size = 0;
		return true;
	}

	//获取链表大小
	int GetListSize()
	{
		return size;
	}

	//反转整个链表的节点  例：1->2->3   ----->     3->2->1
	void ReverseWholeList()
	{
		LinkNode<T> *curNode = head->next;
		LinkNode<T> *tempNode;
		LinkNode<T> *preNode = NULL;
		while (curNode)
		{
			tempNode = curNode->next;
			printf("make value %d reverse\n", curNode->val);
			curNode->next = preNode;
			preNode = curNode;
			curNode = tempNode;
		}
		curNode = head;
		curNode->next = preNode;
	}
	//反转链表的部分节点  例：1->2->3->4  left:2  right:3    ----->  1->3->2->4
	void ReversePartOfList(int leftIndex, int rightIndex)
	{
		if (leftIndex <= 0 || leftIndex > size || rightIndex <= leftIndex || rightIndex > size)
		{
			printf("Index out of range or invalid which Index limits in (0,%d]",size);
			printf(", but now is [%d,%d]\n", leftIndex, rightIndex);
			return;
		}
		//首先获取左索引的前节点，右索引的后节点
		LinkNode<T> *leftNode, *rightNode, *curNode, *preNode, *tempNode, *headNode;
		curNode = head;
		preNode = NULL;
		for (int i = 0; i <= rightIndex; i++)
		{
			printf("curNode equals %d \n",i);
			if (i == leftIndex - 1)
			{
				printf("make index %d equals leftNode",i);
				printf(", make index %d equals headNode\n",i + 1);
				leftNode = curNode;
				headNode = leftNode->next;
				curNode = curNode->next;
				continue;
			}
			else if (i >= leftIndex)
			{
				printf("make %d linked to %d\n",i,i-1);
				tempNode = curNode->next;
				curNode->next = preNode;
				preNode = curNode;
				curNode = tempNode;
				if (i == rightIndex)
				{
					printf("make index %d equals rightNode\n", i + 2);
					rightNode = curNode->next;
				}
			}
			else
			{
				curNode = curNode->next;
				continue;
			}
		}
		leftNode->next = preNode;
		headNode->next = tempNode;
	}

private:
	LinkNode<T> *head;
	int size;
};


int main()
{

	myList<int> mylist;
	int array[4] = {1, 2, 3, 4};
	mylist.printList();
	system("pause");
	return 0;
}