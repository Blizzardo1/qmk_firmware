// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(KENOBI_EFFECT)
RGB_MATRIX_EFFECT(KENOBI_LOCKED)
// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define ENTRY_SIZE 5
// ID, OCCURRENCE, R, G, B
//   The OCCURRENCE is the number of times the color
//   should be displayed before moving to the next color

const int kenobi_keymap[][ENTRY_SIZE] = {
{0, 1, 255, 0, 0},      {1, 4, 255, 128, 0},    {5, 2, 255, 128, 191},  {7, 2, 255, 128, 0},
{9, 2, 255, 128, 191},  {11, 1, 0, 255, 0},     {12, 1, 255, 255, 0},   {13, 1, 0, 255, 0},
{14, 1, 217, 165, 33},  {15, 1, 153, 245, 255}, {16, 1, 128, 255, 0},   {17, 1, 255, 124, 77},
{18, 1, 255, 255, 255}, {19, 1, 255, 0, 0},     {20, 1, 0, 128, 128},   {21, 10, 122, 0, 255},
{31, 1, 0, 255, 255},   {32, 1, 255, 0, 255},   {33, 1, 0, 255, 128},   {34, 3, 255, 217, 0},
{37, 1, 0, 255, 255},   {38, 1, 255, 217, 0},   {39, 1, 0, 255, 0},     {40, 1, 71, 110, 106},
{41, 1, 255, 128, 0},   {42, 10, 255, 0, 0},    {52, 3, 0, 255, 0},     {55, 3, 255, 217, 0},
{58, 3, 122, 0, 255},   {61, 1, 0, 255, 0},     {62, 1, 255, 128, 0},   {63, 3, 255, 0, 0},
{66, 1, 0, 255, 255},   {67, 2, 255, 0, 0},     {69, 1, 0, 255, 255},   {70, 2, 255, 0, 0},
{72, 2, 0, 255, 0},     {74, 1, 255, 128, 0},   {75, 3, 122, 0, 255},   {78, 1, 255, 128, 0},
{79, 7, 255, 0, 0},     {86, 3, 0, 255, 0},     {89, 1, 255, 128, 0},   {90, 1, 0, 128, 128},
{91, 3, 122, 0, 255},   {94, 1, 255, 217, 0},   {95, 1, 0, 128, 128},   {96, 1, 255, 255, 0},
{97, 1, 255, 0, 255},   {98, 1, 255, 124, 77},  {99, 1, 255, 0, 255},   {100, 1, 255, 255, 0},
{101, 1, 255, 128, 191},{102, 1, 0, 128, 128},  {103, 3, 0, 255, 0},    {106, 1, 122, 0, 255},
{107, 1, 255, 217, 0}
};


static void kenobi_effect_init(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 1, 36, 86);
    }
}


static bool kenobi_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (int i = 0; i < sizeof(kenobi_keymap) / (ENTRY_SIZE * sizeof(int)); i++) {
        int d = kenobi_keymap[i][0];
        int om = kenobi_keymap[i][1];
        for(int o = 0; o < om; o++) {
            int a = d + o;
            rgb_matrix_set_color(a, kenobi_keymap[i][2], kenobi_keymap[i][3], kenobi_keymap[i][4]);
        }
    }
    // uint8_t scale = scale8(64, rgb_matrix_config.speed);

    // for (uint8_t i = led_min; i < led_max; i++) {
    //     rgb_matrix_set_color(i, hsv_to_rgb((i * 2) + scale), hsv_to_rgb((i * 2) - scale) , hsv_to_rgb((i / 2) + scale));
    // }
  return rgb_matrix_check_finished_leds(led_max);
}
static bool KENOBI_EFFECT(effect_params_t* params) {
  if (params->init) kenobi_effect_init(params);
  return kenobi_effect_run(params);
}

static bool KENOBI_LOCKED(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 255, 0, 0);
    }
    return true;
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
