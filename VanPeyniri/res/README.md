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



    program = stmts; 
    
    stmts  =  stmt+;

    stmt =  
        expr
        |var_stmt 
        | if_stmt
        | for_stmt
        | switch_stmt
        | func_declare_stmt            
        | func_call_stmt
        | while_stmt;
    /*
    var_stmt
    ================================================================================
    ================================================================================
    ================================================================================
    */

    var_stmt = data_types identifier ("=" expr)? ";";

    /*
    if_stmt
    ================================================================================
    ================================================================================
    ================================================================================
    */

    if_stmt  = 'if' '(' expr ')' '{' stmts '}'
        ( 'else' 'if' '(' expr ')' '{' stmts '}')*
        ( 'else' '{' stmts '}')? ;

    /*
    for_stmt
    ================================================================================
    ================================================================================
    ================================================================================
    */

    for_stmt = 'for' '('assign ';' ')' '{' stmts '}';

    /*
    switch_stmt
    ================================================================================
    ================================================================================
    ================================================================================
    */

    switch_stmt = switch '('')' '{' case ':' break ';' '}';

    /*
    ================================================================================
    ================================================================================
    ================================================================================
    */

    func_call_stmt = identifier "(" args* ")";

    args ::= expr ( ',' expr )*;


    /*
    ================================================================================
    ================================================================================
    ================================================================================
    */

    expr = or_logical;

    or_logical = and_logical | ("||")* ;

    and_logical = equality ("&&" equality)*;

    equality = comparison (("!=" | "==") comparison)*;

    comparison = addition ( ( ">" | ">=" | '<' | "<=" ) addition )*;

    addition = multiplication ( ( '+' | '-' ) multiplication )*;

    multiplication = modulo ( ( '*' | '/' ) modulo )*;

    modulo = unary ( '%' unary )*;

    unary    = ( '!' | '-' | '+' )* exponent;

    exponent ::= primary ( '^^' exponent )*;

    primary = literal
           | grouping
           | funccall
           | identifier;

        literal  ::=
                integer
            | float
            | string;

            integer  ::= digit+;

            float  ::= integer? '.' integer;

        grouping ::= '(' expr ')';

        identifier ::= alpha alnum*;

            alnum ::= alpha | digit;

            alpha    ::= (A-Z) | (a-z) | '_' ;

    /*
    ================================================================================
    ===================Temel Seyler=================================================
    ================================================================================
    */
    data_types = (unsigned | signed)?
        ("int"
        |"char"
        |"void"
        |"short"        
        |"float"
        |"double"
        |"long");

    
```

https://pinky-lang.org/grammar.html
https://en.cppreference.com/c/language/operator_precedence
markdown.preview.scrollPreviewWithEditorSelection