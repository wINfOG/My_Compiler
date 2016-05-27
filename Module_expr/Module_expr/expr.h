#include "include_All.h"
#include "tree.h"
#include "lex.h"
#include "token.h"
using namespace TOKEN_TO_NUM;
#ifndef EXPR_HEADER

#define EXPR_HEADER
class _expr_table
{
public:
	_expr_table();
	inline int operator[] (int xx){ return _this_table[xx]; };
private:
	std::map<int, int> _this_table;
};

class expr
{
public:
	Ptree expression();
private:
	Ptree _Expr(int);
	Ptree _Euqals();
	Ptree _binary(int);
	Ptree _unit();
	Ptree _unary();
	Ptree _postfix(Ptree);

	
	Ptree _CreateNode(int op,int type, Ptree left, Ptree right);
	int _DeleteNode(Ptree xx);
	int _DeleteTree(Ptree xx);

	_expr_table _tb;

	std::vector<Ptree> _Bin_stack;
protected:

};


#ifdef _DEBUG
void _DEBUG_PRINT_TREE(Ptree xx);
#endif

#endif
//CreateNode 需要被改写成创建常量node 与变量node