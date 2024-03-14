#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

int readNboIntFromFile(char* filename, uint32_t *out) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File open error\n");
        return 1;
    }
    uint32_t n;
    if (fread(&n, sizeof(uint32_t), 1, file) != 1) {
        printf("File read error\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    *out = ntohl(n);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax : %s <file1> <file2>\n", argv[0]);
        printf("sample : %s a.bin b.bin\n", argv[0]);
        return 1;
    }

    uint32_t n1, n2;
    if (
        !readNboIntFromFile(argv[1], &n1) &&
        !readNboIntFromFile(argv[2], &n2)
    )
        printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, n1 + n2, n1 + n2);

    return 0;
}