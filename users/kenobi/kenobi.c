#include "kenobi.h"

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
#endif
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_kenobi_effect);
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
    if(host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(37, 255, 0, 0);
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(62, 0, 255, 0);
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, kenobi_color_caps_map[i][0], kenobi_color_caps_map[i][1], kenobi_color_caps_map[i][2]);
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
