#pragma once
//链表节点
struct NodeL
{
	int value;
	NodeL* next;
	NodeL(int value_ = 0, NodeL* next_ = nullptr):value(value_),next(next_) {}
};


//二叉树节点
struct NodeT
{
	int value;
	NodeT* left;
	NodeT* right;
	//NodeT(int value_ = 0，NodeT*);
};
