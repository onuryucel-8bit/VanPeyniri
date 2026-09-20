```mermaid

---
config:
  theme: base
  themeVariables:
    primaryColor: "#816b6b"
    primaryTextColor: "#610d0d"
    primaryBorderColor: "#571111"
    lineColor: "#5d611f"

    secondaryColor: "#533434"
    secondaryTextColor: "#070101"
    secondaryBorderColor: "#533131"

    tertiaryColor: "#9b3434"
    tertiaryTextColor: "#641f1f"
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
    ================================================================================
    ================================================================================
    ================================================================================
    */

    func_call_stmt = identifier "(" args* ")";

    args ::= expr ( ',' expr )*;

    expr = or_logical;

    or_logical = and_logical | ("||")* ;

    and_logical = equality ("&&" equality)*;

    equality = comparison (("!=" | "==") comparison)*;

    comparison = addition ( ( ">" | ">=" | '<' | "<=" ) addition )*;

    addition = multiplication ( ( '+' | '-' ) multiplication )*;

    multiplication
         = modulo ( ( '*' | '/' ) modulo )*;

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
    

    



    
```


markdown.preview.scrollPreviewWithEditorSelection