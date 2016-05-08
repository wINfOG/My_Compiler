#include "include_All.h"
#include "lex.h"
#include "token.h"

int main()
{
	int key = 0;
	lex LL("Test");
	std::vector<std::string> xx(128);
	Create_ID_Map(xx);
	key = LL.gettok();
	while (key)
	{
		std::cout << xx[key];
		key = LL.gettok();
	}
	
	return 0;
}