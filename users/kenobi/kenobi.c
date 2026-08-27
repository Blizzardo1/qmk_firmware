#include "kenobi.h"
#include <stdint.h>
#include "debug.h"
#include "os_detection.h"
#include "rgb_matrix.h"

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
#endif
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_KENOBI_EFFECT);
}

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

#endif

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
    return false;
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

    uint8_t response[32];
    memset(response, 0, 32);
    response[0] = KENOBI_GET_LOCK_STATUS_CMD;
    response[1] = secure_status;
    raw_hid_send(response, 32);

    return true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t __sendlen = 32;
    uint8_t  response[__sendlen];
    keypos_t key;
    switch (data[0]) {
        case KENOBI_GET_BATTERY_CMD:
            response[0] = KENOBI_GET_BATTERY_CMD;
            battery_measure();
            uint16_t voltage = battery_get_voltage();
            response[1]      = battery_get_percentage();
            response[2]      = (voltage >> 8) & 0xFF;
            response[3]      = (voltage) & 0xFF;
            raw_hid_send(response, __sendlen);
            break;
        case KENOBI_GET_LAYOUT_CMD:
            key.row     = data[1];
            key.col     = data[2];
            response[0] = KENOBI_GET_LAYOUT_CMD;
            response[1] = layer_switch_get_layer(key);
            raw_hid_send(response, __sendlen);
            break;
        case KENOBI_GET_LOCK_STATUS_CMD:
            response[0] = KENOBI_GET_LOCK_STATUS_CMD;
            response[1] = secure_get_status();
            raw_hid_send(response, __sendlen);
            break;
        case KENOBI_GET_WPM:
            response[0] = KENOBI_GET_WPM;
            response[1] = get_current_wpm();
            raw_hid_send(response, __sendlen);
        break;
    }
    k10_pro_raw_hid_receive(data, length);
}
