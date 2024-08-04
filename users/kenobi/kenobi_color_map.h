
#ifndef KENOBI_COLOR_MAP_H
#define KENOBI_COLOR_MAP_H

#include <stdlib.h>
#include "color.h"


// THIS GETS USED! GO HOME CLANGD, YOU'RE DRUNK!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static uint8_t kenobi_color_map[108][3] = {
{RGB_RED}, {RGB_ORANGE}, {RGB_ORANGE}, {RGB_ORANGE}, {RGB_ORANGE}, {RGB_PINK}, {RGB_PINK}, {RGB_ORANGE}, {RGB_ORANGE}, {RGB_PINK}, {RGB_PINK}, {RGB_GREEN}, {RGB_YELLOW}, {RGB_GREEN}, {RGB_GOLDENROD}, {RGB_AZURE}, {RGB_CHARTREUSE}, {RGB_CORAL}, {RGB_WHITE}, {RGB_RED },
{RGB_TEAL}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_CYAN}, {RGB_MAGENTA}, {RGB_SPRINGGREEN}, {RGB_GOLD}, {RGB_GOLD}, {RGB_GOLD}, {RGB_CYAN}, {RGB_GOLD}, {RGB_GREEN}, {RGB_TURQUOISE},
{RGB_ORANGE}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_GREEN}, {RGB_GREEN}, {RGB_GREEN}, {RGB_GOLD}, {RGB_GOLD}, {RGB_GOLD}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_GREEN},
{RGB_ORANGE}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_CYAN}, {RGB_RED}, {RGB_RED}, {RGB_CYAN}, {RGB_RED}, {RGB_RED}, {RGB_GREEN}, {RGB_GREEN},  {RGB_ORANGE},    {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, 
{RGB_ORANGE},  {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_RED}, {RGB_GREEN}, {RGB_GREEN}, {RGB_GREEN},  {RGB_ORANGE},  {RGB_TEAL},  {RGB_PURPLE}, {RGB_PURPLE}, {RGB_PURPLE}, {RGB_GOLD},
{RGB_TEAL}, {RGB_YELLOW}, {RGB_MAGENTA},    {RGB_CORAL},    {RGB_MAGENTA}, {RGB_YELLOW}, {RGB_PINK}, {RGB_TEAL}, {RGB_GREEN}, {RGB_GREEN}, {RGB_GREEN}, {RGB_PURPLE},  {RGB_GOLD}};

static uint8_t kenobi_color_caps_map[108][3] = {};


uint8_t *kenobi_color_map_add_color(int amplifier, uint8_t color[3]);

extern void kenobi_color_map_initialize(void);

#pragma GCC diagnostic pop

#endif