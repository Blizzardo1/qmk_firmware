#ifndef USERSPACE
#define USERSPACE


#include "quantum.h"
#include "k10_pro.h"
#include "raw_hid.h"
#include "battery.h"
#include "secure.h"
#include "os_detection.h"

// #include "quantum/audio/song_list.h"

#define KENOBI_PROTO_MAJOR 1
#define KENOBI_PROTO_MINOR 1

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
extern os_variant_t dos;

bool process_record_win32(uint16_t keycode, keyrecord_t *record);
bool process_record_gnu(uint16_t keycode, keyrecord_t *record);
bool process_record_macos(uint16_t keycode, keyrecord_t *record);
bool process_record_ios(uint16_t keycode, keyrecord_t *record);

#endif

enum KENOBI_STATUS {
    K_OK = 0,
    K_ERR_RANGE = 1,
    K_ERR_LEN = 2,
    K_ERR_DENIED = 3,
    K_ERR_UNKNOWN = 0xFF
};

enum KENOBI_COMMANDS {
    KENOBI_GET_BATTERY_CMD = 0xC0,
    KENOBI_GET_LAYOUT_CMD = 0xC1,
    KENOBI_GET_LOCK_STATUS_CMD = 0xC2,
    KENOBI_GET_WPM = 0xC3,
    KENOBI_GET_OS = 0xC4,
    KENOBI_GET_CONN_MODE = 0xC5,
    KENOBI_GET_PING = 0xC6,
    KENOBI_GET_VERSION = 0xC7,
    KENOBI_SET_BRIGHTNESS = 0xC8,
    KENOBI_SET_RGB_MODE = 0xC9,
    KENOBI_SET_RGB_COLOR = 0xCA,
    KENOBI_SET_LED = 0xCB,
    KENOBI_CLEAR_LED = 0xCC,
    KENOBI_LOCK = 0xCD,
    KENOBI_BOOTLOADER = 0xCE,
    KENOBI_EVENT = 0xCF
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

