//
// Created by bripl on 4/5/2026.
//

#define PAGE_SIZE 128
#define OFFSET_MASK 0x7F
#include <stdio.h>

#include "pagetable.h"
#include "physpages.h"

unsigned long translate(unsigned long v_addr);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        perror("Wrong number of arguments. 2 expected");
        return 1;
    }
    const char* infile = argv[1];
    const char* outfile = argv[2];

    FILE* in = fopen(infile, "rb");
    FILE* out = fopen(outfile, "wb");

    if (!in || !out) {
        perror("Error opening file");
        return 1;
    }

    table_init();
    reset_frame_allocator();

    unsigned long v_addr;
    unsigned long p_addr;
    int faults = 0;

    while (fread(&v_addr, sizeof(unsigned long), 1, in)) {
        int vpn = (int) v_addr >> 7;

        // Try to get frame number from page table
        int pfn = table_get(vpn);

        if (pfn == INVALID) {
            // Page fault. look for free frame
            faults++;
            pfn = get_frame();

            if (pfn == INVALID) {
                // No free frame must evict lru
                int victim_vpn = get_lru();
                int victim_frame = table_get(victim_vpn);

                // Invalidate old data and reuse frame
                table_invalidate(victim_vpn);
                pfn = victim_frame;

            }
            table_set(vpn, pfn);
        }

        // Perform translation and write out
        p_addr = translate(v_addr);
        fwrite(&p_addr, sizeof(unsigned long), 1, out);
    }
    fclose(in);
    fclose(out);
    fprintf(stderr, "Total page faults: %d\n", faults);
    return 0;
}