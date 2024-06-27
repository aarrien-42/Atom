section .text
  global _start

_start:
  mov rax, 1
  mov rdi, rax
  mov rax, 60
  syscall
