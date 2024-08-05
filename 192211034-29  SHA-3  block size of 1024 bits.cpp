#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define STATE_SIZE 25
#define LANE_SIZE 64

void set_random_bit(uint64_t state[STATE_SIZE]) {
    int lane = rand() % STATE_SIZE;
    int bit = rand() % LANE_SIZE;
    state[lane] |= ((uint64_t)1 << bit);
}

int all_lanes_nonzero(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {

    uint64_t state[STATE_SIZE] = {0};

    srand(time(NULL));

    int steps = 0;

    while (!all_lanes_nonzero(state)) {
        set_random_bit(state);
        steps++;
    }

    printf("Number of steps until all lanes have at least one nonzero bit: %d\n", steps);

    return 0;
}

