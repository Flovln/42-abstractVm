# abstractVm

Ecole 42 project

## Goal

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions. These arithmetic expressions are provided to the machine as basic assembly programs and saved as a stack like structure.

## Lexical rules

AbstractVM’s assembly language has a limited type system:

	- One instruction per line.
	- Comments start with a ’;’ and finish with a newline. A comment can be either at the start of a line, or after an instruction.
	- There are 11 commands to handle: push, pop, dump, assert, add, sub, mul, div, mod, print and exit.
	- Push and Assert are the 2 commands taking a value as parameter.
	- There are 5 values to handle: int8, int16, int32, double and float.
	- Whitespaces handling before, after and between commands.
	- Can read from a file.
	- Can read from the standard input.

## Commands

  - push v: pushes a new value on the top of the stack.
  - pop: pop the first element of the stack.
  - dump: display all the values of the stack without changing its order.
  - print: if value is a int8 prints it as a char, if that's not the case.
  - assert v: Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction..
  - add: Unstacks the first two values on the stack, adds them together and stacks the result.
  - sub: Unstacks the first two values on the stack, subtracts them, then stacks the result.
  - mul: Unstacks the first two values on the stack, multiplies them, then stacks the result.
  - div: Unstacks the first two values on the stack, divide them, then stacks the result.
  - mod: Unstacks the first two values on the stack, calculates the modulus, then stacks the result.
  - exit: Terminate the execution of the current program.

## Execution

  -  When a computation involves two operands of different types, the value returned has the type of the more precise operand.

## Errors

  - Overflow and underflow on values.
  - Overflow and underflow on results.
  - Division/Modulo by 0.
  - The stack is empty when calling an instruction manipulating the stack, the program execution stops with an error.
  - The stack is composed of strictly less that two values when an arithmetic instruction is executed.
  - The exit instruction does not appears while all others instruction has been processed, the execution stops.

## Usage

In your terminal:

```sh

  - $> make && make clean
  - $> ./avm || ./avm [filepath]

```
