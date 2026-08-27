#ifndef USERSPACE
#define USERSPACE


#include "quantum.h"
#include "k10_pro.h"
#include "raw_hid.h"
#include "battery.h"
#include "secure.h"
#include "os_detection.h"

// #include "quantum/audio/song_list.h"

// Secure Lock
#define SECURE_UNLOCK_SEQUENCE { {0, 0} } // {{213,52}, {213,39}, {213,52}, {203,52}}

// RAW HID
#define RAW_USAGE_PAGE 0xFF60 // Decimal 65376
#define RAW_USAGE_ID 0x61 // Decimal 97

// Keychron K10_Pro Vendor ID
#define VENDOR_ID 0x3434
#define MATRIX_ROWS 6
#define MATRIX_COLS 21


#define ENABLE_RGB_MATRIX_MULTISPLASH

#undef RGB_LIGHT_EFFECT_RAINBOW_SWIRL
#undef RGB_LIGHT_EFFECT_STATIC_GRADIENT

#ifdef OS_DETECTION_ENABLE
os_variant_t dos;

bool process_record_win32(uint16_t keycode, keyrecord_t *record);
bool process_record_gnu(uint16_t keycode, keyrecord_t *record);
bool process_record_macos(uint16_t keycode, keyrecord_t *record);
bool process_record_ios(uint16_t keycode, keyrecord_t *record);

#endif

enum KENOBI_COMMANDS {
    KENOBI_GET_BATTERY_CMD = 0xC0,
    KENOBI_GET_LAYOUT_CMD = 0xC1,
    KENOBI_GET_LOCK_STATUS_CMD = 0xC2,
    KENOBI_GET_WPM = 0xC3
};

// Move these someplace else
static inline uint8_t max(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}

static inline uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

/*
    \brief Clamp a value into the 8-bit range.
    \param a The number to clamp.
*/
static inline uint8_t mid(int16_t a) {
    if (a < 0) {
        return 0;
    }
    if (a > 255) {
        return 255;
    }
    return (uint8_t)a;
}

#endif

