#include <stdio.h>
#include <stdlib.h>

void encrypt(FILE *Original, FILE *Encrypted, FILE *Key) {
    int encryptionkey, i = 0;
    char realtextholder, encryptedtextholder;

    Original = fopen("bootloader.asm", "r");
    Encrypted = fopen("bootloader_encrypted.asm", "w");
    Key = fopen("key.txt", "r");

    if (Original == NULL || Encrypted == NULL || Key == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while ((realtextholder = fgetc(Original)) != EOF) {
        encryptionkey = fgetc(Key);
        if (encryptionkey == EOF) {
            fseek(Key, 0, SEEK_SET); // Rewind key file if at end
            encryptionkey = fgetc(Key);
        }
        encryptedtextholder = realtextholder ^ encryptionkey; // Simple XOR encryption
        fputc(encryptedtextholder, Encrypted);
    }

    fclose(Original);
    fclose(Encrypted);
    fclose(Key);
}

int main() {
    FILE *Original, *Encrypted, *Key;
    encrypt(Original, Encrypted, Key);
    return 0;
}
