//
// Created by bripl on 4/6/2026.
//

#ifndef PAGETABLE_H
#define PAGETABLE_H

typedef struct {
    int valid;
    int frame;
    unsigned long timestamp;
} Entry;

void table_init(void);

int table_get(int vpn);

void table_set(int vpn, int pfn);

void table_invalidate(int vpn);

int get_lru();


#endif //PAGETABLE_H
