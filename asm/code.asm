section .data
    newline db 0xA        ; Newline character

section .text
    global _start

_start:
    mov eax, 1            ; Initialize counter to 1

print_loop:
    cmp eax, 101          ; Compare counter with 101 (loop until 100)
    jge exit_program      ; If counter >= 101, exit the program

    mov ebx, eax          ; Move the current number to ebx for comparison

    ; Check if the number is divisible by 3 and 5 (FizzBuzz)
    mov edx, 0            ; Clear edx to check divisibility
    mov eax, ebx
    mov ecx, 15           ; Divisor for 3 and 5
    div ecx
    cmp edx, 0
    je fizzbuzz

    ; Check if the number is divisible by 3 (Fizz)
    mov eax, ebx
    mov ecx, 3            ; Divisor for 3
    xor edx, edx          ; Clear edx to check divisibility
    div ecx
    cmp edx, 0
    je fizz

    ; Check if the number is divisible by 5 (Buzz)
    mov eax, ebx
    mov ecx, 5            ; Divisor for 5
    xor edx, edx          ; Clear edx to check divisibility
    div ecx
    cmp edx, 0
    je buzz

    ; Print the number
    mov eax, 4            ; Syscall number for sys_write
    mov ebx, 1            ; File descriptor: STDOUT
    mov ecx, ebx          ; Buffer address (pointer to the number)
    mov edx, 1            ; Buffer size (length of the number)
    int 0x80              ; Invoke sys_write syscall
    jmp next_iteration    ; Jump to the next iteration

fizz:
    mov eax, 4            ; Syscall number for sys_write
    mov ebx, 1            ; File descriptor: STDOUT
    mov ecx, fizz_msg     ; Buffer address (pointer to "Fizz")
    mov edx, 4            ; Buffer size (length of "Fizz")
    int 0x80              ; Invoke sys_write syscall
    jmp next_iteration    ; Jump to the next iteration

buzz:
    mov eax, 4            ; Syscall number for sys_write
    mov ebx, 1            ; File descriptor: STDOUT
    mov ecx, buzz_msg     ; Buffer address (pointer to "Buzz")
    mov edx, 4            ; Buffer size (length of "Buzz")
    int 0x80              ; Invoke sys_write syscall
    jmp next_iteration    ; Jump to the next iteration

fizzbuzz:
    mov eax, 4            ; Syscall number for sys_write
    mov ebx, 1            ; File descriptor: STDOUT
    mov ecx, fizzbuzz_msg ; Buffer address (pointer to "FizzBuzz")
    mov edx, 8            ; Buffer size (length of "FizzBuzz")
    int 0x80              ; Invoke sys_write syscall
    jmp next_iteration    ; Jump to the next iteration

next_iteration:
    ; Print newline character
    mov eax, 4            ; Syscall number for sys_write
    mov ebx, 1            ; File descriptor: STDOUT
    mov ecx, newline      ; Buffer address (pointer to newline character)
    mov edx, 1            ; Buffer size (length of newline character)
    int 0x80              ; Invoke sys_write syscall

    ; Increment counter
    inc dword [eax]

    ; Continue the loop
    jmp print_loop

exit_program:
    ; Exit the program
    mov eax, 1            ; Syscall number for sys_exit
    xor ebx, ebx          ; Exit code 0
    int 0x80              ; Invoke sys_exit syscall

section .data
    fizz_msg db 'Fizz', 0   ; Null-terminated string "Fizz"
    buzz_msg db 'Buzz', 0   ; Null-terminated string "Buzz"
    fizzbuzz_msg db 'FizzBuzz', 0  ; Null-terminated string "FizzBuzz"
