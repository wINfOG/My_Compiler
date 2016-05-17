#include "include_All.h"
#include "symbol.h"
#ifndef Declaration_HEADER
#define Declaration_HEADER




class Declaration
{
public:
	explicit Declaration();
	virtual ~Declaration();
	void _doit(Psymbol _last_token);
protected:

private:
	Declaration(const Declaration & Ths); // no copy
	std::vector<std::vector<symbol> > layer; //这个文件的符号表
	int scope; //当前声明的层次 0 表示global 数字越大越深

	int _doit_type(symbol & _this);
	int _doit_identify(symbol & _this);
	int _doit_postfix(symbol & _this);
};

class Global_declaration : public Declaration
{
public:
private:
};

class Local_declaration : public Declaration
{
public:
private:
};




#endif // !Declaration_HEADER