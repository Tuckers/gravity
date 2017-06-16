#include "gameDef.h"

// RINGMASTER

typedef struct Ring2 {
    int x;
    int y;
    int width;
    int height;
    float velY;
    S2D_Color *color;
} Ring2;

typedef struct RM {
    struct Ring2 *rings[13];
    int numRings;
    int topRing;
    int active;
    int maxY;
    int seperation;
    bool delay;
    int count;
    bool randomized;
    S2D_Color *color;
} RM;

Ring2 ringList[13];

RM rm1 = {
    .numRings = 12,
    .active = 0,
    .topRing = 0,
    .maxY = 15,
    .seperation = 600,
    .delay = false,
    .count = 0,
    .randomized = false,
};



S2D_Color ringColor = {.r = 1.0, .g = 0.0, .b = 0.0, .a = 1.0};

void generateRings(RM *rm){
    for (int i = 0; i <= 12; i++){
        ringList[i].x = 0;
        ringList[i].y = nomScreenHeight;
        ringList[i].width = nomScreenWidth;
        ringList[i].height = 180;
        ringList[i].color = &ringColor;
        ringList[i].velY = 1;
        rm->rings[i] = &ringList[i];

    }
}


/*
count++
	if count > 30
		createRing()
		count = 0
	for (ringmaster->one, index in rings
		if velY < speedY
			velY = speedY * -(ring.y - 1920) / 1920
		if ring.y > playerY and ring.height > 4
			ring.height = 180 * (ring.y) / 1920
		ring.y -= velY
		if ring.y < 0
			destroyRing(ring, "hit")
*/

void reorderRingArray(RM *rm){
    Ring2 *ringTemp;
    ringTemp = rm->rings[0];
    ringTemp->y = nomScreenHeight;
    ringTemp->height = 300;
    ringTemp->velY = 0.1;
    for (int i = 0; i < rm->numRings; i++){
        rm->rings[i] = rm->rings[i+1];
    }
    rm->rings[rm->numRings] = ringTemp;
}

float acceleration = 0.001;

void updateRM(RM *rm){
    rm->count++; //Count between launches
    if (rm->active <= rm->numRings  && rm->count > 60){ //When to launch new rings
        rm->active++;
        rm->count = 0;
    }
    for(int i = 0; i <= rm->active; i++){ // Cycle through all active rings
        Ring2 *ring = rm->rings[i];
        if (ring->velY < rm->maxY){
            ring->velY += (nomScreenHeight - (ring->y)) * acceleration;
            //ring->velY = rm->maxY * 1 - ((ring->y) / nomScreenHeight); // Accelerate speed
        }
        if (ring->height > 4){
            ring->height = 300 * (ring->y - 600) / nomScreenHeight; //Decrease height
        }
        ring->y -= ring->velY; //Apply speed to Y value
        if (ring->y < 0){ //Do this when you hit the top
            reorderRingArray(rm);
            rm->active--;
        }
    }
}


void drawRing2(Ring2 *ring){
    int x = ring->x;
    int y = ring->y;
    int width = ring->width;
    int height = ring->height;
    S2D_Color *color = ring->color;
    S2D_DrawQuad(
        // Upper left
        x, y, color->r, color->g, color->b, color->a,
        // Upper right
        (x + width), y, color->r, color->g, color->b, color->a,
        // Lower right
        (x + width), (y + height), color->r, color->g, color->b, color->a,
        // Lower left
        x, (y + height), color->r, color->g, color->b, color->a
    );
}

void drawRM(RM *rm){
    for(int i = 0; i <= rm->numRings; i++){
        drawRing2(rm->rings[i]);
    }
}

Ring2 ringTest = {
    .x = 0,
    .y = nomScreenHeight,
    .width = nomScreenWidth,
    .height = 180,
    .color = &ringColor
};

void drawRingDemo(RM *rm, Ring2 *ring){
    if (ring->velY < rm->maxY){
        ring->velY = rm->maxY * (1 - ring->y / nomScreenHeight);
    }
    if (ring->height > 4){
        ring->height = 180 * (ring->y - 1000) / (nomScreenHeight);
    }
    ring->y -= ring->velY;
    if (ring->y < 0){
        ring->y = nomScreenHeight;
        ring->height = 180;
    }
    drawRing2(ring);
}

////// BACKGROUND //////

S2D_Color black = {.r = 0.0, .g = 0.0, .b = 0.0, .a = 1.0};
S2D_Color darkBlue = {.r = 0.1216,.g = 0.4157,.b = 0.6588};

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
