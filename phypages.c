//
// Created by bripl on 4/5/2026.
//
#include "physpages.h"

static int next_free = 1;

int get_frame() {
    if (next_free < FRAMES) {
        return next_free++;
    }
    return INVALID;
}

void reset_frame_allocator() {
    next_free = 1;
}


