#include "include_All.h"

#ifndef symbol_HEADER
#define symbol_HEADER

//对于每一个源文件，都有单独的全局符号表，extern符号表，局部函数符号表
//实现方式是一个表

struct _type
{
	int size;
	int type;
	int pointer;
};
typedef struct _type type;
typedef struct _type* Ptype;

struct _symbol
{
	std::string name;	//名字
	int hash;			//哈希用于比较
	int scope;			//作用域，很重要
	int line, letral;	//源码中的位置
	type type;
};
typedef struct _symbol symbol;
typedef struct _symbol* Psymbol;


#endif