#include "gameDef.h"
#include "color.h"
#ifndef RINGS_H
#define RINGS_H

// RINGMASTER

typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    float velY;
    S2D_Color *color;
} Ring;

typedef struct Ringmaster {
    struct Ring *rings[13];
    int numRings;
    int topRing;
    int active;
    int maxY;
    int seperation;
    bool delay;
    int count;
    bool randomized;
    float acceleration;
} Ringmaster;

Ring ringList[13];

Ringmaster rm1 = {
    .numRings = 12,
    .active = 0,
    .topRing = 0,
    .maxY = 15,
    .seperation = 600,
    .delay = false,
    .count = 0,
    .randomized = false,
    .acceleration = .001
};

void generateRings(Ringmaster *rm){
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

void reorderRingArray(Ringmaster *rm){
    Ring *ringTemp;
    ringTemp = rm->rings[0];
    ringTemp->y = nomScreenHeight;
    ringTemp->height = 300;
    ringTemp->velY = 0.1;
    for (int i = 0; i < rm->numRings; i++){
        rm->rings[i] = rm->rings[i+1];
    }
    rm->rings[rm->numRings] = ringTemp;
}

void updateRingmaster(Ringmaster *rm){
    rm->count++; //Count between launches
    if (rm->active <= rm->numRings  && rm->count > 60){ //When to launch new rings
        rm->active++;
        rm->count = 0;
    }
    for(int i = 0; i <= rm->active; i++){ // Cycle through all active rings
        Ring *ring = rm->rings[i];
        if (ring->velY < rm->maxY){
            ring->velY += (nomScreenHeight - (ring->y)) * rm->acceleration;
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

void drawRing(Ring *ring){
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

void drawRingmaster(Ringmaster *rm){
    for(int i = 0; i <= rm->numRings; i++){
        drawRing(rm->rings[i]);
    }
}

#endif /* RINGS_H */
