# sasm reference manual

* [Opcodes](#Opcodes)
* [Labels](#Labels)
* [Comments](#Comments)
* [Examples](#Examples)

-----

## Opcodes
Opcode|Mneumonic|Arguments
:------:|:---------:|:---:
0|[NOP](#NOP)|	0
1|[HALT](#HALT)|	0
2|[PUSH](#PUSH)|	1
3|[POP](#POP)|	0
4|[NEG](#NEG)|	0
5|[ADD](#ADD)|	0
6|[SUB](#SUB)|	0
7|[MUL](#MUL)|	0
8|[DIV](#DIV)|	0
9|[AND](#AND)|	0
10|[OR](#OR)|	0
11|[XOR](#XOR)|	0
12|[NOT](#NOT)|	0
13|[GT](#GT)|	0
14|[GE](#GE)|	0
15|[LT](#LT)|	0
16|[LE](#LE)|	0
17|[EQ](#EQ)|	0
18|[JMP](#JMP)|	1
19|[JIF](#JIF)|	1
20|[CALL](#CALL)|1
21|[RET](#RET)|	1
22|[LOAD](#LOAD)|1
23|[STORE](#STORE)|1

### NOP
	NOP
No operation
### HALT
	HALT
Stops the program execution
### PUSH
	PUSH <signed int>
Pushes a value to the top of the stack
### POP
	POP
Removes the top element from stack
### NEG
	NEG
Replaces the top element with its sign inverted.
### ADD
	ADD
Removes the top two elements and pushes their sum at the top.
### SUB
	SUB
Removes the top two elements and pushes their `difference` at the top.\
The top element is subtracted from the second top element.
### MUL
	MUL
Removes the top two elements and pushes their `product` at the top.
### DIV
	DIV
Removes the top two elements and pushes their `integer quotient` at the top.\
The top element is divided from the second top element.
### AND
	AND
Removes the top two elements and pushes their `bitwise and` at the top.
### OR
	OR
Removes the top two elements and pushes their `bitwise or` at the top.
### XOR
	XOR
Removes the top two elements and pushes their `bitwise xor` at the top.
### NOT
	NOT
Replaces the top element with its `1's complement`.
### GT
	GT
Removes the top two elements.\
Pushes 1 if secondTop `>` top element.\
Pushes 0 if otherwise.	
### GE
	GE
Removes the top two elements.\
Pushes 1 if secondTop `>=` top element.\
Pushes 0 if otherwise.	
### LT
	LT
Removes the top two elements.\
Pushes 1 if secondTop `<` top element.\
Pushes 0 if otherwise.	
### LE
	LE
Removes the top two elements.\
Pushes 1 if secondTop `<=` top element.\
Pushes 0 if otherwise.
### EQ
	EQ
Removes the top two elements.\
Pushes 1 if secondTop `equals` top element.\
Pushes 0 if otherwise.

### JMP
	JMP <label>
Unconditionally jumps to the address specified by label.
### JIF
	JIF <label>
Removes the top element.\
Jumps to the address specified by label only if the popped element didn't equal to 0.
### CALL
	CALL <label>
 Saves the next program address and jumps to the address specified by label.\
 Also creates a new storage for local variables.
### RET
	RET
Jumps to the address saved by the call instruction.\
Also removes the variable store and local variables are deleted.
### LOAD
	LOAD <index>
Gets a value from the local variable store specified by the index and pushes it onto the stack.
### STORE
	STORE <index>
Pops the top element and saves it into the local variable store specified by the index.

----

## Labels
	label_name:
Marks the beginning of a  code segment.\
Can be used by CALL, JMP and JIF instruction for jumps.
## Comments
	// Comment goes here
Single line comments begin with `//` till the line end.\
Everything in between is ignored by the assembler.
## Examples