#include "kenobi.h"

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
#endif
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_KENOBI_EFFECT);
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    dos = detected_os;

    return true;
}

void process_record_win32(keyrecord_t *record) {
    // Not ready
    if (record->event.pressed && (record->event.keycode == LGUI(KC_L))) {
        // Windows+L was pressed
        // Add your code here
    }
}

void process_record_gnu(keyrecord_t *record) {

}

void process_record_macos(keyrecord_t *record) {

}

void process_record_ios(keyrecord_t *record) {

}

void process_record(keyrecord_t *record) {
    switch(dos) {
        case OS_WINDOWS:
        process_record_win32(record);
        case OS_LINUX:
        process_record_gnu(record);
        case OS_MACOS:
        process_record_macos(record);
        case OS_IOS:
        process_record_ios(record);
        break;
    }
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
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if(layer_state_is(1)) {
                    rgb_matrix_set_color_all(HSV_OFF);
                }


                if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    uint8_t color[3] = {mid(index * 4), mid(index * 6), mid(index * 2)};
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
    uint8_t response[32];
    keypos_t key;
    switch (data[0]) {
        case KENOBI_GET_BATTERY_CMD:
            battery_measure();
            uint16_t voltage = battery_get_voltage();
            response[1]      = battery_get_percentage();
            response[2]      = (voltage >> 8) & 0xFF;
            response[3]      = (voltage) & 0xFF;
            raw_hid_send(response, length);
            break;
        case KENOBI_GET_LAYOUT_CMD:
            key.row = data[1];
            key.col = data[2];
            response[0] = KENOBI_GET_LAYOUT_CMD;
            response[1] = layer_switch_get_layer(key);
            raw_hid_send(response, length);
            break;
        case KENOBI_GET_LOCK_STATUS_CMD:
            response[0] = KENOBI_GET_LOCK_STATUS_CMD;
            response[1] = secure_get_status();
            raw_hid_send(response, length);
            break;
    }
    k10_pro_raw_hid_receive(data, length);
}
