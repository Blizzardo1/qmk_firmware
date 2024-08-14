#include "kenobi.h"

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
#endif
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_KENOBI_EFFECT);
}

// Unused (undeclared)?
void rgb_startup(void) {
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
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

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }
    return false;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[32];
    keypos_t key;
    switch (data[0]) {
        case KENOBI_GET_BATTERY_CMD:
            battery_measure();
            uint16_t voltage = battery_get_voltage();
            response[0]      = battery_get_percentage();
            response[1]      = (voltage >> 8) & 0xFF;
            response[2]      = (voltage) & 0xFF;
            raw_hid_send(response, length);
            break;
        case KENOBI_GET_LAYOUT_CMD:
            key.row = data[1];
            key.col = data[2];
            response[0] = layer_switch_get_layer(key);
            raw_hid_send(response, length);
            break;
    }
    k10_pro_raw_hid_receive(data, length);
}
