```mermaid

---
config:
  theme: base
  themeVariables:
    primaryColor: "#816b6b"
    primaryTextColor: "#5f1212"
    primaryBorderColor: "#571111"
    lineColor: "#5d611f"

    secondaryColor: "#fff5f5"
    secondaryTextColor: "#0e0405"
    secondaryBorderColor: "#533131"

    tertiaryColor: "#c4afaf"
    tertiaryTextColor: "#8b8080"
    tertiaryBorderColor: "#5a0101"
---

railroad-ebnf-beta

    /*
    TINY BASIC
    https://github.com/SamHammersley/Tiny-BASIC-Compiler/blob/master/tiny_basic_grammar.ebnf

    https://en.wikipedia.org/wiki/Tiny_BASIC
    */

    program ::= stmt;
    stmt ::= statements+ ;

    statements ::= print_stmt
                | if_stmt 
                | input_stmt
                | let_stmt
                | goto_stmt
                | assignment_statement| func_decl_stmt
                | func_call_stmt
                ;

    print_stmt = "PRINT" (string | expression)  ;

    if_stmt = "IF" expression relational_op expression " THEN " statement ("END" |("ELSE" statement "END"));

    input_stmt = "INPUT" identifier;

    let_stmt = "LET" identifier "=" expression;
    
    goto_stmt = "GOTO" expression;

    func_call_stmt = "CALL " expression;    

    assignment_statement = identifier "=" expression ;

    func_decl_stmt = identifier "(" ")"expression "RETURN";

    expression ::= term (("+" | "-") term)*;

    term ::= factor (("*" | "/") factor)*;

    factor ::= identifier | number | "(" expression ")";

    relational_op ::= 'kucuktur' | "kucuk esittir" | ">" | ">=" | "==" | "!=";

    identifier ::= char;
    number ::= digit digit*;
    string ::= "'" (char | digit) "'";

    digit ::= "0" | "1" | "2" | "..";

    char ::= "[A-Z] _ [a-z]";
    
    
    
```