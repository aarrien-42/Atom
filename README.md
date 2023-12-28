# [Atom] - Intuitive and Simple Programming

The goal of this project is to develop my own programming language. It is a very ambitious and costly project, so initially, it will start as a simple compiler and will grow from there. I don't intend for it to be a complex and deep language, its purpose is rather educational.

## Key Features
- Still working on them

## File Structure
 - Project Directory
    - inc/             # Header files (.hpp)
    - src/             # Source files (.cpp)
    - obj/             # Object files (.o)
    - asm/             # Assembly code files (.s)
    - bin/             # Binaries (executable for getting assembly code and the final executable)
    - lang/            # Own language files (.atm)

## How to use
make run lang/<file>.atm *(Compiles files and Writes a valid assembly code)*

## Theory
Programming languages can be either interpreted or compiled. Interpreted languages are executed line by line, while compiled languages, as the name suggests, directly translate the source code into machine code.

Mine is meant to be compiled, so it requires a few more steps before executing. Here's a summary of the process:
- Lexical Analysis - Splits the source code into tokens, resulting in a token list.
- Parsing
- Semantic Analysis
- Optimization
- Code Generation

## How to Contribute
At this stage, the development is purely personal.

## Additional Resources
- [Pixeled - Creating a Compiler](https://www.youtube.com/watch?v=vcSijrRsrY0&list=PLUDlas_Zy_qC7c5tCgTMYq2idyyT241qs)
- [freeCodeCamp - I wrote a programming language. Here’s how you can, too.](https://www.freecodecamp.org/news/the-programming-language-pipeline-91d3f449c919/)
- [Medium - How to Build Your Own Programming Language — Introduction](https://ruslandzhafarov.medium.com/how-to-create-your-own-programming-language-introduction-7c848585c59)
