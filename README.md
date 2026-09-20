```

https://csh.rit.edu/~moffitt/docs/6502.html
https://6502.co.uk/lesson/memory-map

cizim yaparken kullandigim arac (ne kadar guzel biseysin sen o_o)
https://asciiflow.com/#/

sp = sp + 0x100

|---8---| |---8---| |---8---|
┌───────┐ ┌───────┐ ┌───────┐
│  ACC  │ │   X   │ │   Y   │
└───────┘ └───────┘ └───────┘
┌───────┐
│   F   │
└───────┘


$0000 ┌──────────────────┐
      │                  │
      │    Zero Page     │  $0000-$00FF
      │                  │
$00FF ├──────────────────┤
      │                  │
      │      Stack       │  $0100-$01FF
      │                  │
$01FF ├──────────────────┤
      │                  │
      │                  │
      │      RAM         │ 
      │                  │
      │                  │ 4000-7FFF  - Memory mapped I/O
$8000 ├──────────────────┤
      │                  │
      │                  │ ROM for programmer usage
      │                  │
      │                  │
      │                  │
$FFF9 ├──────────────────┤
      │ NMI low          │ $FFFA
      │ NMI high         │ $FFFB
      │ RESET low        │ $FFFC
      │ RESET high       │ $FFFD
      │ IRQ/BRK low      │ $FFFE
      │ IRQ/BRK high     │ $FFFF
      └──────────────────┘


Event	Vector			Maskable?	
-----------------------------------------------------------------------
NMI		$FFFA/$FFFB		No			Non-maskable interrupt
RESET	$FFFC/$FFFD		—			Start/reset the CPU
IRQ		$FFFE/$FFFF		Yes			Normal hardware interrupt
BRK			—			—			Software interrupt instruction
-----------------------------------------------------------------------



┌───────────────────────────────────────────────────────────────────────────────────────────────────┐ 
│            Adres Hatti                                                                            │ 
└───────┬───────────────────┬───────────────────┬────────────────┬──────────────────────────────────┘ 
        │                   │                   │                │                                    
        │                   │                   │                │                                    
 ┌──────┴───────┐    ┌──────┴───────┐    ┌──────┴─────┐   ┌──────┴──────┐                             
 │              │    │              │    │            │   │             │                             
 │   mos6502    │    │     RAM      │    │  Klavye    │   │   Disk      │                             
 │              │    │              │    │            │   │             │                             
 └────┬─┬───────┘    └──────┬───────┘    └────┬─┬─────┘   └────┬─┬──────┘                             
      │ │                   │                 │ │              │ │                                    
      │ │                   │                 │ │              │ │                                    
      │ │                   │                 │ │              │ │                                    
 ┌────┼─┴───────────────────┴─────────────────┼─┴──────────────┼─┴───────────────────────────────────┐
 │    │        Veri Hatti                     │                │                                     │
 └────┼───────────────────────────────────────┼────────────────┼─────────────────────────────────────┘
      │                                       │                │                                      
 ┌────┴───────────────────────────────────────┴────────────────┴─────────────────────────────────────┐
 │             Kesme Hatti                                                                           │
 └───────────────────────────────────────────────────────────────────────────────────────────────────┘
                                                                                                      
    ┌──────┐                ┌─┬─┬─┬─┬─┬─┬─┬─┐                                                         
    │  A   │ genel amacli   │N│V│-│B│D│I│Z│C│                                                         
    └──────┘                └┬┴┬┴─┴┬┴┬┴┬┴┬┴┬┘                                                         
    ┌──────┐                 │ │   │ │ │ │ └─────► Carry 1 = true                                     
    │  X   │ indeks          │ │   │ │ │ │                                                            
    └──────┘                 │ │   │ │ │ └───────► Zero 1 = result zero                               
    ┌──────┐                 │ │   │ │ │                                                              
    │  Y   │ indeks          │ │   │ │ └─────────► IRQ disable 1 = disable                            
    └──────┘                 │ │   │ │                                                                
    ┌──────┬──────┐          │ │   │ └───────────► Decimal mode 1 = true                              
    │ PCH  │ PCL  │ PC       │ │   │                                                                  
    └──────┴──────┘          │ │   └─────────────► BRK command 1 = BRK                                
    ┌──────┐                 │ │                                                                      
    │  S   │ Yigin           │ └─────────────────► Overflow 1 = true                                  
    └──────┘                 │                                                                        
                             └───────────────────► Negative 1 = neg                                   
                                                                                                      
       ┌────────────────┐                                                                             
       │  zero page     │                                                                             
       │                │                                                                             
       ├────────────────┤                                                                             
       │    yigin       │                                                                             
       ├────────────────┤                                                                             
  ┌───►│                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    │                │                                                                             
  │    ├────────────────┤                                                                             
  │    │ Kesme tablosu  │◄─────┐                                                                      
  │    │                │      │                                                                      
  │    │                │      │                                                                      
  │    │                │      │                                                                      
  │    │                │      │                                                                      
  │    ├────────────────┤      │                                                                      
  │    │NMI low         │      │                                                                      
  │    │NMI high        │      │                                                                      
  │    ├────────────────┤      │                                                                      
  │    │RESET low       │      │                                                                      
  └────┤RESET high      │      │                                                                      
       ├────────────────┤      │                                                                      
       │IRQ/BRK low     │      │                                                                      
       │IRQ/BRK high    ├──────┘                                                                      
       └────────────────┘                                                                             

C BNF

https://bnfplayground.pauliankline.com

Single digit and letter intervals are allowed. For instance, instead of writing: <e> ::= "1" | "2" | "3", you can write <e> ::= [1-3]
Basic EBNF is supported. Specifically:
"+" can be used to mean "one or more of the previous." For example: <e> ::= [a-z]+ can produce any non-zero length sequence of lower case letters.
"*" can be used to mean "zero or more of the previous."
"?" can be used to mean "zero or one occurances of the previous."
"(" ")" can be used to group elements. For example, <e> ::= ([1-9] [a-z])+ allows strings such as: 1a, 4f, 4g3f9d, etc.
Inside parentheticals, you may also indicate choice by "|". For example, <e> ::= ([1-9] | [a-z])+ allows strings such as: 2, 3553, 1ffvv2, ggg, etc.
Note: EBNF symbols must touch the element(s) they are grouping. valid:( [1-9]? | [a-z] )+ invalid: ( [1-9] || [a-z] ) +.

==========================================

v0.1

toplama,cikarma
       2 + 4 + 1
<program> ::= <ifade>
<ifade> ::= <toplama>
<toplama> ::= <sayi> ('+' | '-') <sayi>
<sayi> ::= [0-9]+
==========================================

v0.2
carpma,bolme

    2 + 4 + 1 * 5 / 2
<program> ::= <ifade>
<ifade> ::= <toplama>
<toplama> ::= <carpma> ('+' | '-') <carpma>
<carpma> ::= <sayi> ('*' | '/') <sayi>
<sayi> ::= [0-9]+

==========================================

v0.2
degiskenler

int a; 
<ifade> 
 <degisken>
  "int" <degisken_ismi> ";"
   <degisken_ismi> => a 
  
int a = 4;
<ifade> 
 <degisken>
  "int" <degisken_ismi> <atama>? ";"
    <degisken_ismi> => a
     <atama> "="
      <ifade>
       <islem>
        <carpma>


int a = 2 + 1;
int a = b;

<program> ::= <ifade>

<ifade> ::= <islem>
           | <degisken>

<degisken> ::= "int" <degisken_ismi> <atama>? ";"

<atama> ::= "=" <ifade>


<islem> ::= <carpma> (("+" | "-") <carpma>)*
<carpma> ::= <sayi> (("*" | "/") <sayi>)*

<sayi> ::= [0-9]+
<degisken_ismi> ::= [a-zA-Z_][a-zA-Z0-9_]*

```