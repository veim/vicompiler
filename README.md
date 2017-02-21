# vicompiler
Try to create my compiler, an intelligent one.  
A compiler can be splited into two parts: analysis & synthesis.  
Analysis part (front end) breaks up the source program into constituent pieces and imposes a grammatical structure on them, also collects information and store it in symbol table.  
Synthesis part (back end) constructs the desired target program from the intermediate representation and the information in the symbol table.   
<small>Reference to "Compliers: Principles, Techniques, and Tools"</small>  
## 1. Lexical Analysis
Parse character stream into token stream and create symbol tables.  
<token-name, attribute-value>  
### 1.1 Token   
<small>  
ID 			⇒ / * identifier * /  
SEMI 		⇒ ;  
COMMA 		⇒ ,  
INT 		⇒ / * integer * /  
BINARYOP 	⇒ / * binary operators * /  
UNARYOP 	⇒ / * unary operators * /  
LP 			⇒ (  
RP 			⇒ )  
LB 			⇒ [  
RB 			⇒ ]  
LC 			⇒ {  
RC 			⇒ }  
TYPE 		⇒ int  
STRUCT 		⇒ struct  
RETURN 		⇒ return  
IF 			⇒ if  
ELSE 		⇒ else  
BREAK 		⇒ break  
CONT 		⇒ continue  
FOR 		⇒ for  
</small>

## 2. Syntax Analysis
Parse token stream into syntax tree.

## 3. Semantic Analysis


## 4. Intermediate Code Generation

## 5. Run-time Environment
### Register
### Stack
### Heap

## Code Optimization

## Etc: preprocessor, assembler, linker, loader

<meta http-equiv="refresh" content="2">