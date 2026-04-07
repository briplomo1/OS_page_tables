#include <stdio.h>
#include <stdlib.h>

unsigned long translate(const unsigned long *table, size_t size, unsigned long v_addr);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        perror("Wrong number of arguments. 2 expected");
        return 1;
    }
    const char* infile = argv[1];
    const char* outfile = argv[2];

    unsigned long curr_addr;
    unsigned long new_addr;
    const unsigned long table[] = {2, 4, 1, 7, 3, 5, 6, -1, -1, -1, -1};

    FILE* in = fopen(infile, "rb");
    FILE* out = fopen(outfile, "wb");
    if(!in || !out) {
        perror("Error opening file");
    }

    while (fread(&curr_addr, sizeof(unsigned long), 1, in)) {
        new_addr = translate(table, sizeof(table), curr_addr);
        fwrite(&new_addr, sizeof(unsigned long), 1, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

unsigned long translate(const unsigned long *table, const size_t size, const unsigned long v_addr) {
    unsigned long offset = v_addr & 0x7F;
    unsigned long vpn = v_addr >> 7;
    printf("v_addr: 0x%X\n", v_addr);
    printf("vpn: 0x%X\n", vpn);
    printf("pfn: 0x%X\n", table[vpn]);
    printf("new_addr: 0x%X\n", (table[vpn]<< 7) | offset);

    return (table[vpn]<<7) | offset;
}