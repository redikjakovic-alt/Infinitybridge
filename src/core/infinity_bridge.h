/*
 * InfinityBridge — portable adapter interface.
 *
 * This file is original InfinityBridge glue. The protocol implementation
 * itself is provided by the separately pinned FlipBase dependency.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "infinity_core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    InfBase protocol;
} InfinityBridge;

/*
 * Initialize or reset the bridge and all protocol state.
 * This also clears loaded figures.
 */
void ib_init(InfinityBridge* bridge);

/*
 * Reset link queues/handshake while preserving loaded figure images.
 */
void ib_reset_link(InfinityBridge* bridge);

/*
 * Pass one 32-byte Disney Infinity OUT packet to the protocol core.
 * Returns false only for an invalid bridge or packet pointer.
 */
bool ib_handle_out(InfinityBridge* bridge, const uint8_t packet[INF_PACKET_SIZE]);

/*
 * Fetch the next 32-byte IN packet. Returns false if the queue is empty
 * or an argument is invalid.
 */
bool ib_next_in(InfinityBridge* bridge, uint8_t packet[INF_PACKET_SIZE]);

/*
 * Load/remove a figure in one of the nine logical slots.
 * Figure images are exactly INF_FIGURE_SIZE (320) bytes.
 */
bool ib_load_figure(
    InfinityBridge* bridge,
    uint8_t slot,
    const uint8_t image[INF_FIGURE_SIZE]);

bool ib_remove_figure(InfinityBridge* bridge, uint8_t slot);
bool ib_slot_present(const InfinityBridge* bridge, uint8_t slot);

/*
 * Copy figure data modified by the game. Returns true only when dirty
 * data was available and copied to image.
 */
bool ib_take_dirty(
    InfinityBridge* bridge,
    uint8_t slot,
    uint8_t image[INF_FIGURE_SIZE]);

#ifdef __cplusplus
}
#endif
