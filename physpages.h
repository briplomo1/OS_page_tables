//
// Created by bripl on 4/6/2026.
//

#ifndef PHYSPAGES_H
#define PHYSPAGES_H

#define FRAMES 8
#define PAGE_SIZE 128
#define OFFSET 7
#define OFFSET_MASK 0x7F
#define INVALID -1

int get_frame();

void reset_frame_allocator();

#endif //PHYSPAGES_H
