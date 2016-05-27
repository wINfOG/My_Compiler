#include "expr.h"

#ifdef _DEBUG
#include "jOrgChart_export.h"
std::vector<std::string> _Debug_ID_Map(128);
jOrgChart_export Jorg;
void _This_PRINT_TREE(Ptree xx, PjNode _This_PjNode)
{
	//printf("Node Level %d Type %d , value %d \n",level,xx->_type,xx->op);
	//++level;
	std::stringstream _for_this;
	_for_this << _Debug_ID_Map[xx->op] << "  \n" << _Debug_ID_Map[xx->_type] << "<br>   \n" << xx->value;
	_This_PjNode->_in = _for_this.str();
	if (xx->_left != nullptr)
	{

		_This_PRINT_TREE(xx->_left, Jorg.jOrgChart_AddChildNode(_This_PjNode));
	}
	if (xx->_right != nullptr)
	{
		_This_PRINT_TREE(xx->_right, Jorg.jOrgChart_AddChildNode(_This_PjNode));
	}
}
void _DEBUG_PRINT_TREE(Ptree xx)
{
	Create_ID_Map(_Debug_ID_Map);
	_This_PRINT_TREE(xx, Jorg.jOrgChart_CreateRootNode());
	Jorg.jOrgChart_Output();
}

#endif
Ptree expr::expression()
{
	return _Expr(-1);
}
Ptree expr::_Expr(int _stop_token)
{
	Ptree ret = _Euqals();
	static char stop[] = { IF, ID, 0 };
	int xx = (*Current_Analysis_File).get_this_tok();
	if (xx == ',')	//逗号当然先算左边的部分
	{
		ret = _CreateNode(',', 0, _Euqals(), ret);
	}
	if (xx == _stop_token)
	{
		(*Current_Analysis_File).gettok();
		return ret;
	}
	else
	{
		//skip until the stop token
	}
	return ret;
}
Ptree expr::_Euqals()
{
	Ptree ret = _binary(1);
	int xx = (*Current_Analysis_File).get_this_tok();
	if (xx == '=')
	{
		ret = _CreateNode('=', 0, ret, _Euqals());//等号是右结合的！
	}
	else if ((_tb[xx] >= 6 && _tb[xx] <= 8) ||
		(_tb[xx] >= 11 && _tb[xx] <= 13))//copy from LCC
	{
		//!!处理 +=  -=  >>= z 暂时不处理
	}
	else
	{
		//!!error
	}
	return ret;
}
Ptree expr::_binary(int level)
{
	Ptree right = nullptr,left = nullptr,ret = nullptr;
	
	ret = _unary();
	_Bin_stack.push_back(ret);
	std::cout<< "Push Value :"<< ret->value<<std::endl;
	for (int k1 = _tb[(*Current_Analysis_File).get_this_tok()]; k1 >= level; k1--)
	{
		while (_tb[(*Current_Analysis_File).get_this_tok()] == k1)
		{
			int op = (*Current_Analysis_File).get_this_tok();
			//(*Current_Analysis_File).gettok();
			_binary(k1 + 1);
			printf("use op %c\n", op);
 
			//
			left = _Bin_stack.back();
			_Bin_stack.pop_back();
			right = _Bin_stack.back();
			_Bin_stack.pop_back();
			//
			ret = _CreateNode(op, 0, left, right);
			
			//.pop_back();
			_Bin_stack.push_back(ret);
		
			ret->op = op;
		}
	}
	return ret;
}
Ptree expr::_unary()
{
	Ptree ret = nullptr;
	int xx = (*Current_Analysis_File).gettok();
	if (xx == '*')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('*', 0, ret, nullptr);
	}
	else if (xx == '&')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('&', 0, ret, nullptr);
	}
	else if (xx == '+')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('+', 0, ret, nullptr);
	}
	else if (xx == '-')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('-', 0, ret, nullptr);
	}
	else if (xx == '~')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('~', 0, ret, nullptr);
	}
	else if (xx == '!')
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('!', 0, ret, nullptr);
	}
	else if (xx == INC)
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('+', 0, ret, _CreateNode(0, INT, nullptr, nullptr));// ++a = a+1
	}
	else if (xx == DEC)
	{
		xx = (*Current_Analysis_File).gettok();
		ret = _unit();
		ret = _CreateNode('-', 0, ret, _CreateNode(0, INT, nullptr, nullptr));// --a = a-1
	}
	else if (xx == '(')
	{
		//类型强制转换暂时不管
		
		//优先级通过递归expr加上postfix处理，LCC神奇的设计 great
		
		ret = _Expr(')');
		_Bin_stack.pop_back();//由于括号内会被push一次，需要吐出来
		printf("00\n");
	}
	else
	{
		ret = _unit();//postfix
	}
	return ret;
}
Ptree expr::_unit()
{
	int xx = (*Current_Analysis_File).get_this_tok();
	Ptree ret = nullptr;
	if (xx == ID)
	{
		ret = _CreateNode(0, ID, nullptr, nullptr);
		ret->value = (*Current_Analysis_File).getLastID();
		//将ID的符号链接加入tree symbol 中
	}
	else if (xx == INT_CONST)
	{
		ret = _CreateNode(0, INT, nullptr, nullptr);
		ret->value = std::to_string((*Current_Analysis_File).getLasrIntValue());
		//将int的值加入tree value 中
	}
	else if (xx == FLOAT_CONST)
	{
		ret = _CreateNode(0, FLOAT, nullptr, nullptr);
	}
	//else string const
	ret = _postfix(ret);

	return ret;

}
Ptree  expr::_postfix(Ptree _unit)//返回时this_token指向下一个operator
{
	Ptree ret = _unit;;
	int xx = (*Current_Analysis_File).gettok();
	if (xx == INC)
	{

	}
	else if (xx == DEC)
	{

	}
	else if (xx == '[')
	{
		//arrage
	}
	else if (xx == '(')
	{
		//call
	}
	else if (xx == '.')
	{
		//struct
	}
	else if (xx == DEREF)
	{
		//for the '->'
	}
	return ret;
}
Ptree expr::_CreateNode(int op, int type, Ptree left, Ptree right)
{
	Ptree ret = new tree;
	ret->op = op;
	ret->_left = left;
	ret->_right = right;
	ret->_type = type;
	//这里需要进行节点检测
	return ret;

}

int expr::_DeleteNode(Ptree xx)
{
	return 0;
}
int expr::_DeleteTree(Ptree xx)
{
	return 0;
}
/*
4		左				||					逻辑或
5		左				&&					逻辑与
6		左				|					位或
7		左				^					位异或
8		左				&					位与
9		左			  == !=					等价
10		左			< > <= >= 				关系
11		左			  << >>					位移
12		左			  + -					加
13		左			 * /%					乘
*/

_expr_table::_expr_table()
{
	_this_table[ANDAND] = 4;
	_this_table[OROR] = 5;
	_this_table['|'] = 6;
	_this_table['^'] = 7;
	_this_table['&'] = 8;
	_this_table[EQL] = 9;
	_this_table[NEQ] = 9;
	_this_table[LEQ] = 10;
	_this_table[GEQ] = 10;
	_this_table['>'] = 10;
	_this_table['<'] = 10;
	_this_table[RSHIFT] = 11;
	_this_table[LSHIFT] = 11;
	_this_table['+'] = 12;
	_this_table['-'] = 12;
	_this_table['*'] = 13;
	_this_table['/'] = 13;
	_this_table['%'] = 13;
}