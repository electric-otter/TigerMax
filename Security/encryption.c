void encrypted(FILE *Original, FILE *Encrypted, FILE *Key){

    int encryptionkey, i;
    char realtextholder, encryptedtextholder;

    Original = fopen("bootloader.asm", "r");
    Key = fopen("key.txt", "r");
