global _start
_start:
  PUSH 1
  PUSH 2
  PUSH 4
  POP rcx
  POP rax
  MUL rcx
  PUSH rax

  POP rcx
  POP rax
  ADD rax, rcx
  PUSH rax

  POP rdi
  MOV rax, 60
  syscall
