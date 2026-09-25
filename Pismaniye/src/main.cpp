#include "Parser.h"
int main()
{	
	baz::Parser parser(cmake_PROJECT_RES "tinybasic.basic");
	parser.run();
}