/* Basic BIOS Bootloader in C - Requires Assembly for low-level access */

#include <stdint.h>

// Function to print a string to the console (requires BIOS interrupt)
void print_string(char *str) {
    // Assembly code to set up interrupt parameters (not shown)
    // Call BIOS interrupt 0x10h with AH=0x0E, AL=string pointer
}

// Simple boot loader that displays a message and jumps to the OS
void boot_loader() {
    // Set text color (requires BIOS interrupt)
    // ...

    print_string("TigerMax (v.1.0.0)\n");
    chdir("..");
    fopen("bootloader.asm")
}
