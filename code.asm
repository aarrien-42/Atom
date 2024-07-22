section .bss
  x resb 8
section .text
  global _start
_start:
; Get literal value
  PUSH 42

; Assign value to x
  POP rax
  MOV qword [x], rax

; Get identifier value
  MOV qword [x], rax
  PUSH rax

; Get literal value
  PUSH 3

; Get literal value
  PUSH 2

  POP rcx
  POP rax
  MUL rcx
  PUSH rax

  POP rcx
  POP rax
  SUB rax, rcx
  PUSH rax

; Get literal value
  PUSH 100

  POP rcx
  POP rax
  ADD rax, rcx
  PUSH rax

; Assign value to x
  POP rax
  MOV qword [x], rax

; Get identifier value
  MOV qword [x], rax
  PUSH rax

  POP rdi
  MOV rax, 60
  syscall

