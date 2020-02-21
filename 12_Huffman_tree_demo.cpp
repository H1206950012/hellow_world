// 12_Huffman_tree_demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<malloc.h>

#define MaxSize 1000
#define MinData -1000 

int A[] = { 13,1,45,7,20,4,19,13,40,33,38 };//预先定义好一组权值
int A_length = 11;//定义其长度

typedef struct HeapStruct *MinHeap;
typedef struct TreeNode *HuffmanTree;
struct HeapStruct//存放huffman树的堆
{
	HuffmanTree *data;//存值的数组
	int size;//堆的当前大小
	int capability;//最大容量
};
struct TreeNode//Huffman树
{
	int weight;//权值
	HuffmanTree left;//左子树
	HuffmanTree right;//右子树
};
using namespace std;

MinHeap create();//初始化堆
HuffmanTree Create();//初始化Huffman树
void sort(MinHeap H, int i);//调整最小堆
void adjust(MinHeap H);//调整最小堆
void BuildMinHeap(MinHeap H);//建堆
HuffmanTree Delete(MinHeap H);//删除最小堆元素
void Insert(MinHeap H, HuffmanTree Huff);//插入最小堆元素
void PreOrderTraversal(HuffmanTree Huff);//先序遍历
HuffmanTree Huffman(MinHeap H);//哈夫曼树的构建

//初始化堆
MinHeap create()
{
	MinHeap H;
	HuffmanTree Huff;
	H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->data = (HuffmanTree*)malloc(sizeof(struct TreeNode)*(MaxSize + 1));
	H->capability = MaxSize;
	H->size = 0;
	//给堆置哨兵
	Huff = Create();
	Huff->weight = MinData;
	H->data[0] = Huff;
	return H;
}

//初始化哈夫曼树
HuffmanTree Create()
{
	HuffmanTree Huff;
	Huff = (HuffmanTree)malloc(sizeof(struct TreeNode));
	Huff->weight = 0;
	Huff->left = NULL;
	Huff->right = NULL;
	return Huff;
}

//调整最小堆(实际上是最小堆的一个删除操作)
void sort(MinHeap H, int i)
{
	int parent,child;
	int tmp = H->data[i]->weight;//取出当前根节点的值
	for (parent = i; parent * 2 <= H->size; parent = child)
	{
		child = 2 * parent;
		if ((child != H->size) && (H->data[child]->weight > H->data[child + 1]->weight))
			child++;
		if (H->data[child]->weight >= tmp)
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent]->weight = tmp;
}

//调整最小堆
void adjust(MinHeap H)
{
	for (int i = H->size / 2; i > 0; i--)
		sort(H, i);
}

//建堆(实际上这里是读入A[i]的过程)
void BuildMinHeap(MinHeap H)
{
	HuffmanTree Huff;
	for (int i = 0; i < A_length; i++)
	{
		Huff = Create();
		Huff->weight = A[i];
		H->data[++H->size] = Huff;
	}
	adjust(H);
}

//删除最小堆元素
HuffmanTree Delete(MinHeap H)
{
	int parent, child;
	HuffmanTree T = H->data[1];//取出根节点的哈夫曼树
	HuffmanTree tmp = H->data[H->size--];//取出最后一个节点的信息
	for (parent = 1; parent * 2 <= H->size; parent = child)
	{
		child = parent * 2;
		if ((child != H->size) && (H->data[child]->weight > H->data[child + 1]->weight))
			child++;
		if (H->data[child]->weight >= tmp->weight)
			break;
		else
			H->data[parent]= H->data[child];
	}
	H->data[parent] = tmp;
	return T;
}

//插入最小堆元素
void Insert(MinHeap H, HuffmanTree Huff)
{
	int weight = Huff->weight;
	int i = ++H->size;
	for (; H->data[i / 2]->weight > weight; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = Huff;
}

//遍历
void PreOrderTraversal(HuffmanTree Huff)
{
	if (Huff)
	{
		cout << Huff->weight << ' ';
		PreOrderTraversal(Huff->left);
		PreOrderTraversal(Huff->right);
	}
}

//哈夫曼树的构建
HuffmanTree Huffman(MinHeap H)
{
	HuffmanTree T;
	BuildMinHeap(H);//建堆
	int times = H->size;
	//作times-1次的合并
	for (int i = 1; i < times; i++)
	{
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		T->left = Delete(H);// 从堆中删除一个结点，作为新 T 的左子结点 
		T->right = Delete(H);// 从堆中删除一个结点，作为新 T 的右子结点
		T->weight = T->left->weight + T->right->weight;// 重新计算权值
		Insert(H, T);//把T在加进堆里
	}
	T = Delete(H);
	return T;
}

int main()
{
	MinHeap H;
	HuffmanTree Huff;
	H = create();
	Huff = Huffman(H);
	PreOrderTraversal(Huff);
    return 0;
}

