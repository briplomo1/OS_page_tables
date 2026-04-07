//
// Created by bripl on 4/5/2026.
//

#include <stdlib.h>
#include "pagetable.h"

#define PAGES 32
#define INVALID -1

static Entry table[PAGES];
static unsigned long clock = 0;

void table_init() {
    int i;
    for (i = 0; i < PAGES; i++) {
        table[i].frame = INVALID;
        table[i].valid = 0;
        table[i].timestamp = 0;
    }
    clock = 0;
}

int table_get(int vpn) {
    if (vpn >= PAGES || vpn < 0) {
        return INVALID;
    }
    if (table[vpn].valid) {
        table[vpn].timestamp = ++clock;
        return table[vpn].frame;
    }
    return INVALID;
}

void table_set(int vpn, int pfn) {
    if (vpn >= PAGES || vpn < 0) {
        return;
    }
    table[vpn].valid = 1;
    table[vpn].frame = pfn;
    table[vpn].timestamp = ++clock;
}

void table_invalidate(int vpn) {
    if (vpn >= PAGES || vpn < 0) {
        return;
    }
    table[vpn].valid = 0;
}

int get_lru() {
    int i;
    int victim = 0;
    unsigned long min = table[0].timestamp;

    for (i = 1; i < PAGES; i++) {
        if (table[i].valid && table[i].timestamp < min) {
            min = table[i].timestamp;
            victim = i;
        }
    }
    return victim;
}


