#include "include_All.h"

#include <cstring>
#include <sstream>

#ifndef LEX_HEEADER

#define LEX_HEEADER

const int Line_Max_Cell = 10;

class Current_Input
{
public:
	explicit Current_Input();
	~Current_Input();

	void operator ++();
	char operator *();
	char operator[](int xx) = delete;

	void BindingFile(char *xx);
private:
	void Fill_Buff(char * xx, int num);
	//std::queue<char> Charactor_List;
	char input[Line_Max_Cell];
	int RemainWord;
	char *CurrentWord = nullptr;
	std::fstream SoureFile;

};

class lex
{
public:
	explicit lex();
	~lex();
	lex(char *xx);
	lex(std::string xx);

	int gettok();
	inline int get_this_tok() const { return _token; }
	inline int getline() const { return line; }
	inline int getletral() const { return letral; }
	inline std::string getLastID() const { return Last_ID_Name; }
	inline int getLastIDhash() const{ return hash; }
	bool _eof;
private:
	int _token;
	int _Get_All_token();
	std::string Last_ID_Name;
	int line, letral, hash;
	Current_Input src;	//source code
	std::vector<std::string> ID_Map;
};

extern lex * Current_Analysis_File;


#endif // !LEX_HEEADER