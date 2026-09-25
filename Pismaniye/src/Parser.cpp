#include "Parser.h"


namespace baz
{
    Parser::Parser(fs::path path)
        :m_lexer(path)
    {
        m_peekToken = m_lexer.getToken();
        nextToken();      

        m_file.open(cmake_PROJECT_RES "outAsm.asm");
        
        if (!m_file.is_open())
        {
            std::cout << "hata outASM acilamadi \n";
        }

        //outputAsm("org 100h");
    }

    Parser::~Parser()
    {
        //outputAsm("jmp $");
        //outputAsm("ret");
        //m_file.close();
    }
    
    //program ::= stmt;
    void Parser::run()
    {
        while (m_currentToken.m_type != baz::TokenType::eof)
        {            
            stmt();
            //nextToken();
        }
    }

    bool Parser::matchPeek(TokenType tokenType)
    {
        return m_peekToken.m_type == tokenType;
    }

    bool Parser::matchCurrent(TokenType tokenType)
    {
        return m_currentToken.m_type == tokenType;
    }

    void Parser::outputAsm(std::string str)
    {
        m_file << str << "\n";
    }

    void Parser::printCurrentToken()
    {
        for (size_t i = 0; i < m_tabCounter; i++)
        {
            std::cout << " ";
        }

        std::cout << m_currentToken.m_text << "[" << magic_enum::enum_name(m_currentToken.m_type) << "]\n";
    }

    void Parser::nextToken()
    {
        m_currentToken = m_peekToken;
        m_peekToken = m_lexer.getToken();
    }


    /*
    program ::= stmt

    stmt ::= statements++
    
    statements ::= print_stmt
                | if_stmt 
                | input_stmt
                | let_stmt
                | goto_stmt
                | assignment_stmt                
                ;

    print_stmt = "PRINT" (string | identifier)  ;

    if_stmt = "IF" expression relational_op expression " THEN " statement ("END" |("ELSE" statement "END"));

    input_stmt = "INPUT" identifier;

    let_stmt = "LET" identifier "=" factor;
    
    goto_stmt = "GOTO" label; 

    assignment_stmt = identifier "=" expression ;

    expression ::= term (("+" | "-") term)*;

    term ::= factor (("*" | "/") factor)*;

    factor ::= identifier | number;

    relational_op ::= 'kucuktur' | "kucuk esittir" | ">" | ">=" | "==" | "!=";

    identifier ::= char;
    number ::= digit digit*;
    string ::= "'" (char | digit) "'";

    digit ::= "0" | "1" | "2" | "..";

    char ::= "[A-Z] _ [a-z]";
    */

    //stmt ::= statements+ ;
    void Parser::stmt()
    {
        statements();       
    }
     
  
    /*
    statements :: = print_stmt
        | if_stmt
        | input_stmt
        | let_stmt
        | goto_stmt
        | assignment_statement         
        ;
    */
    void Parser::statements()
    {
       switch (m_currentToken.m_type)
       {
       case baz::TokenType::PRINT:
           print_stmt();
           break;

       case baz::TokenType::IF:
           if_stmt();
           break;

       case baz::TokenType::INPUT:
           input_stmt();
           break;

       case baz::TokenType::LET:
           let_stmt();
           break;

       case baz::TokenType::GOTO:
           goto_stmt();
           break;

       /*case baz::TokenType::CALL:
           func_call_stmt();
           break;*/

       case baz::TokenType::IDENTIFIER:
        
           if (m_peekToken.m_type == baz::TokenType::LPAREN) 
           {
               //func_decl_stmt();
           }
           else
           {
               assignment_stmt();
           }
           break;

       default:
           printCurrentToken();
           printError("tanimsiz paket var burda");
           nextToken();
           break;
       }
    }

    //print_stmt = "PRINT" (string | identifier )  ;
    void Parser::print_stmt()
    {

        nextToken();

        //currentToken = str | id
        if (m_currentToken.m_type != baz::TokenType::STRING_LITERAL
            && m_currentToken.m_type != baz::TokenType::IDENTIFIER)
        {
            printError(std::format("hata var print \"abc\" veya print var print(string | expression), peekToken.type => : {}", magic_enum::enum_name(m_peekToken.m_type)));
            return;
        }
       
        switch (m_currentToken.m_type)
        {
        case baz::TokenType::STRING_LITERAL:
            /*
            outputAsm(
                "mov ah, 0x0e\n"
                "mov al, '" + m_currentToken.m_text + "'\n"
                "int 0x10\n");
            */

            std::cout << m_currentToken.m_text << "\n";
            break;

        case baz::TokenType::IDENTIFIER:
        {
            std::optional<uint8_t> idval = m_memoryManager.getValue(m_currentToken.m_text);

            if (idval.has_value())
            {
                std::cout << "print calisiyor:"
                          << static_cast<int>(idval.value()) << "\n";
            }
            else
            {
                printError("ulan print icindeki degiskenin degeri falan yok");
            }
        }
            break;

        }

        nextToken();
    }

    //if_stmt = "IF" "(" expression relational_op expression ")" "{" statement "}";
    void Parser::if_stmt()
    {
        printCurrentToken();

        //currentToken => (
        nextToken();

        if (!matchCurrent(baz::TokenType::LPAREN))
        {
            printError("( parantezi unuttun");
        }

        //currentToken => expression
        nextToken();
        expression();

        //currentToken => relational_op
        relational_op();

        //currentToken => expression
        nextToken();
        expression();       

        printCurrentToken();        
        //currentToken => )
        if (!matchCurrent(baz::TokenType::RPAREN))
        {
            printError(") parantezi unuttun");
        }

        //currentToken => {
        nextToken();
        if (!matchCurrent(baz::TokenType::LBRACKET))
        {
            printError("{ parantezi unuttun");
        }
        printCurrentToken();

        //currentToken => stmt (if block)
        nextToken();
        
        m_tabCounter+= 5;
        while (!matchCurrent(baz::TokenType::RBRACKET) && !matchCurrent(baz::TokenType::eof)) 
        {
            stmt();
        }
        
        m_tabCounter -= 5;
        if (!matchCurrent(baz::TokenType::RBRACKET))
        {
            printError("} parantezi unuttun");
        }
        else
        {
            printCurrentToken();
            
            nextToken();
        }

        
    }

    //input_stmt = "INPUT" identifier;
    void Parser::input_stmt()
    {
        nextToken();

        if (!matchCurrent(IDENTIFIER))
        {
            printError("input id degisken nerede...?");
        }

        std::cout << "INPUT id [" << m_currentToken.m_text << "]\n";

        nextToken();
    }

    // let_stmt = "LET" identifier "=" factor;
    void Parser::let_stmt()
    {
        
        //currentToken => LET
        nextToken();
        //currentToken => id        

        baz::Token id;

        if (!matchCurrent(baz::TokenType::IDENTIFIER))
        {
            printError("degisken ismini unuttun");
            return;
        }
        else if(matchCurrent(baz::TokenType::IDENTIFIER))
        {
            //degisken ismini kenara kaydet
            id = m_currentToken;
            //eger degisken ise tabloda yer olustur
            m_memoryManager.createVariable(m_currentToken.m_text, VarSize::Char);
        }

        //print id
        printCurrentToken();                


        nextToken();
        //currentToken => =
        if (!matchCurrent(baz::TokenType::ASSIGN))
        {
            printError("= eksik");
        }
         
            

        nextToken();
        //currentToken => factor

        //TODO LET a = b ihtimali eksik
        
        //ornek LET a = 5
        //("a", 5)
                
        m_memoryManager.setValue(id.m_text, std::stoi(factor().m_text));        
    }

    //goto_stmt = "GOTO" expression;
    void Parser::goto_stmt()
    {
        //if (!matchPeek(EXpression))
        {
            printError("");
        }
    }

    //assignment_stmt = identifier "=" expression ;
    void Parser::assignment_stmt()
    {
        //TODO id tabloda varmi ?
        identifier();

        //currentToken => '='
        nextToken();
        if (!matchCurrent(baz::TokenType::ASSIGN))
        {
            printError("= eksik");
        }

        nextToken();
        expression();

    }

    //expression ::= term (("+" | "-") term)*;
    baz::Token Parser::expression()
    {
        term();

        if (matchCurrent(baz::TokenType::PLUS) || matchCurrent(baz::TokenType::MINUS))
        {
            baz::TokenType op = m_currentToken.m_type;

            nextToken();

            switch (op)
            {
            case baz::TokenType::PLUS:
                printCurrentToken();
                break;

            case baz::TokenType::MINUS:
                printCurrentToken();
                break;
            }

            factor();
        }

        return m_currentToken;
    }

    //term :: = factor(("*" | "/") factor)*;
    baz::Token Parser::term()
    {
        factor();

        if (matchCurrent(baz::TokenType::ASTERISK) || matchCurrent(baz::TokenType::SLASH))
        {            
            baz::TokenType op = m_currentToken.m_type;

            nextToken();

            switch (op)
            {
            case baz::TokenType::ASTERISK:
                printCurrentToken();
                break;

            case baz::TokenType::SLASH:
                printCurrentToken();
                break;
            }
           
            factor();
        }

        return m_currentToken;
    }

    //TODO optionel ??
    //factor :: = identifier | number;
    baz::Token Parser::factor()
    {
        baz::Token retval = m_currentToken;

        switch(m_currentToken.m_type)
        {
            case baz::TokenType::NUMBER_INT:
                printCurrentToken();
                break;

            case baz::TokenType::IDENTIFIER:
                //std::cout <<"id["<< m_currentToken.m_text << "]\n";
                identifier();                
                break;

            default:
                printError("factor() hata");
                break;
        }

        nextToken();

        return retval;
    }

    //identifier
    void Parser::identifier()
    {
        //std::cout << "id[" << m_currentToken.m_text << "] = ";

        printCurrentToken();
               
        //tabloda varmi?
            //evet imleci gonder
        //hayir
            //hata ver
    }

    void Parser::relational_op()
    {
        /*
        LESS_THAN,          // <
        GREATER_THAN,       // >
        NOT_EQUAL,          // !=
        EQUAL_EQUAL,        // ==
        EQUAL_LESS,         // <=
        EQUAL_GREATER,      // >=
        */
        if (!matchCurrent(baz::TokenType::LESS_THAN) 
            && !matchCurrent(baz::TokenType::GREATER_THAN)
            && !matchCurrent(baz::TokenType::NOT_EQUAL)
            && !matchCurrent(baz::TokenType::EQUAL_EQUAL)
            && !matchCurrent(baz::TokenType::EQUAL_LESS)
            && !matchCurrent(baz::TokenType::EQUAL_GREATER))
        {
            printError("hmm < <= > >= != sunlardan biri eksik");
        }

        printCurrentToken();        
    }

    void Parser::printError(std::string message)
    {
        std::cout << "HATA :: " << message << "\n";
    }
    
}