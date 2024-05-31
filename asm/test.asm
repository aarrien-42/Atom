bits 64

section .data
    x dd 0

section .rodata
    newline db 0x0a
    msg_1 db "Odd", 0
    msg_2 db "Pair", 0
section .text
    global _start

print_digit: ; fd = %rdi, digit = %rsi
    mov rax, 1
    add rsi, '0'
    mov rdx, 1
    syscall
    ret

print_str: ; fd = %rdi, buff = %rsi, size = %rdx
    mov rax, 1
    syscall

    mov rax, 1
    mov rsi, newline
    mov rdx, 1
    syscall
    ret

_start:
    mov eax, 1
    mov [x], eax        ; v. x = 1
    start_while_loop_1:
        mov edx, 0
        mov eax, [x]
        mov ecx, 2
        div ecx ; divides eax by ecx, result = eax, reminder = edx

        mov eax, edx ; take the reminder
        cmp eax, 0

        jne if_1
        jmp else_1

        if_1:
            mov rdi, 1
            mov rsi, msg_1
            mov rdx, 3
            call print_str
            jmp end_if_1
        else_1:
            mov rdi, 1
            mov rsi, msg_2
            mov rdx, 4
            call print_str
            jmp end_if_1
        end_if_1:

        mov eax, [x] ; gets value stored on x
        inc eax
        mov [x], eax    ; x = x + 1

        mov rdi, 1
        mov rsi, 5
        call print_digit

        mov eax, [x] ; gets value stored on x
        cmp eax, 10
        jl start_while_loop_1
    end_while_loop_1:

    mov rax, 60
    mov rdi, 0
    syscall
