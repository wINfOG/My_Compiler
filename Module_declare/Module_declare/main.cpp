#include "include_All.h"
#include "lex.h"
#include "token.h"
#include "declaration.h"
lex * Current_Analysis_File;	//current analysis file
std::vector<std::string> ID_Token_Map(128);

int main()
{
	int key = 0;
	lex LL("Test");

	Create_ID_Map(ID_Token_Map);
	Current_Analysis_File = &LL;
	Declaration decl;
	for (decl._doit(nullptr); Current_Analysis_File->_eof != true; decl._doit(nullptr));
	
	


	
	return 0;
}