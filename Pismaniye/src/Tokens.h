#pragma once

namespace baz
{
    enum TokenType
    {
        NUMBER_INT,         // 3
        NUMBER_FLOAT,       // 3.14
        PLUS,               // +
        MINUS,              // -
        ASTERISK,           // *
        SLASH,              // /
        ASSIGN,             // =
        SEMICOLON,          // ;
        LPAREN,             // (
        RPAREN,             // )
        LBRACKET,           // {
        RBRACKET,           // }
        LSQUARE,            // [
        RSQUARE,            // ]

        NOT,                // !
        AND,                // &
        OR,                 // |
        XOR,                // ^
        AND_AND,            // &&
        OR_OR,              // ||
        INCREMENT,          // ++
        DECREMENT,          // --
        MODULO,             // %
        LEFT_SHIFT,         // <<
        RIGHT_SHIFT,        // >>
        BITWISE_NOT,        // ~
        PLUS_EQUAL,         // +=
        MINUS_EQUAL,        // -=
        ASTERISK_EQUAL,     // *=
        SLASH_EQUAL,        // /=
        AND_EQUAL,          // &=
        OR_EQUAL,           // |=
        XOR_EQUAL,          // ^=
        MODULO_EQUAL,       // %=
        LEFT_SHIFT_EQUAL,   // <<=
        RIGHT_SHIFT_EQUAL,  // >>=
        COMMA,              // ,
        DOT,                // .
        ELLIPSES,           // ...
        ARROW,              // ->

        LESS_THAN,          // <
        GREATER_THAN,       // >
        NOT_EQUAL,          // !=
        EQUAL_EQUAL,        // ==
        EQUAL_LESS,         // <=
        EQUAL_GREATER,      // >=

        STRING_LITERAL,     // "abcdef"
        CHAR_CONSTANT,      // 'a'
        IDENTIFIER,

        //tiny basic
        PRINT,
        INPUT,
        CALL,
        LET,
        //===================//

        AUTO,
        LONG,
        SWITCH,
        BREAK,
        ENUM,
        REGISTER,
        TYPEDEF,

        CASE,
        EXTERN,
        RETURN,
        UNION,

        CHAR,
        FLOAT,
        SHORT,
        UNSIGNED,

        CONST,
        FOR,
        SIGNED,
        VOID,

        CONTINUE,
        GOTO,
        SIZEOF,
        VOLATILE,

        DEFAULT,
        IF,
        ELSE,
        STATIC,
        WHILE,

        DO,
        INT,
        STRUCT,

        DOUBLE,

        NEWLINE,
        UNDEFINED,
        eof
    };

    struct Token
    {
        std::string m_text = "";
        TokenType m_type = TokenType::UNDEFINED;
        size_t m_lineNumber = 0;
    };
}