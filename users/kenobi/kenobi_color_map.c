#include "kenobi_color_map.h"

uint8_t *kenobi_color_map_add_color(int amplifier, uint8_t color[3]) {
    uint8_t *colors = (uint8_t *)malloc(3 * sizeof(uint8_t));
  uint8_t max = 255;
  for (uint8_t i = 0; i < 3; i++) {
    colors[i] = color[i] + amplifier > max ? 255 : color[i] + amplifier;
  }
  return colors;
}

void kenobi_color_map_initialize(void) {
    kenobi_color_map[0][0] = kenobi_color_map[0][0];
    for(int i = 0; i < (sizeof(kenobi_color_map) / 3); i++) {
        uint8_t base[3] = {kenobi_color_map[i][0], kenobi_color_map[i][1], kenobi_color_map[i][2]};
        uint8_t *normalized = kenobi_color_map_add_color(100, base);
        kenobi_color_caps_map[i][0] = normalized[0];
        kenobi_color_caps_map[i][1] = normalized[1];
        kenobi_color_caps_map[i][2] = normalized[2];
    }
}