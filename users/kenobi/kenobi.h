#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "k10_pro.h"
#include "raw_hid.h"
#include "battery.h"

#include "kenobi_color_map.h"

// #include "quantum/audio/song_list.h"

// Secure Lock
#define SECURE_UNLOCK_TIMEOUT 5000
#define SECURE_IDLE_TIMEOUT 0
#define SECURE_UNLOCK_SEQUENCE {{213,52}, {213,39}, {213,52}, {203,52}}

// RAW HID
#define RAW_USAGE_PAGE 0xFF60 // Decimal 65376
#define RAW_USAGE_ID 0x61 // Decimal 97

// Keychron K10_Pro Vendor ID
#define VENDOR_ID 0x3434


#define ENABLE_RGB_MATRIX_MULTISPLASH

#undef RGB_LIGHT_EFFECT_RAINBOW_SWIRL
#undef RGB_LIGHT_EFFECT_STATIC_GRADIENT 


enum KENOBI_COMMANDS {
    KENOBI_GET_BATTERY_CMD = 0xC0,
    KENOBI_GET_LAYOUT_CMD = 0xC1, 
};

#endif

