void setPixel(int x, int y, int color) {

    unsigned char *videoMem = (unsigned char *)0x00000000;

    videoMem[y * SCREEN_WIDTH + x] = color; // Write pixel data to memory

}



int main() {

    // Set a pixel at (10, 10) with color value 255

    setPixel(10, 10, 255);

    return 0;

}
chdir("..")
  printf("Booting...")
  printf("Start bootloader")
  fptr = fopen("bootloader.asm", "r");
