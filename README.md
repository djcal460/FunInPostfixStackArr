# FunInPostfixArrStack

### Interactive Infix to Postfix Conversion Using an Array Stack

FunInPostfixArrStack was developed in c language to demonstrate how to convert a commonly seen infix mathmatical problem to postfix. Useful because rather than scanning infix, compilers usually convert these types of problems automagically behind the scenes. It's quite simple, the infix gets scanned from left to right. During scan, operands get sent to the postfix string, operators get pushed to the stack and are popped to postfix depending on their precedence. If scan comes across an operator with higher or equal precedence than the one at the top of the stack, then the stack is popped and the popped operator is saved to the postfix string. 

- Choose from 10 postfix equations
- Get the converstion from infix to postfix
- Get the solution using postfix computation

# Features!

Array Stacks! Stacks! Sta-Sta-Sta-Stacks! If you'd like to see how this is done using linked lists, look into my other repositories.

### Tech

Tech uses the very very very advanced terminal shell and gcc compiler.

### Installation

The program comes with a swanky Makefile for you to automagically compile the .c extensions into .o binaries. Exciting? Make the file and run the file in bash.

### Run the File
```sh
$ gcc -o funinpostfixarrstack funinpostfixarrstack.c 
```

### To Do
Add conversion for larger numbers
