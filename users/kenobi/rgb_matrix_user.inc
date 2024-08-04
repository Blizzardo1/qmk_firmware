// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(kenobi_effect)
// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "kenobi_color_map.h"

static void kenobi_effect_init(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    kenobi_color_map_initialize();
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, RGB_GREEN);
    }
}

static bool kenobi_effect_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, kenobi_color_map[i][0], kenobi_color_map[i][1], kenobi_color_map[i][2]);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
static bool kenobi_effect(effect_params_t* params) {
  if (params->init) kenobi_effect_init(params);
  return kenobi_effect_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS