#include "lex.h"
#include "token.h"
Current_Input::Current_Input(){}
Current_Input::~Current_Input(){ SoureFile.close(); }

void Current_Input::Fill_Buff(char * xx, int num)
{
	if (SoureFile.eof() == true)//end
	{
		memset(input, 0, Line_Max_Cell);
		return;
	}
	memset(input, 0, num);
	SoureFile.read(input, num);

	if (SoureFile.eof() == true)
		RemainWord = strlen(input);
	else
		RemainWord = num;
}
void Current_Input::BindingFile(char * xx)
{
	memset(input, 0, Line_Max_Cell);
	SoureFile.open(xx);
	Fill_Buff(input, Line_Max_Cell);
	CurrentWord = input;
}
void Current_Input::operator++()
{
	if (RemainWord == 0)
	{
		Fill_Buff(input, Line_Max_Cell);
		CurrentWord = input;
	}
	else
	{
		CurrentWord++;
		RemainWord--;
	}
}

char Current_Input::operator* ()
{
	if (RemainWord == 0)
	{
		Fill_Buff(input, Line_Max_Cell);
		CurrentWord = input;
	}
	return *CurrentWord;
}
lex::lex() :
line(1), letral(0), _eof(false), hash(0)
{}
lex::lex(char *xx) :
line(1), letral(0), _eof(false), hash(0)
{
	ID_Map.resize(128);
	src.BindingFile(xx);
	Create_ID_Map(ID_Map);
}
lex::~lex()
{
}
int lex::gettok()
{
	int xx = _Get_All_token();
	while (xx == 18 || xx == '\r' || xx == '\t' || xx == 17)
		xx = _Get_All_token();
	
	_token = xx;
	return xx;
}
int lex::_Get_All_token()
{
	char token;
	letral++;
	while (token = *src)
	{
		++src;
		// parse token here
		if (token == ' ') { return 18; }
		else if (token == '\r'){ return 19; }
		else if (token == '\t') { return 20; }
		else if (token == '\n'){
			line++;  letral = 0;//printf("line:%d", line); 
			return 17;
		}
		else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_'))
		{
			std::stringstream  ID_String;
	
			ID_String << token;
			hash = token;
			while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {

				//printf("%c", *src);
				ID_String << (*src);
				hash = hash * 147 + *src;
				++src;
			}
			for (unsigned int i = 1; i < 128; i++)
			{

				if (ID_Map[i] == ID_String.str())
					return i;
			}
			//没找到
			Last_ID_Name = ID_String.str(); //保存ID名会在之后使用
			return 32;
		}
		else if (token >= '0' && token <= '9')
		{
			int token_value = token - '0';
			while (*src >= '0' && *src <= '9'){ token_value = token_value * 10 + (*src - '0'); ++src; }
			//printf("num:  %d\n", token_value);
			return 35;
		}
		else if (token == '"' || token == '\'')
		{
			std::stringstream  Char_String;
			while (*src != 0 && *src != token)
			{
				//printf("%c", *src);
				Char_String << *src;
				++src;
			}
			++src;

			return 36;

		}
		else if (token == '/')
		{
			if (*src == '/') { while (*src != 0 && *src != '\n') ++src; }
			else { return '/'; }
		}
		else if (token == '=')
		{
			// parse '==' and '='
			if (*src == '=') { ++src; return 53; }
			else { return '='; }
		}
		else if (token == '+')
		{
			// parse '+' and '++'
			if (*src == '+') { ++src; return 39; }
			else { return '+'; }
		}
		else if (token == '-')
		{
			// parse '-' and '--'
			if (*src == '-') { ++src; return 48; }
			else { return '-'; }
		}
		else if (token == '!')
		{
			// parse '-' and '--'
			if (*src == '=') { ++src; return 54; }
			else { return '!'; }
		}
		else if (token == '{')	return '{';
		else if (token == '}')	return '}';
		else if (token == '(')	return '(';
		else if (token == ')')	return ')';
		else if (token == ';')	return ';';
		else if (token == '[')	return '[';
		else if (token == ']')	return ']';
		else if (token == ',')	return ',';
		else
		{
			printf("Error!!! unknow character < %c >  < %x >\n", token, token);
		}

	}
	//error or end of file
	_eof = true;
	return 0;
}
