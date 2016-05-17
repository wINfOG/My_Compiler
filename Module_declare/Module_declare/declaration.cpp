#include "declaration.h"
#include "lex.h"
#include "token.h"
#include "error.h"

using namespace TOKEN_TO_NUM;
std::vector<std::string> _this_debug_ID_Token_Map(128);

#ifdef _DEBUG
void _DBG_Print_Decl_Information(symbol _this)
{
	std::cout << "DBG_Decl_Information： Name: " << _this.name
		<< "	hash:" << _this.hash << '\n'
		<< "	scope:" << _this.scope
		<< "	type:" << _this_debug_ID_Token_Map[_this.type.type]
		<< "	size:" << _this_debug_ID_Token_Map[_this.type.size] << '\n'
		<< std::endl;
}
#endif

Declaration::Declaration() :
scope(0)
{
#ifdef _DEBUG
	Create_ID_Map(_this_debug_ID_Token_Map);
#endif
	//这里添加global 
	layer.resize(3);
}
Declaration::~Declaration()
{

}
//处理出现类型，写入this中
//正确返回0，识别出的语法错误返回-1， 
int Declaration::_doit_type(symbol & _this)
{
	int cls = 0, cons = 0, sign = 0, size = 0, type = 0, vol = 0;//LCC实现方式十分合理啊

	int xx = 0;
	for (;;)
	{
		xx = (*Current_Analysis_File).gettok();
		//匹配关键字
		//这里所谓平行，就是指的是二个关键词不能同时出现，比如static extern int a; 就不行
		//所有关键字除了long long以外，都不能同时出现2次
		if (xx == STATIC || xx == EXTERN)
		{
			if (cls == 0) cls = xx;
			else { ERROR(); return -1; }
		}
		else if (xx == REGISTER)
		{
			if (cls == 0) cls = xx;
			else { ERROR(); return -1; }
			//对于register寄存器类型，作用域不能是全局
			if (scope == 0)
			{
				ERROR(); return -1;
			}
		}
		else if (xx == TYPEDEF)
		{
			if (cls == 0) cls = xx;
			else { ERROR(); return -1; }
			//这玩意需要特殊处理,放在后面
		}
		else if (xx == CONST)
		{
			if (cons == 0) cons = xx;
			else { ERROR(); return -1; }
		}
		else if (xx == VOLATILE)
		{
			if (vol == 0) vol = xx;
			else { ERROR(); return -1; }
		}
		else if (xx == SIGNED || xx == UNSIGNED)
		{
			if (sign == 0) sign = xx;
			else { ERROR(); return -1; }
		}
		else if (xx == LONG || xx == SHORT)
		{
			//注意longlong
			if (size == 0) size = xx;
			else if (size == LONG) size = LONGLONG;
			else { ERROR(); return -1; }

		}
		else if (xx == VOID || xx == CHAR || xx == INT || xx == FLOAT || xx == DOUBLE)
		{
			if (type == 0) type = xx;
			else { ERROR(); return -1; }
		}
		else if (xx == ENUM || xx == STRUCT || xx == UNION)
		{
			//结构体之类的暂时不做处理，写完了再写它
			WARNING();
		}
		else if (xx == '*')
		{
			//暂时不支持坑爹的指针
			WARNING();
		}
		else if (xx == ID)
		{
			//ID 分为2部分，如果是typedef的ID 当作type去处理,当然还没完成
			//一般ID直接break
			break;
		}
		else
		{
			if (xx == ',')
				//?? Error()?
				return xx;
			else
				return -1;
		}
	}

	//处理一些非法组合的问题!
	if (type == 0)
	{
		if (size == 0)
		{
			ERROR("type must be defined"); return -1;
		}
		type = INT;
	}
	if (size == SHORT     && type != INT
		|| size == LONG + LONG && type != INT
		|| size == LONG      && type != INT && type != DOUBLE
		|| sign && type != INT && type != CHAR)
		ERROR("invalid type specification\n");	//这段直接抄LCC的


	
	//组合声明加入_this

	_this.line = (*Current_Analysis_File).getline();
	_this.letral = Current_Analysis_File->getletral();

	
	_this.scope = scope;
	_this.type.type = type;
	_this.type.size = size;

	

	return 0;
}
//处理ID类型，写入符号表
//正常返回0，出错返回非0
int Declaration::_doit_identify(symbol & _this)
{
	//通过hash与name查找 ID是不是重定义
	int _this_ID_hash = Current_Analysis_File->getLastIDhash();
	std::string _this_ID_name = Current_Analysis_File->getLastID();
	for (auto i = layer[scope].cbegin(); i != layer[scope].cend(); i++)
	{
		if (i->hash == _this_ID_hash && i->name == _this_ID_name)
		{
			ERROR("Redeclaration"); return 3;
		}
	}
	//添加进符号表
	_this.name = _this_ID_name;
	_this.hash = _this_ID_hash;
	if (_this.name.size() == 0) compiler_Error();
	layer[scope].push_back(_this);
	_DBG_Print_Decl_Information(_this);
	return 0;
}
//处理后缀，错误返回-1，否则返回下一个token
int Declaration::_doit_postfix(symbol & _this)
{
	static int xx;
	xx = (*Current_Analysis_File).get_this_tok();
	if (xx == '[')
	{
		while (xx == '[')
		{

			xx = (*Current_Analysis_File).gettok();
			if (xx == ']')
			{
			//do something
				WARNING();

				xx = (*Current_Analysis_File).gettok();
			}
			else
			{
				//这里需要使用expr进行分析，因为有x[1+2] 这种玩意 
				WARNING();

				xx = (*Current_Analysis_File).gettok();
				if (xx != ']')
				{
				
					ERROR(); return 0;
				}
				else
					xx = (*Current_Analysis_File).gettok();
			}
		}
		return xx;
	}
	//如果后面跟的是()是函数声明或者调用，就比较复杂了，需要进一步深入
	else if (xx == '(')
	{
		char _parameter_num = '1';
		int _t_ret = -1;
		scope++;
		while (xx != ')')
		{
			_t_ret = _doit_type(_this);
			if (0 == _t_ret)
			{
				if (0 == _doit_identify(_this))
				{
					xx = (*Current_Analysis_File).gettok();
					xx = _doit_postfix(_this);
					if (xx == -1)
						return -1;
				}
				else
				{
					ERROR("2"); return -1;
				}
			}
			else
			{
				
				_this.name = "_@";
				_this.name += _parameter_num;
				_this.hash = 0;

				_parameter_num++;

				xx = _doit_postfix(_this);
				if (xx == -1)
					return -1;
				layer[scope].push_back(_this);
				_DBG_Print_Decl_Information(_this);
			}

			if (xx == ',' || xx == ')'){  }
			else { 
				ERROR("3"); return -1; }
		}
		xx = (*Current_Analysis_File).gettok();
		if (xx == '{')
		{
			//!!实现函数
			if (scope != 1)
			{
				ERROR("Can not define the function in there");
			}

			while (xx != '}')
			{
				_doit(nullptr);
			}

		}
		else
		{
			scope--;
			//记录函数声明
			return xx;
		}

	}
	else
		return xx;
	return xx;
}
void Declaration::_doit(Psymbol _last_token)
{
	symbol _this;
	if (_last_token != nullptr)
		_this = *_last_token;

	int xx = 0;

	if (0 == _doit_type(_this))
	{
		if (0 == _doit_identify(_this))
		{
			xx = (*Current_Analysis_File).gettok();
			xx = _doit_postfix(_this);
			if (xx == -1)
				return;
		}

		else
			return;
	}
	else return;




	//处理进一步的 初始赋值之类的
	//


	//处理并列
	if (xx == ',')
	{
		while (xx == ',')
		{
			//_DBG_Print_Decl_Information(_this);
			if (0 == _doit_identify(_this))
			{
				xx = (*Current_Analysis_File).gettok();
				xx = _doit_postfix(_this);
				if (xx == -1)
					return;
			}
		}
	}
	if (xx == ';')
	{
		//_DBG_Print_Decl_Information(_this);
	}
	else
	{
		ERROR("1_1");
	}
}
