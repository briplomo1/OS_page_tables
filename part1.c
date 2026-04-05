#include <stdio.h>
#include <stdlib.h>
# include <stdint.h>

uint32_t translate(const int *table, size_t size, uint32_t v_addr);

int main(int argc, char* argv) {
    if(argc < 3) {
        perror("Wrong number of arguments. 2 expected");
    }
    char* infile = argv[1];
    char* outfile = argv[2];

    uint32_t curr_addr;
    const int table[] = {2, 4, 1, 7, 3, 5, 6, -1, -1, -1, -1};

    FILE* in = fopen(infile, "rb");
    FILE* out = fopen(outfile, "wb");
    if(!in || !out) {
        perror("Error opening file");
    }
    fseek(in, 0, SEEK_END);
    while (fread(&curr_addr, sizeof(uint32_t), 1, in)) {
        curr_addr = translate(table, sizeof(uint32_t), curr_addr);
        fwrite(&curr_addr, sizeof(uint32_t), 1, out);
    }

    return 0;
}

uint32_t translate(const int *table, const size_t size, const uint32_t v_addr) {
    return table[v_addr];
}