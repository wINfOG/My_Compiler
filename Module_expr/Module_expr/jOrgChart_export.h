#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#ifndef jOrgChart_export_HEADER
#define jOrgChart_export_HEADER

typedef struct _jNode jNode;
typedef struct _jNode * PjNode;
struct _jNode
{
	std::string _in;
	PjNode _LeftNode;
	PjNode _RightNode;
};


class jOrgChart_export
{
public:
	jOrgChart_export();
	jOrgChart_export(char *_path);
	~jOrgChart_export();
	PjNode jOrgChart_CreateRootNode();
	PjNode jOrgChart_AddChildNode(PjNode _Father);
	void jOrgChart_Output();
private:
	void _This_Output_Tree(PjNode _node);
	void _This_Delete_Tree(PjNode _node);

	std::ofstream _File;
	PjNode _RootNode;
};

#endif