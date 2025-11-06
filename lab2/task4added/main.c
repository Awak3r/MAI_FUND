#include "include/func.h"
#include <stdio.h>

int main() {
    int roman_val;
    oversscanf("MCMXCIV", "%Ro", &roman_val);
    printf("MCMXCIV = %d\n", roman_val);
    unsigned int zeck_val;
    oversscanf("101011", "%Zr", &zeck_val);
    printf("101011 (Zeckendorf) = %u\n", zeck_val);
    int hex_val;
    oversscanf("1a2f", "%Cv", &hex_val, 16);
    printf("1a2f (base 16) = %d\n", hex_val);
    int hex_upper;
    oversscanf("FF", "%CV", &hex_upper, 16);
    printf("FF (base 16) = %d\n", hex_upper);
    int binary;
    oversscanf("1101", "%Cv", &binary, 2);
    printf("1101 (base 2) = %d\n", binary);
    int dec, rom;
    oversscanf("50 XXV", "%d %Ro", &dec, &rom);
    printf("Decimal: %d, Roman XXV: %d\n", dec, rom);
    int octal;
    oversscanf("77", "%CV", &octal, 8);
    printf("77 (base 8) = %d\n", octal);
    FILE *fp = fopen("input.txt", "w");
    fprintf(fp, "CDXLIV");
    fclose(fp);
    fp = fopen("input.txt", "r");
    int file_roman;
    overfscanf(fp, "%Ro", &file_roman);
    fclose(fp);
    printf("CDXLIV from file = %d\n", file_roman);
    int base10, base16;
    unsigned int zeck;
    oversscanf("100 ff 10011", "%d %Cv %Zr", &base10, &base16, 16, &zeck);
    printf("Parsed: %d, %d, %u\n", base10, base16, zeck);
    int value, chars_read;
    oversscanf("XII 123", "%Ro%n %d", &value, &chars_read, &dec);
    printf("Read %d chars before space, XII=%d, then %d\n", chars_read, value, dec);
    return 0;
}
