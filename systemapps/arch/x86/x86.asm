section .data
    message db "Welcome! Boot in x86...", 10 ; String to print, including newline
    message_len equ $ - message ; Calculate string length

section .text
    global _start ; Entry point for the program

_start:
    ; Set up the system call number for writing to standard output (sys_write)
    mov eax, 4 

    ; Set up the file descriptor for standard output (stdout)
    mov ebx, 1 

    ; Load the address of the message string into ecx
    mov ecx, message 

    ; Load the length of the message into edx
    mov edx, message_len 

    ; Make the system call
    int 0x80 

    ; Exit the program
    mov eax, 1
    mov ebx, 0
    int 0x80 
