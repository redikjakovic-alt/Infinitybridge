/*
 * InfinityBridge — portable adapter implementation.
 *
 * FlipBase is a separate dependency; see docs/INTEGRATION.md.
 */
#include "infinity_bridge.h"

void ib_init(InfinityBridge* bridge) {
    if (bridge == 0) {
        return;
    }
    inf_base_init(&bridge->protocol);
}

void ib_reset_link(InfinityBridge* bridge) {
    if (bridge == 0) {
        return;
    }
    inf_base_reset_link(&bridge->protocol);
}

bool ib_handle_out(InfinityBridge* bridge, const uint8_t packet[INF_PACKET_SIZE]) {
    if (bridge == 0 || packet == 0) {
        return false;
    }
    inf_base_handle_out(&bridge->protocol, packet);
    return true;
}

bool ib_next_in(InfinityBridge* bridge, uint8_t packet[INF_PACKET_SIZE]) {
    if (bridge == 0 || packet == 0) {
        return false;
    }
    return inf_base_next_in(&bridge->protocol, packet);
}

bool ib_load_figure(
    InfinityBridge* bridge,
    uint8_t slot,
    const uint8_t image[INF_FIGURE_SIZE]) {
    if (bridge == 0 || image == 0 || slot >= INF_SLOT_COUNT) {
        return false;
    }
    return inf_base_load_figure(&bridge->protocol, slot, image);
}

bool ib_remove_figure(InfinityBridge* bridge, uint8_t slot) {
    if (bridge == 0 || slot >= INF_SLOT_COUNT) {
        return false;
    }
    return inf_base_remove_figure(&bridge->protocol, slot);
}

bool ib_slot_present(const InfinityBridge* bridge, uint8_t slot) {
    if (bridge == 0 || slot >= INF_SLOT_COUNT) {
        return false;
    }
    return inf_base_slot_present(&bridge->protocol, slot);
}

bool ib_take_dirty(
    InfinityBridge* bridge,
    uint8_t slot,
    uint8_t image[INF_FIGURE_SIZE]) {
    if (bridge == 0 || image == 0 || slot >= INF_SLOT_COUNT) {
        return false;
    }
    return inf_base_take_dirty(&bridge->protocol, slot, image);
}
