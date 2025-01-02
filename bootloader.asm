mov eax,cr0
or eax,1
mov cr0,eax
mov ax,10h
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
mov ss,ax

section .text
   global _start         ;must be declared for using gcc
    
_start:                  ;tell linker entry point
   ; Open the existing file for reading
   mov  eax, 5           ; sys_open system call number
   mov  ebx, file_name   ; file name
   mov  ecx, 0           ; access mode (O_RDONLY)
   int  0x80             ; call kernel
   mov  [fd_out], eax

   ; Keep the program running without exiting
hang:
   jmp hang

section .data
file_name db 'osselector.txt', 0

section .bss
fd_out resb 1
