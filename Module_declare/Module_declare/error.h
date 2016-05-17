#include "lex.h"



void ERROR(char str[])
{
	int xx;
	//错误处理还要继续完善啊
	std::cout << "ERROR in line:" << (*Current_Analysis_File).getline() << "   " << str << std::endl;
	while (xx = Current_Analysis_File->gettok())
	{
		if (xx == ';' || xx == '\n')
			break;
	}
}
void ERROR()
{
	int xx;
	//错误处理还要继续完善啊
	printf("an error happen in line; %d  but this module still in coding\n", Current_Analysis_File->getline());
	while (xx = Current_Analysis_File->gettok())
	{
		if (xx == ';' || xx == '\n')
			break;
	}
}
void WARNING()
{
	printf("Yes there is a warning in line %d , it means I don't complete this module\n");
	//暂时未完成
}
////
////
void compiler_Error()
{
	printf("compiler error !!!\n ");
	getchar();
	exit(2);
}
void _Jmp_Next_Line()
{
	int xx;
	printf("Next Keyword \n");
	while (xx = Current_Analysis_File->gettok())
	{
		if (xx == ';' || xx == '\n')
			break;
	}
}
