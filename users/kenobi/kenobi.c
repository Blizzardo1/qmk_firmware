#include "kenobi.h"

void keyboard_post_init_user(void) {
    #ifdef AUDIO_ENABLE

    float startup[][2] = SONG(STARTUP_SOUND);
    PLAY_SONG(startup);
    #endif
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
}

void rgb_startup(void) {

}


// originally in k10_pro.c
#if !defined(VIA_ENABLE)
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[length];

    switch (data[0]) {
        case RAW_HID_CMD:
            via_command_kb(data, length);
            break;
        case KENOBI_GET_BATTERY_CMD:
            
            battery_measure();
            response[0] = battery_get_percentage();
            response[1] = battery_get_voltage();
            raw_hid_send(response, length);
            break;
    }
}
#endif