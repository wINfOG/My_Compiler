#include "include_All.h"

#ifndef token_HEADER

#define token_HEADER

namespace TOKEN_TO_NUM
{

	enum
	{
		FLOAT = 1,
		DOUBLE = 2,
		CHAR = 3,
		SHORT = 4,
		INT = 5,
		UNSIGNED = 6,
		POINTER = 7,
		VOID = 8,
		STRUCT = 9,
		UNION = 10,
		FUNCTION = 11,
		ARRAY = 12,
		ENUM = 13,
		LONG = 14,
		CONST = 15,
		VOLATILE = 16,
		LONGLONG = 28,
		//-----
		ID = 32,
		FLOAT_CONST = 34,
		INT_CONST = 35,
		STRING_CONST = 36,

		INC = 39,

		DEC = 48,
		DEREF = 49,
		ANDAND = 50,
		OROR = 51,
		LEQ = 52,
		EQL = 53,
		NEQ = 54,
		GEQ = 55,
		RSHIFT = 56,
		LSHIFT = 57,
		ELLIPSIS = 64,
		SIZEOF = 65,

		AUTO = 67,
		BREAK = 68,
		CASE = 69,
		CONTINUE = 70,
		DEFAULT = 71,
		DO = 72,
		ELSE = 73,
		EXTERN = 74,
		FOR = 75,
		GOTO = 76,
		IF = 77,
		REGISTER = 78,
		RETURN = 79,
		SIGNED = 80,
		STATIC = 81,
		SWITCH = 82,
		TYPEDEF = 83,
		WHILE = 84,
		TYPECODE = 85,
		FIRSTARG = 86,
	};
}
/* $Id$ */
/*
xx(symbol,	value,	prec,	op,	optree,	kind,	string)
[xy][xy]\([0-9,A-Z,a-z]+([\, ][0-9]+)[0-9 a-z A-Z ,  ]+ ([\"][a-z A-Z]+[\"])\)
\1,\2
*/
inline void Create_ID_Map(std::vector<std::string> &xx)
{
	xx[0] = "";
	xx[1] = "float";
	xx[2] = "double";
	xx[3] = "char";
	xx[4] = "short";
	xx[5] = "int";
	xx[6] = "unsigned";
	xx[7] = "pointer";
	xx[8] = "void";
	xx[9] = "struct";
	xx[10] = "union";
	xx[11] = "function";
	xx[12] = "array";
	xx[13] = "enum";
	xx[14] = "long";
	xx[15] = "const";
	xx[16] = "volatile";
	xx[17] = "\n"; //<---
	xx[18] = " ";
	xx[19] = "\r";
	xx[20] = "\t";
	xx[21] = "";
	xx[22] = "";
	xx[23] = "";
	xx[24] = "";
	xx[25] = "";
	xx[26] = "";
	xx[27] = "";
	xx[28] = "long long";
	xx[29] = "";
	xx[30] = "";
	xx[31] = "const volatile";
	xx[32] = "identifier";
	xx[33] = "!";
	xx[34] = "floating constant";
	xx[35] = "integer constant";
	xx[36] = "string constant";
	xx[37] = "%";
	xx[38] = "&";
	xx[39] = "++";
	xx[40] = "(";
	xx[41] = ")";
	xx[42] = "*";
	xx[43] = "+";
	xx[44] = ",";
	xx[45] = "-";
	xx[46] = ".";
	xx[47] = "/";
	xx[48] = "--";
	xx[49] = "->";
	xx[50] = "&&";
	xx[51] = "||";
	xx[52] = "<=";
	xx[53] = "==";
	xx[54] = "!=";
	xx[55] = ">=";
	xx[56] = ">>";
	xx[57] = "<<";
	xx[58] = ":";
	xx[59] = ";";
	xx[60] = "<";
	xx[61] = "=";
	xx[62] = ">";
	xx[63] = "?";
	xx[64] = "...";
	xx[65] = "sizeof";
	xx[66] = "";
	xx[67] = "auto";
	xx[68] = "break";
	xx[69] = "case";
	xx[70] = "continue";
	xx[71] = "default";
	xx[72] = "do";
	xx[73] = "else";
	xx[74] = "extern";
	xx[75] = "for";
	xx[76] = "goto";
	xx[77] = "if";
	xx[78] = "register";
	xx[79] = "return";
	xx[80] = "signed";
	xx[81] = "static";
	xx[82] = "switch";
	xx[83] = "typedef";
	xx[84] = "while";
	xx[85] = "__typecode";
	xx[86] = "__firstarg";
	xx[87] = "";
	xx[88] = "";
	xx[89] = "";
	xx[90] = "";
	xx[91] = "[";
	xx[92] = "";
	xx[93] = "]";
	xx[94] = "^";
	xx[95] = "";
	xx[96] = "";
	xx[97] = "";
	xx[98] = "";
	xx[99] = "";
	xx[100] = "";
	xx[101] = "";
	xx[102] = "";
	xx[103] = "";
	xx[104] = "";
	xx[105] = "";
	xx[106] = "";
	xx[107] = "";
	xx[108] = "";
	xx[109] = "";
	xx[110] = "";
	xx[111] = "";
	xx[112] = "";
	xx[113] = "";
	xx[114] = "";
	xx[115] = "";
	xx[116] = "";
	xx[117] = "";
	xx[118] = "";
	xx[119] = "";
	xx[120] = "";
	xx[121] = "";
	xx[122] = "";
	xx[123] = "{";
	xx[124] = "|";
	xx[125] = "}";
	xx[126] = "~";
	xx[127] = "end of input";
}


#endif // !token_HEADER