#include "Lexer.h"
namespace baz
{
	Lexer::Lexer(fs::path path)
	{
		if (!std::filesystem::exists(path))
		{
			std::cout << "Dosya bulunamadi: " << path << "\n";
		}

		m_program = readFile(path);
		nextChar();
	}

	Lexer::~Lexer()
	{
	}

	Token Lexer::getToken()
	{
		bool consumed = true;
		while (consumed)
		{
			consumed = skipComments();
			consumed |= skipWhiteSpace();
		}

		Token retToken;

		//degiskenler, anahtar kelimeler
		if (std::isalpha(m_currentChar))
		{
			int startPos = m_position;
			int length = 1;
			
			while (std::isalnum(peek()) || peek() == '_' || std::isdigit(peek()))
			{
				length++;
				nextChar();
			}

			std::string tokenStr = m_program.substr(startPos, length);

			std::string copyStr = tokenStr;

			//tokenStr.toUpper();
			std::transform(copyStr.begin(), copyStr.end(), copyStr.begin(), ::toupper);
			
			if (checkIfKeyword(copyStr))
			{
				std::optional<TokenType> enumVal = magic_enum::enum_cast<TokenType>(copyStr);
				retToken.m_type = enumVal.value();				
				retToken.m_text = copyStr;
			}
			else
			{
				retToken.m_type = TokenType::IDENTIFIER;
				retToken.m_text = tokenStr;
			}
		}
		//sayilar
		else if (std::isdigit(m_currentChar))
		{
			int startPost = m_position;
			int length = 1;

			while (std::isdigit(peek()))
			{
				length++;
				nextChar();
			}

			retToken.m_type = TokenType::NUMBER_INT;

			//number_float
			if (peek() == '.')
			{
				length += 2;
				nextChar();
				nextChar();
				while (std::isdigit(peek()))
				{
					length++;
					nextChar();
				}
				retToken.m_type = TokenType::NUMBER_FLOAT;
			}

			retToken.m_text = m_program.substr(startPost, length);

			//retToken.m_lineNumber = m_lineNumber;
		}
		//karakterler
		else
		{
			switch (m_currentChar)
			{
			case '&':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::AND;

				if (peek() == '&')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::AND_AND;
					nextChar();
				}
				else if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::AND_EQUAL;
					nextChar();
				}
				break;

			case '|':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::OR;

				if (peek() == '|')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::OR_OR;
					nextChar();
				}
				else if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::OR_EQUAL;
					nextChar();
				}
				break;

			case '~':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::BITWISE_NOT;
				break;

			case '^':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::XOR;

				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::XOR_EQUAL;
					nextChar();
				}

				break;

			case '%':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::MODULO;
				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::MODULO_EQUAL;
					nextChar();
				}
				break;

			case ',':
				retToken.m_text = ',';
				retToken.m_type = TokenType::COMMA;
				break;

			case '.':
				retToken.m_text = '.';
				retToken.m_type = TokenType::DOT;

				if (peek() == '.' && peek(2) == '.')
				{
					retToken.m_text = "...";
					retToken.m_type = TokenType::ELLIPSES;

					nextChar();
					nextChar();
				}
				break;

			case '!':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::NOT;

				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::NOT_EQUAL;
					nextChar();
				}
				break;

			case '>':
				retToken.m_text = ">";
				retToken.m_type = TokenType::GREATER_THAN;

				if (peek() == '=')
				{
					retToken.m_text = ">=";
					retToken.m_type = TokenType::EQUAL_GREATER;
					nextChar();
				}
				else if (peek() == '>')
				{
					retToken.m_text = ">>";
					retToken.m_type = TokenType::RIGHT_SHIFT;
					nextChar();

					if (peek() == '=')
					{
						retToken.m_text = ">>=";
						retToken.m_type = TokenType::RIGHT_SHIFT_EQUAL;
						nextChar();
					}
				}

				break;

			case '<':
				retToken.m_text = "<";
				retToken.m_type = TokenType::LESS_THAN;

				//<=
				if (peek() == '=')
				{
					retToken.m_text = "<=";
					retToken.m_type = TokenType::EQUAL_LESS;
					nextChar();
				}
				//<<
				else if (peek() == '<')
				{
					retToken.m_text = "<<";
					retToken.m_type = TokenType::LEFT_SHIFT;
					nextChar();

					//<<=
					if (peek() == '=')
					{
						retToken.m_text = "<<=";
						retToken.m_type = TokenType::LEFT_SHIFT_EQUAL;
						nextChar();
					}
				}
				break;

			case '[':
				retToken.m_text = "[";
				retToken.m_type = TokenType::LSQUARE;
				break;

			case ']':
				retToken.m_text = "]";
				retToken.m_type = TokenType::RSQUARE;
				break;

			case '{':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::LBRACKET;
				break;

			case '}':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::RBRACKET;
				break;

			case '(':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::LPAREN;
				break;

			case ')':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::RPAREN;
				break;

			case '"':
			{
				nextChar();
				int startPost = m_position;

				int length = 1;

				while (std::isalpha(peek()))
				{
					length++;
					nextChar();
				}

				retToken.m_text = m_program.substr(startPost, length);
				retToken.m_type = TokenType::STRING_LITERAL;

				nextChar();
				break;
			}
			case '\'':
				nextChar();
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::CHAR_CONSTANT;
				nextChar();
				break;

			case '=':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::ASSIGN;

				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::EQUAL_EQUAL;
					nextChar();
				}
				break;

			case ';':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::SEMICOLON;
				break;

			case '+':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::PLUS;
				if (peek() == '+')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::INCREMENT;
					nextChar();
				}
				else if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::PLUS_EQUAL;
					nextChar();
				}
				break;

			case '-':
				retToken.m_text = "-";
				retToken.m_type = TokenType::MINUS;
				if (peek() == '-')
				{
					retToken.m_text = "--";
					retToken.m_type = TokenType::DECREMENT;
					nextChar();
				}
				else if (peek() == '=')
				{
					retToken.m_text = "-=";
					retToken.m_type = TokenType::MINUS_EQUAL;
					nextChar();
				}
				else if (peek() == '>')
				{
					retToken.m_text = '->';
					retToken.m_type = TokenType::ARROW;
					nextChar();
				}
				break;

			case '*':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::ASTERISK;

				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::ASTERISK_EQUAL;
					nextChar();
				}
				break;

			case '/':
				retToken.m_text = m_program.substr(m_position, 1);
				retToken.m_type = TokenType::SLASH;

				if (peek() == '=')
				{
					retToken.m_text = m_program.substr(m_position, 2);
					retToken.m_type = TokenType::SLASH_EQUAL;
					nextChar();
				}
				break;

			case '\n':
				retToken.m_text = "newline(\\n)";
				retToken.m_type = TokenType::NEWLINE;
				break;


			case '\t':
				retToken.m_text = "tabb(\\t)";
				retToken.m_type = TokenType::NEWLINE;
				break;

			case EOF:
				retToken.m_text = "eof";
				retToken.m_type = TokenType::eof;
				break;

			default:

				std::cout << "lexer default case" << (int)m_currentChar << "\n";
				break;
			}

			//retToken.m_lineNumber = m_lineNumber;
		}
		
		nextChar();
		return retToken;
	}

	void Lexer::nextChar()
	{
		m_position++;
		if (m_position >= m_program.length())
		{
			m_currentChar = EOF;
		}
		else
		{
			m_currentChar = m_program[m_position];
		}
	}

	void Lexer::printError(std::string message)
	{
		std::cout << "ERROR::" << __FUNCTION__ << "() " << message << "\n";
	}

	bool Lexer::checkIfKeyword(std::string token)
	{
		std::optional<TokenType> tempToken = magic_enum::enum_cast<TokenType>(token);
		if (tempToken.has_value())
		{
			return true;
		}

		return false;
	}

	bool Lexer::skipWhiteSpace()
	{
		bool flag = false;

		if (m_currentChar == ' ' ||
			m_currentChar == '\t' ||
			m_currentChar == '\n' ||
			m_currentChar == '\r')
		{
			flag = true;
		}

		while (m_currentChar == ' ' ||
			m_currentChar == '\t' ||
			m_currentChar == '\n' ||
			m_currentChar == '\r'
			)
		{
			nextChar();			
		}

		return flag;
	}

	bool Lexer::skipComments()
	{
		bool flag = false;

		if (m_currentChar == '/' && peek() == '/')
		{
			while (m_currentChar != '\n' && m_currentChar != '\0')
			{
				nextChar();
			}

			flag = true;
		}
		if (m_currentChar == '/' && peek() == '*')
		{
			nextChar(); // imlec => *
			nextChar(); // imlec => bir sonraki karakter

			while (!(m_currentChar == '*' && peek() == '/') && m_currentChar != '\0')
			{
				nextChar();				
			}

			if (m_currentChar == '*' && peek() == '/')
			{
				nextChar(); // imlec => '/'
				nextChar(); //imlec => bir sonraki karakter
			}
			else
			{
				printError("aciklama satiri kapatmayi unuttun /**/");
			}
			
			flag = true;
		}

		return flag;
	}

	char Lexer::peek(size_t offset)
	{
		if (m_position + offset >= m_program.length())
		{
			return EOF;
		}
		else
		{
			return m_program[m_position + offset];
		}
	}

	std::string Lexer::readFile(fs::path path)
	{
		std::fstream file(path);

		if (!file.is_open())
		{
			std::cout << "ERROR:: couldnt open the file\n";
			return "";
		}

		std::stringstream ss;

		ss << file.rdbuf();

		return ss.str();
	}

}