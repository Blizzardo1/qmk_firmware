#include "kenobi.h"
#include <stdint.h>
#include "config.h"
#include "debug.h"
#include "host.h"
#include "indicator.h"
#include "led.h"
#include "os_detection.h"
#include "rgb_matrix.h"
#include "transport.h"

os_variant_t dos;

typedef struct {
    uint8_t  r, g, b;
    uint32_t expires;   // 0 = never expires
    bool     active;
} led_overlay_t;

static led_overlay_t overlay[RGB_MATRIX_LED_COUNT];

static void overlay_set(uint8_t i, uint8_t r, uint8_t g, uint8_t b, uint16_t ms) {
    overlay[i].r       = r;
    overlay[i].g       = g;
    overlay[i].b       = b;
    overlay[i].expires = ms ? (timer_read32() + ms) : 0;
    overlay[i].active  = true;
}

static void overlay_apply(uint8_t led_min, uint8_t led_max) {
    uint32_t now = timer_read32();
    for (uint8_t i = led_min; i < led_max; i++) {
        if (!overlay[i].active) continue;
        if (overlay[i].expires && timer_expired32(now, overlay[i].expires)) {
            overlay[i].active = false;
            continue;
        }
        rgb_matrix_set_color(i, overlay[i].r, overlay[i].g, overlay[i].b);
    }
}

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
#endif
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_KENOBI_EFFECT);
}

#define SEND_LENGTH 32

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
    dos = detected_os;
    // uint8_t mode = rgb_matrix_get_mode();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
    switch(detected_os) {
        case OS_LINUX:
            // #1030FF
            rgb_matrix_set_color_all(16, 48, 255);
            break;
        case OS_MACOS:
            // #6030F0
            rgb_matrix_set_color_all(96, 48, 224);
            break;
        case OS_WINDOWS:
            // #0000FF
            rgb_matrix_set_color_all(0, 0, 255);
            break;
        case OS_IOS:
            // #A010A0
            rgb_matrix_set_color_all(160, 16, 160);
            break;
        case OS_UNSURE:
        default:
            // #C0C0C0
            rgb_matrix_set_color_all(192, 192, 192);
            break;
    }
    // rgb_matrix_mode_noeeprom(mode);
    return true;
}
#endif

bool process_record_win32(uint16_t keycode, keyrecord_t *record) {
    // Not ready
    if (record->event.pressed && (keycode == LGUI(KC_L))) {
        // Windows+L was pressed
        // Add your code here
        rgb_matrix_mode(RGB_MATRIX_PIXEL_RAIN);
    }

    return true;
}

bool process_record_gnu(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed && (keycode == LGUI(KC_L))) {
        // Super+L was pressed
        // Add your code here
        rgb_matrix_mode(RGB_MATRIX_PIXEL_RAIN);
    }
    if(record->event.pressed && (keycode == LGUI(KC_R))) {
        // Super+R was pressed
        // Add your code here
        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);

        // #FF8040
        rgb_matrix_set_color_all(255, 128, 64);

    }
    return true;
}

bool process_record_macos(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_ios(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case QK_DEBUG_TOGGLE:
            // rgblight_blink_layer_repeat(debug_enable ? 0 : 1, 200, 3);
        break;
    }
    switch (dos) {
        case OS_WINDOWS:
            process_record_win32(keycode, record);
            break;
        case OS_LINUX:
            process_record_gnu(keycode, record);
            break;
        case OS_MACOS:
            process_record_macos(keycode, record);
            break;
        case OS_IOS:
            process_record_ios(keycode, record);
            break;
        case OS_UNSURE:
        default:
            process_record_gnu(keycode, record);
            break;
    }
    return true;
}

void matrix_init_user(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            uint8_t color[3] = {mid(index * 4), mid(index * 6), mid(index * 2)};
            rgb_matrix_set_color(index, color[0], color[1], color[2]);
        }
    }
}

// ?????
void keyboard_pre_sleep_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Layer State Changed
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        if (layer_state_is(1)) {
            rgb_matrix_set_color_all(HSV_OFF);
        }

        // static coloring
        uint32_t hex_color = 0xFF8050;
        uint8_t color[3] = {hex_color >> 16 & 0xFF, hex_color >> 8 & 0xFF, hex_color & 0xFF};

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});

                if(index == 0 && keycode > KC_TRNS) {
                    // Set Escape to RED if a keybind is set.
                    rgb_matrix_set_color(index, 255, 0, 0);
                }

                // dynamic coloring
                // uint8_t color[3] = {mid(index * 4), mid(index * 6), mid(index * 6)};
                if (index >= led_min && index < led_max && index != NO_LED && keycode > KC_TRNS) {
                    rgb_matrix_set_color(index, color[0], color[1], color[2]);
                }
            }
        }
    }
    overlay_apply(led_min, led_max);
    return false;
}

static void send_event(uint8_t type, uint8_t a, uint8_t b) {
    uint8_t ev[SEND_LENGTH] = {KENOBI_EVENT, type, a, b};
    raw_hid_send(ev, SEND_LENGTH);
}

bool secure_hook_user(secure_status_t secure_status) {
    switch (secure_status) {
        case SECURE_LOCKED:
            // rgb_matrix_set_color_all(HSV_RED);
            rgb_matrix_mode(RGB_MATRIX_PIXEL_RAIN);
            break;
        case SECURE_UNLOCKED:
            // rgb_matrix_set_color_all(HSV_GREEN);
            // rgb_matrix_mode(RGB_MATRIX_CUSTOM_KENOBI_EFFECT);
            rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
            break;
        case SECURE_PENDING:
            rgb_matrix_set_color_all(HSV_YELLOW);
            break;
    }
    snled27351_flush();

    send_event(KENOBI_GET_LOCK_STATUS_CMD, secure_status, 0);

    return true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    keypos_t key;
    uint8_t response[SEND_LENGTH] = {0};

    switch (data[0]) {
        case KENOBI_GET_BATTERY_CMD:
            response[0] = KENOBI_GET_BATTERY_CMD;
            battery_measure();
            uint16_t voltage = battery_get_voltage();
            response[1]      = battery_get_percentage();
            response[2]      = (voltage >> 8) & 0xFF;
            response[3]      = (voltage) & 0xFF;
            break;
        case KENOBI_GET_LAYOUT_CMD:
            if(data[1] >= MATRIX_ROWS || data[2] >= MATRIX_COLS) {
                response[0] = KENOBI_GET_LAYOUT_CMD;
                response[1] = K_ERR_RANGE;
                break;
            }
            key.row     = data[1];
            key.col     = data[2];
            response[0] = KENOBI_GET_LAYOUT_CMD;
            response[1] = layer_switch_get_layer(key);
            break;
        case KENOBI_GET_LOCK_STATUS_CMD:
            response[0] = KENOBI_GET_LOCK_STATUS_CMD;
            response[1] = secure_get_status();
            break;
        case KENOBI_GET_WPM:
            response[0] = KENOBI_GET_WPM;
            response[1] = get_current_wpm();
        break;

        case KENOBI_GET_OS:
            response[0] = KENOBI_GET_OS;
            response[1] = (uint8_t)dos;
        break;
        case KENOBI_GET_CONN_MODE:
            response[0] = KENOBI_GET_CONN_MODE;
            response[1] = get_transport();
        break;
        case KENOBI_GET_PING:
            memcpy(response, data, SEND_LENGTH);
        break;
        case KENOBI_GET_VERSION:
            response[0] = KENOBI_GET_VERSION;
            response[1] = K_OK;
            response[2] = KENOBI_PROTO_MAJOR;
            response[3] = KENOBI_PROTO_MINOR;
        break;
        case KENOBI_SET_BRIGHTNESS:
            response[0] = KENOBI_SET_BRIGHTNESS;
            rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(),
                rgb_matrix_get_sat(),
                min(data[1], RGB_MATRIX_MAXIMUM_BRIGHTNESS));
        break;
        case KENOBI_SET_RGB_MODE:
            response[0] = KENOBI_SET_RGB_MODE;
            if(length < 2) {
                response[1] = K_ERR_LEN;
            } else if (data[1] >= RGB_MATRIX_EFFECT_MAX) {
                response[1] = K_ERR_RANGE;
            } else {
                rgb_matrix_mode_noeeprom(data[1]);
                response[1] = K_OK;
            }
        break;
        case KENOBI_SET_RGB_COLOR:
            response[0] = KENOBI_SET_RGB_COLOR;
            rgb_matrix_sethsv_noeeprom(data[1],
                    data[2],
                    min(data[3], RGB_MATRIX_MAXIMUM_BRIGHTNESS));
            response[1] = K_OK;
        break;
        case KENOBI_SET_LED:
            response[0] = KENOBI_SET_LED;
            if(length < 7) {
                response[1] = K_ERR_LEN;
                break;
            }
            if(data[1] >= RGB_MATRIX_LED_COUNT) {
                response[1] = K_ERR_RANGE;
                break;
            }
            overlay_set(data[1], data[2], data[3], data[4], (data[5] << 8) | data[6]);
            response[1] = K_OK;
        break;
        case KENOBI_CLEAR_LED:
            response[0] = KENOBI_CLEAR_LED;
            if(length < 2) {
                response[1] = K_ERR_LEN;
                break;
            }
            if(data[1] == 0xFF) {
                memset(overlay, 0, sizeof(overlay)); // May break;
            } else if(data[1] < RGB_MATRIX_LED_COUNT) {
                overlay[data[1]].active = false;
            } else {
                response[1] = K_ERR_RANGE;
                break;
            }
            response[1] = K_OK;
        break;
        case KENOBI_LOCK:
            response[0] = KENOBI_LOCK;
            secure_lock();
            response[1] = K_OK;
        break;
        case KENOBI_BOOTLOADER:
            if (length >= 5 && data[1]==0xDE && data[2]==0xAD && data[3]==0xB0 && data[4]==0x0B) {
                reset_keyboard();
            }
            response[0] = KENOBI_BOOTLOADER; response[1] = K_ERR_DENIED;
        break;
        case KENOBI_EVENT:
            return;
        default:
            k10_pro_raw_hid_receive(data, length);
        return;
    }
    raw_hid_send(response, SEND_LENGTH);
}
