#pragma once

/*
https://chibiakumas.com/6502/#Lesson1
6502 assembler

#	#16384	16384	Decimal Number
#%	#%00001111	%00001111	Binary Number
#$	#$4000	&4000	Hexadecimal number
#'	#'a	'a'	ascii value

12345	(16384)	decimal memory address
$	$4000	(&4000)	Hexadecimal memory address

*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

#include "Lexer.h"

#include "Tokens.h"

#include "MemoryManager.h"

#ifdef _MSVC_style
	#define printFuncName() std::cout << "---------------------------" << __FUNCSIG__ << "()\n"
#else
	#define printFuncName() std::cout << "---------------------------" << __FUNCTION__ << "()\n"
#endif

namespace baz
{
	class Parser
	{
	public:
		Parser(fs::path path);
		~Parser();

		//translation-unit
		void run();
	private:
		bool matchPeek(TokenType tokenType);
		bool matchCurrent(TokenType tokenType);

		void stmt();						

		void nextToken();
		void printError(std::string message);

		void outputAsm(std::string str);

		void printCurrentToken();

		//========================================//
		void statements();
		void if_stmt();
		void print_stmt();
		void input_stmt();
		void let_stmt();
		void goto_stmt();
		void assignment_stmt();

		baz::Token expression();
		baz::Token term();
		baz::Token factor();
		void identifier();
		void relational_op();
		//========================================//
		

		baz::Token m_currentToken;
		baz::Token m_peekToken;
		baz::Lexer m_lexer;

		std::fstream m_file;

		MemoryManager m_memoryManager;

		int m_tabCounter = 0;
	};
}