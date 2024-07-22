section .bss
x resb 8
global _start
_start:
  PUSH 0
  POP rdi
  MOV rax, 60
  syscall
