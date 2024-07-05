global _start
_start:
  push 1
  push 2
  push 6
  push 7
  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdx
  pop rax
  sub rax, rdx
  push rax

  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdi
  mov rax, 60
  syscall
