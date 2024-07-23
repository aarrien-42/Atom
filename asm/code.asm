; VARIABLE MACROS:
%macro DEF_VAR 2 ; Example: x resq
    ; %1 is the variable name
    ; %2 is the size of the variable (e.g., byte, word, dword, qword)
    %1 resb %2
%endmacro

%macro LOAD_VAR 2 ; Example: mov rax, [x]
    ; %1 is the variable name
    ; %2 is the register to load into (e.g., rax, rbx)
    mov %2, [%1]
%endmacro

%macro MOD_VAR 3 ; Example: mov qword [x], 6
    ; %1 is the variable name
    ; %2 is the value to store (e.g., 6, 0xFF)
    ; %3 is the size of the variable (e.g., byte, word, dword, qword)
    mov %3 [%1], %2 ; Store value into the address pointed by RSI
%endmacro

; STRING MACROS
%macro DEF_STR 2
    ; %1 is the label for the string
    ; %2 is the string value
    %1 db %2, 0  ; Null-terminated string
%endmacro

%macro MOD_STR 2
    ; %1 is the address of the string
    ; %2 is the new value to store (e.g., 'A')
    mov rsi, %1   ; Load address of string into RSI
    mov byte [rsi], %2 ; Store new value at the address pointed by RSI
%endmacro

%macro PRINT_STR 2
    ; %1 is the address of the string
    ; %2 is the length of the string
    mov rax, 1          ; syscall number for sys_write
    mov rdi, 1          ; file descriptor 1 is stdout
    mov rsi, %1         ; address of the string
    mov rdx, %2         ; length of the string
    syscall             ; make the syscall
%endmacro

section .bss
    DEF_VAR x, 8
    DEF_VAR y, 8

section .data
    scaling_factor dd 65536
    DEF_STR msg, "Hello world"

section .text
    global _start

_start:
    ; Modify the reserved space
    MOD_VAR x, 10, qword
    MOD_VAR y, 3, qword

    MOD_STR msg+3, 'X'
    MOD_STR msg, 'X'
    PRINT_STR msg, 10

    LOAD_VAR x, rdi
    mov rax, 60
    syscall
