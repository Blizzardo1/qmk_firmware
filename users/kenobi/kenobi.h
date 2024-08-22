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
#define SECURE_UNLOCK_TIMEOUT 5000
#define SECURE_IDLE_TIMEOUT 0
#define SECURE_UNLOCK_SEQUENCE { {0, 0} } // {{213,52}, {213,39}, {213,52}, {203,52}}

// RAW HID
#define RAW_USAGE_PAGE 0xFF60 // Decimal 65376
#define RAW_USAGE_ID 0x61 // Decimal 97

// Keychron K10_Pro Vendor ID
#define VENDOR_ID 0x3434


#define ENABLE_RGB_MATRIX_MULTISPLASH

#undef RGB_LIGHT_EFFECT_RAINBOW_SWIRL
#undef RGB_LIGHT_EFFECT_STATIC_GRADIENT

os_variant_t dos;

void process_record_win32(uint16_t keycode, keyrecord_t *record);
void process_record_gnu(uint16_t keycode, keyrecord_t *record);
void process_record_macos(uint16_t keycode, keyrecord_t *record);
void process_record_ios(uint16_t keycode, keyrecord_t *record);


enum KENOBI_COMMANDS {
    KENOBI_GET_BATTERY_CMD = 0xC0,
    KENOBI_GET_LAYOUT_CMD = 0xC1,
    KENOBI_GET_LOCK_STATUS_CMD = 0xC2,
};

// Move these someplace else
uint8_t max(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}

uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

/*
    \brief Get the middle value of a number between 0 and 255
    \param a The number to get the middle value of
    \remarks Basically clamp8 but with a different name, I'm not sure why I did this. I'm stupid.
*/
uint8_t mid(uint8_t a) {
    return a < 0 ? 0 : a > 255 ? 255 : a;
}

#endif

