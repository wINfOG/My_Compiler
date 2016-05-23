#include "jOrgChart_export.h"

jOrgChart_export::jOrgChart_export()
:_RootNode(nullptr)
{
	_File.open("jOrgChart/example/example.html", std::ios::out);


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
	_File << "<!DOCTYPE html>"
		<< "<html><head><meta http - equiv = \"Content-Type\" content = \"text/html; charset=ISO-8859-1\">" << "\n"
		<< "<title>Example</title>" << "\n"
		<< "<link rel = \"stylesheet\" href = \"css/bootstrap.min.css\"/>" << "\n"
		<< "<link rel = \"stylesheet\" href = \"css/jquery.jOrgChart.css\"/>" << "\n"
		<< "<link rel = \"stylesheet\" href = \"css/custom.css\"/>" << "\n"
		<< "<link href = \"css/prettify.css\" type = \"text/css\" rel = \"stylesheet\"/>" << "\n"
		<< "<script type = \"text/javascript\" src = \"prettify.js\"></script>" << "\n"

		<< "<!--jQuery includes-->" << "\n"
		<< "<script type = \"text/javascript\" src = \"https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js\"></script>" << "\n"
		<< "<script type = \"text/javascript\" src = \"https://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/jquery-ui.min.js\"></script>" << "\n"

		<< "<script src = \"jquery.jOrgChart.js\"></script>" << "\n"

		<< "<script>" << "\n"
		<< "jQuery(document).ready(function() {" << "\n"
		<< "$(\"#org\").jOrgChart({" << "\n"
		<< "chartElement: \'#chart\'," << "\n"
		<< "	  dragAndDrop : true" << "\n"
		<< "});" << "\n"
		<< "});" << "\n"
		<< "</script>" << "\n"
		<< "</head>" << "\n"

		<< "<body onload = \"prettyPrint();\">" << "\n"


		<< "<ul id = \"org\" style = \"display:none\">";

	_This_Output_Tree(_RootNode);


	_File << "</ul>"
		<< "<div id = \"chart\" class = \"orgChart\"></div>" << "\n"
		<< "<script>" << "\n"
		<< "jQuery(document).ready(function() {" << "\n"
		<< "$(\"#show-list\").click(function(e){" << "\n"
		<< "e.preventDefault();" << "\n"
		<< "$(\'#list-html\').toggle(\'fast\', function(){" << "\n"
		<< "if ($(this).is(\':visible\')){" << "\n"
		<< "$(\'#show-list\').text(\'Hide underlying list.\');" << "\n"
		<< "$(\".topbar\").fadeTo(\'fast\', 0.9);" << "\n"
		<< "}" << "\n"
		<< "else{" << "\n"
		<< "$(\'#show-list\').text(\'Show underlying list.\');" << "\n"
		<< "$(\".topbar\").fadeTo(\'fast\', 1);" << "\n"
		<< "}" << "\n"
		<< "});" << "\n"
		<< "});" << "\n"
		<< "$(\'#list-html\').text($(\'#org\').html());" << "\n"
		<< "$(\"#org\").bind(\"DOMSubtreeModified\", function() {" << "\n"
		<< "$(\'#list-html\').text(\'\');" << "\n"
		<< "$(\'#list-html\').text($(\'#org\').html());" << "\n"
		<< "prettyPrint();" << "\n"
		<< "});" << "\n"
		<< "});" << "\n"
		<< "</script>" << "\n"
		<< "</body>" << "\n"
		<< "</html>"; 
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
	delete _node;
	_node = nullptr;
}
