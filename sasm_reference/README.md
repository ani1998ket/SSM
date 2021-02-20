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

----

## Comments
	// Comment goes here
Single line comments begin with `//` till the line end.\
Everything in between is ignored by the assembler.

----

## Examples

### Arithmetic

	PUSH 3
	PUSH 2
	SUB
	HALT
	
Explanation :
	
	// Stack : []
	
	PUSH 3
	// Stack : [3]
	
	PUSH 2 
	// Stack : [3 2]
	
	SUB 
	// Stack : [1]
	
	HALT
	// End of program

### Unconditional Jump
	
	main:
		PUSH 1		// Stack : [1]
		JMP label	
		PUSH 2		// this won't execute
		
	label:
		PUSH 3		// Stack : [1 3]
		HALT
	
### Branching

	main:
		PUSH 1
		PUSH 2
		
		LT				// Stack : [ 1 ] ( since 1 < 2  is true )
		JIF is_less		// Condition is true. Jump will occur
		
		PUSH 0			// This won't execute
		HALT
	
	is_less:
		PUSH 1			// This will execute
		HALT

PseudoCode

	if( 1 < 2 ):
		push(1)
	else:
		push(0)
	
	
### Variables
	main:
		PUSH 10
		STORE 0		// x = 10
	
		PUSH 20
		STORE 1		// y = 20
		
		LOAD 0		// Stack : [ 10 ]
		LOAD 0		// Stack : [ 10 10 ]
		MUL			// Stack : [ 100 ]

		LOAD 1		// Stack : [ 100 20]
		LOAD 1		// Stack : [ 100 20 20 ]
		MUL			// Stack : [ 100 400]
		
		ADD			// Stack : [ 500 ]
		STORE 2		//  z = 500
		
		HALT		// Stack : []
Pseudo Code:

	x = 10
	y = 20
	z = (x*x) + (y*y)
	
### Loops
	// Computing 1 + 2 + 3 + 4 + 5 
	main:
		PUSH 5
		STORE 0		// n = 5
		
		PUSH 0
		STORE 1 	// sum = 0
		
	body:
		LOAD 0
		PUSH 0
		LE			// n <= 0
		JIF end		// if( n <= 0 ) jump( end )

		LOAD 0
		LOAD 1
		ADD
		STORE 1		// sum = sum + n

		LOAD 0
		PUSH 1
		SUB
		STORE 0		// n = n - 1
		JMP body
		
	end:
		LOAD 1 		// Stack : [15]
		HALT

Pseudo Code:

	n = 5
	sum = 0
	while( n >= 0 ):
		sum = sum + n
		n = n - 1
	
### Function Calls
	
	main:
		PUSH 3
		CALL cube	// cube(3)
		HALT
		
	cube:
		STORE 0		// x = 3

		LOAD 0
		LOAD 0
		LOAD 0		// Stack : [ 3 3 3 ]
		MUL			// Stack : [3 9]
		MUL			// Stack : [27]
		
		RET

Pseudo Code:
	
	function cube(x):
		return x * x * x

	cube(3)
