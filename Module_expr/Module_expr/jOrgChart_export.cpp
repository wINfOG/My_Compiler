#include "jOrgChart_export.h"

jOrgChart_export::jOrgChart_export()
:_RootNode(nullptr)
{
	_File.open("example.html", std::ios::out);
}
jOrgChart_export::jOrgChart_export(char *_path)
: _RootNode(nullptr)
{
	_File.open(_path, std::ios::out);
}
jOrgChart_export::~jOrgChart_export()
{
	_File.close();
	if (_RootNode != nullptr)
		_This_Delete_Tree(_RootNode);
}

PjNode jOrgChart_export::jOrgChart_CreateRootNode()
{
	if (nullptr != _RootNode)
		_This_Delete_Tree(_RootNode);

	_RootNode = new jNode;
	_RootNode->_LeftNode = nullptr;
	_RootNode->_RightNode = nullptr;
	return _RootNode;
}
PjNode jOrgChart_export::jOrgChart_AddChildNode(PjNode _Father)
{
	PjNode xx = new jNode;
	xx->_LeftNode = nullptr;
	xx->_RightNode = nullptr;

	if (_Father->_LeftNode == nullptr) _Father->_LeftNode = xx;
	else if (_Father->_RightNode == nullptr) _Father->_RightNode = xx;
	else
	{
		printf("Error too many node adding \n");
		exit(3);
	}
	return xx;
}
void jOrgChart_export::jOrgChart_Output()
{
	_This_Output_Tree(_RootNode);
}


void jOrgChart_export::_This_Output_Tree(PjNode _node)
{
	//li
	_File << "<li>";
	//export;
	_File << _node->_in;
	if (_node->_LeftNode != nullptr || _node->_RightNode != nullptr)
	{
		//ui
		_File << "<ul>";
		if (_node->_LeftNode != nullptr)
			_This_Output_Tree(_node->_LeftNode);
		if (_node->_RightNode != nullptr)
			_This_Output_Tree(_node->_RightNode);
		//ui
		_File << "</ul>";
	}
	_File << "</li>";
	//li
}
void jOrgChart_export::_This_Delete_Tree(PjNode _node)
{
	if (_node->_LeftNode != nullptr)
		_This_Delete_Tree(_node->_LeftNode);
	if (_node->_RightNode != nullptr)
		_This_Delete_Tree(_node->_RightNode);
	free(_node);
	_node = nullptr;
}
