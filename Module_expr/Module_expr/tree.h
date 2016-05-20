#include "include_All.h"
#include "symbol.h"

#ifndef TREE_HEADER
#define TREE_HEADER

typedef struct _Tree * Ptree;
typedef struct _Tree tree;
struct _Tree
{
	int op;// operator in this node	操作符包含了类型转换等待
	int _type; // the type in this node 类型是父节点看向子节点的类型
	Ptree _left;
	Ptree _right;
	union
	{
		Psymbol _Psym;	//对于一个ID需要一个索引
		int _value;		//其它类型直接记录类型
	}_u;
};


#endif
