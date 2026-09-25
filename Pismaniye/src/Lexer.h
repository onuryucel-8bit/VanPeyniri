#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <optional>
#include <algorithm>
#include <filesystem>

#include <magic_enum/magic_enum.hpp>

#include "Tokens.h"

namespace fs = std::filesystem;

namespace baz
{
	class Lexer
	{
	public:

		Lexer(fs::path path);
		~Lexer();
		baz::Token getToken();

	private:
		//================================================//
		std::string readFile(fs::path path);
		char peek(size_t offset = 1);		
		void nextChar();

		bool skipComments();
		bool skipWhiteSpace();

		bool checkIfKeyword(std::string token);

		void printError(std::string message);
		//================================================//

		std::string m_program;
		int m_position = -1;
		char m_currentChar = 0;
	};
}