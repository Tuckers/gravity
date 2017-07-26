#include "gameDef.h"
#ifndef COLOR_H
#define COLOR_H

////////// COLOR DEFINITIONS //////////
S2D_Color gray = {.r = 0.5, .g = 0.5, .b = 0.5, .a = 1.0};
S2D_Color green = {.r = 0.0, .g = 1.0, .b = 0.0, .a = 1.0};
S2D_Color red = {.r = 1.0, .g = 0.0, .b = 0.0, .a = 1.0};
S2D_Color white = {.r = 1.0, .g = 1.0, .b = 1.0, .a = 1.0};
S2D_Color blue = {.r = 0.0, .g = 0.8, .b = 0.988, .a = 1.0};
S2D_Color blue2 = {.r = 0.0, .g = 0.5058, .b = 0.6431, .a = 1.0};
S2D_Color blue3 = {.r = 0.5843, .g = 0.8784, .b = 0.9647, .a = 1.0};
S2D_Color yellow = {.r = 0.9607, .g = 0.9019, .b = 0.0, .a = 1.0};
S2D_Color ringColor = {.r = 1.0, .g = 0.0, .b = 0.0, .a = 1.0};
S2D_Color darkBlue = {.r = 0.0509, .g = 0.1490, .b = 0.2667, .a = 1.0};
S2D_Color lightBlue;
S2D_Color lightGreen;

void convertColor(S2D_Color *color, float red, float green, float blue) {
    color->r = red / 255;
    color->g = green / 255;
    color->b = blue / 255;
    color->a = 1.0;
}

void defineColors(){
    // Use convert color to define colors using regular RGB values
    convertColor(&lightBlue, 115, 179, 249);
    convertColor(&lightGreen, 147, 229, 115);
}

S2D_Color* mixColor(S2D_Color *colorOne, S2D_Color *colorTwo, int balance){
    S2D_Color *color;
    color->r = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->g = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->b = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->a = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    return color;
}

#endif /* COLOR_H */
