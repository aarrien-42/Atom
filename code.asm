section .bss
  x resb 8
section .text
  global _start
_start:
; Get literal value
  PUSH 3

; Assign value to x
  POP rax
  MOV qword [x], rax

; Get literal value
  PUSH 5

; Assign value to x
  POP rax
  MOV qword [x], rax

; Get identifier value
  MOV qword [x], rax
  PUSH rax

  POP rdi
  MOV rax, 60
  syscall

