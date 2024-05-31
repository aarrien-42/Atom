# [Atom] - Intuitive and Simple Programming

The goal of this project is to develop my own programming language. It is a very ambitious and costly project, so initially, it will start as a simple compiler and will grow from there. I don't intend for it to be a complex and deep language, its purpose is rather educational.

## Key Features
- Shortened keywords: <details><summary>Keyword List</summary>

    | C++ | if | else | if else | while | for | return | continue | break | any variable | write |
    | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
    | Atom | i. | e. | ie. | w. | f. | r. | c. | b. | v. | p. |

</details>

- New Function declarations. `main:` or using parameters `f_name: v. p1, v. p2`
- Simplyfied conditionals. It's posible to concatenate various conditions to a single variable. `(5 <= x > 1)` or even `(x <= 5 > 1 != 2)`

- Still working on them


## File Structure
 - Project Directory
    - `inc/`             # Header files (.hpp)
    - `src/`             # Source files (.cpp)
    - `obj/`             # Object files (.o)
    - `asm/`             # Assembly code files (.asm)
    - `bin/`             # Binaries (executable for getting assembly code and the final executable)
    - `lang/`            # Own language files (.atm)

## How to use
`make run lang/<file>.atm` *(Compiles files and Writes a valid assembly code)*

`make asm` *(Compiles the assembly code)*

## Theory
Programming languages can be either interpreted or compiled. Interpreted languages are executed line by line, while compiled languages, as the name suggests, directly translate the source code into machine code.

Mine is meant to be compiled, so it requires a few more steps before executing. Here's a summary of the process:

1. Lexical Analysis:
    - **Task**: Implement a lexer to break down the source code into tokens.
    - **Outcome**: A stream of tokens representing the source code.
2. Syntax Analysis (Parsing):
    - **Task**: Develop a parser to check if the arrangement of tokens follows the defined syntax rules.
    - **Outcome**: An Abstract Syntax Tree (AST) representing the structure of the source code.
3. Semantic Analysis:
    - **Task**: Implement a semantic analyzer to check the meaning of the code.
    - **Outcome**: A semantically validated AST with type information and resolved symbols.
4. Code Generation:
    - **Task**: Generate the target code (assembly language or another intermediate code).
    - **Outcome**: Target code suitable for further processing or execution.

## To do list
- [ ] Implement a lexer to break down the source code into tokens:
    - [x] Detect and save basic tokens for general purpouse
    - [x] Save each token position in the code
    - [x] Enable a way to set comments inside the actual code
    - [ ] Implement a character that allows continuing a line on the next line, facilitating multi-line code writing
    - [ ] End of line character support, as ';' in C
    - [ ] Add the posibility for unitary operations (increment, decrement, etc.)
- [ ] Develop a parser to check if the arrangement of tokens follows the defined syntax rules:
    - [x] Make defined nodes for each situation posible
    - [x] Develop an easy way to visualize the resulting AST tree
    - [ ] Make sure it correctly saves every conditional structure:
        - [ ] If statement
        - [ ] While loop
        - [ ] For loop
    - [x] Manage the parenthesis between operations or comparations correctly
    - [ ] Enable concatenation of conditions (ex.: (x < 100 && > 50))
    - [ ] Suport for multiple file compilation
    - [ ] Error management correctly shown and without any crashes
- [x] Multiple file compilation
- [ ] Generate the target code in assembly:
    - [ ] Code generator class
    - [ ] Generate code for every node:
        - [ ] Function nodes
        - [ ] Conditional nodes
        - [ ] Operation nodes
        - [ ] Variable nodes
        - [ ] Return node
- [ ] Final executable:
    - [ ] Compile the assembly code and generate a single executable
    - [ ] Add a flag system for little settings as customizing executable name

## How to Contribute
At this stage, the development is purely personal.

## Additional Resources
- **Compiler related:**
    - [Pixeled - Creating a Compiler](https://www.youtube.com/watch?v=vcSijrRsrY0&list=PLUDlas_Zy_qC7c5tCgTMYq2idyyT241qs)
    - [freeCodeCamp - I wrote a programming language. Here’s how you can, too.](https://www.freecodecamp.org/news/the-programming-language-pipeline-91d3f449c919/)
    - [Medium - How to Build Your Own Programming Language — Introduction](https://ruslandzhafarov.medium.com/how-to-create-your-own-programming-language-introduction-7c848585c59)
- **Assembly language realted:**
    - [RChapman Blog - Linux system call table for x86 64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
    - [University of Alaska Fairbanks - x86_64 NASM Assembly Quick Reference](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html)
    - [Aldeid - Architecture/x86-assembly](https://www.aldeid.com/wiki/Category:Architecture/x86-assembly)
