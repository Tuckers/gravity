#include "gameDef.h"
#include "color.h"
#ifndef BKG_H
#define BKG_H

////// BACKGROUND //////

S2D_Color black = {.r = 0.0, .g = 0.0, .b = 0.0, .a = 1.0};
//S2D_Color darkBlue = {.r = 0.1216,.g = 0.4157,.b = 0.6588};

typedef struct BKG {
    S2D_Color *color1;
    S2D_Color *color2;
} BKG;

BKG background = {
    .color1 = &black,
    .color2 = &darkBlue
};

void updateBKG(BKG *bkg){
    bkg->color1->r += .0001;
    bkg->color1->g += .0002;
    bkg->color1->b += .0003;

    bkg->color2->r += .0001;
    bkg->color2->g += .0001;
    bkg->color2->b += .0001;
}

void drawBKG(BKG *bkg){
    #ifdef ROTATE
        int height = nomScreenWidth;
        int width = nomScreenHeight;
    #else
        int width = nomScreenWidth;
        int height = nomScreenHeight;
    #endif
    int x = 0;
    int y = 0;
    S2D_Color *color1 = bkg->color2;
    S2D_Color *color2 = bkg->color1;
    S2D_DrawQuad(
        // Upper left
        x, y, color1->r, color1->g, color1->b, color1->a,
        // Upper right
        (x + width), y, color1->r, color1->g, color1->b, color1->a,
        // Lower right
        (x + width), (y + height), color2->r, color2->g, color2->b, color2->a,
        // Lower left
        x, (y + height), color2->r, color2->g, color2->b, color2->a
    );
}

#endif /* BKG_H */
