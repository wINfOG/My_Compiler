#include "include_All.h"
#include "lex.h"
#include "token.h"
#include "expr.h"
lex * Current_Analysis_File;	//current analysis file
std::vector<std::string> ID_Token_Map(128);

int main()
{
	int key = 0;
	lex LL("Test");
	Create_ID_Map(ID_Token_Map);
	Current_Analysis_File = &LL;
	/*
	key = LL.gettok();
	while (key)
	{
		std::cout << ID_Token_Map[key];
		key = LL.gettok();
	}
	*/
	expr test;
	
	_DEBUG_PRINT_TREE(test.expression());
	return 0;
}