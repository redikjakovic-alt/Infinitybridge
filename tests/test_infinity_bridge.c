#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "infinity_bridge.h"

static void test_init_and_figure_events(void) {
    InfinityBridge bridge;
    uint8_t figure[INF_FIGURE_SIZE];
    uint8_t packet[INF_PACKET_SIZE];

    memset(figure, 0x5A, sizeof(figure));
    ib_init(&bridge);

    assert(!ib_slot_present(&bridge, 0));
    assert(ib_load_figure(&bridge, 0, figure));
    assert(ib_slot_present(&bridge, 0));

    /* Loading a figure queues an added event before ordinary replies. */
    assert(ib_next_in(&bridge, packet));
    assert(packet[0] == 0xAB);
    assert(packet[1] == 0x04);
    assert(packet[2] == 0x01); /* first physical position */
    assert(packet[3] == 0x09);
    assert(packet[5] == 0x00); /* added */

    assert(ib_remove_figure(&bridge, 0));
    assert(!ib_slot_present(&bridge, 0));
    assert(ib_next_in(&bridge, packet));
    assert(packet[0] == 0xAB);
    assert(packet[5] == 0x01); /* removed */
}

static void test_out_in_round_trip(void) {
    InfinityBridge bridge;
    uint8_t out[INF_PACKET_SIZE] = {0};
    uint8_t in[INF_PACKET_SIZE];

    ib_init(&bridge);

    /* 0x90 is a documented light command with a blank acknowledgement. */
    out[2] = 0x90;
    out[3] = 0x42;
    assert(ib_handle_out(&bridge, out));
    assert(ib_next_in(&bridge, in));

    assert(in[0] == 0xAA);
    assert(in[1] == 0x01);
    assert(in[2] == 0x42);
    assert(in[3] == (uint8_t)(0xAA + 0x01 + 0x42));
}

static void test_argument_validation(void) {
    InfinityBridge bridge;
    uint8_t data[INF_FIGURE_SIZE] = {0};
    uint8_t packet[INF_PACKET_SIZE];

    ib_init(&bridge);
    assert(!ib_handle_out(0, packet));
    assert(!ib_handle_out(&bridge, 0));
    assert(!ib_next_in(0, packet));
    assert(!ib_next_in(&bridge, 0));
    assert(!ib_load_figure(&bridge, INF_SLOT_COUNT, data));
    assert(!ib_load_figure(&bridge, 0, 0));
    assert(!ib_remove_figure(&bridge, INF_SLOT_COUNT));
    assert(!ib_take_dirty(&bridge, 0, 0));
}

int main(void) {
    test_init_and_figure_events();
    test_out_in_round_trip();
    test_argument_validation();
    puts("InfinityBridge adapter tests: OK");
    return 0;
}
