mov eax,cr0
or eax,1
mov cr0,eax
mov ax,10h
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
mov ss,ax

; Assembly code for a basic setup screen (example for x86 architecture)

section .data
    ; Text for the setup screen
    title_text db "Welcome to the Setup", 10
    option1_text db "For bussiness (1)", 10
    option2_text db "For home (2)", 10
    option3_text db "Other (general) (3)", 10
    prompt_text db "Select an option:", 10

section .text
    global _start
    mov eax, [system_call_address]
_start:
    ; Initialize video mode (replace with your video card setup)
    mov ax, 0x0013 ; Set video mode 320x200 256 colors
    int 0x10

    ; Clear screen
    mov ax, 0x0000 ; Set video mode 0 (black)
    int 0x10

    ; Print title
    mov dx, 10  ; Set cursor position
    mov ah, 0x0e ; Print string
    mov si, offset title_text
    int 0x10

    ; Print options
    mov dx, 12  ; Set cursor position
    mov ah, 0x0e ; Print string
    mov si, offset option1_text
    int 0x10

    mov dx, 18  ; Set cursor position
    mov ah, 0x0e ; Print string
    mov si, offset option2_text
    int 0x10

    mov dx, 24  ; Set cursor position
    mov ah, 0x0e ; Print string
    mov si, offset option3_text
    int 0x10

    ; Print prompt
    mov dx, 30  ; Set cursor position
    mov ah, 0x0e ; Print string
    mov si, offset prompt_text
    int 0x10

    ; Get user input (replace with keyboard handling logic)
    ; ...

    ; Handle selected option
    ; ...

    ; Exit
    mov ax, 0x4c00 ; Exit to DOS
    int 0x21

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
file_name db 'osselector.c', 0

section .bss
fd_out resb 1
