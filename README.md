# Pascal Mini Compiler
 

## Fichier

- lexical.h: analyseur lexical
- syntax.h: analyseur syntaxique 
- semantic.h: analyseur semantique .
- pcode_exporter.h:gestion de pcode 
- main.c: fichier Main contenant l'interpreteur .

## Grammaire

Grammaire modifiée :
# Pascal Mini Compiler

## Fichier

- lexical.h: analyseur lexical
- syntax.h: analyseur syntaxique
- semantic.h: analyseur semantique .
- pcode_exporter.h:gestion de pcode
- main.c: fichier Main contenant l'interpreteur .

## Grammaire


<PROGRAM> ::= "program" <ID> ";" <BLOCK> "."
<BLOCK> ::= [<CONSTANTS>] [<VARIABLES>] <INSTRUCTIONS>

<CONSTANTS> ::= "const" <ID> "=" (<INT> | <FLOAT>) ";" { <ID> "=" (<INT> | <FLOAT>) ";" } | ε
<VARIABLES> ::= "var" <VAR_DECL> ";" { "," <VAR_DECL> ";" } | ε
<VAR_DECL> ::= <ID> ":" <TYPE>

<TYPE> ::= "integer" | "float" | "array" "[" <INT> "]" "of" ("integer" | "float")

<INSTRUCTIONS> ::= "begin" <INSTRUCTION> { ";" <INSTRUCTION> } "end"
<INSTRUCTION> ::= <INSTRUCTIONS> | <ASSIGNMENT> | <IF> | <WHILE> | <WRITE> | <READ> | <REPEAT> | <FOR> | <CASE> | ε

<ASSIGNMENT> ::= <ID> ":=" <EXPRESSION>
<IF> ::= "if" <CONDITION> "then" <INSTRUCTION> [ "else" <INSTRUCTION> ]
<WHILE> ::= "while" <CONDITION> "do" <INSTRUCTION>
<WRITE> ::= "write" "(" <EXPRESSION> { "," <EXPRESSION> } ")"
<READ> ::= "read" "(" <ID> { "," <ID> } ")"
<CONDITION> ::= <EXPRESSION> <COMPARISON> <EXPRESSION>
<COMPARISON> ::= "=" | "<>" | "<" | ">" | "<=" | ">="

<EXPRESSION> ::= <TERM> { <ADDSUB_OP> <TERM> }
<TERM> ::= <FACTOR> { <MULDIV_OP> <FACTOR> }
<FACTOR> ::= <ID> | <INT> | <FLOAT> | "(" <EXPRESSION> ")"

<REPEAT> ::= "repeat" <INSTRUCTION> "until" <CONDITION>
<FOR> ::= "for" <ID> ":=" <INT> ("to" | "downto") <INT> "do" <INSTRUCTION>
<CASE> ::= "case" <ID> "of" <INT> ":" <INSTRUCTION> { <INT> ":" <INSTRUCTION> } [ "else" <INSTRUCTION> ] "end"

<ID> ::= <LETTER> { <LETTER> | <DIGIT> } [ "[" <INT> "]" ]
<INT> ::= <DIGIT>+
<FLOAT> ::= <INT> "." <INT>

<DIGIT> ::= "0" | "1" | ... | "9"
<LETTER> ::= "a" | ... | "z" | "A" | ... | "Z"

<ADDSUB_OP> ::= "+" | "-"
<MULDIV_OP> ::= "\*" | "/"
