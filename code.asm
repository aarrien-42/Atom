global _start
_start:
  push 1
  push 2
  push 3
  push 4
  pop rdx
  pop rax
  add rax, rdx
  push rax

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
