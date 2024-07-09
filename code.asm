global _start
_start:
  push 24
  push 6
  pop rdx
  pop rax
  sub rax, rdx
  push rax

  push 12
  push 11
  push 1
  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdx
  pop rax
  sub rax, rdx
  push rax

  push 3
  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdx
  pop rax
  add rax, rdx
  push rax

  pop rdi
  mov rax, 60
  syscall
