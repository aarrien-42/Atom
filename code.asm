global _start
_start:
  push 1
  push 2
  pop rdx
  pop rax
  sub rax, rdx
  push rax

  push 3
  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdi
  mov rax, 60
  syscall
