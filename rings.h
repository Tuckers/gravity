#include "gameDef.h"
#include "color.h"
#ifndef RINGS_H
#define RINGS_H

// RINGMASTER

int playerHeight = 100;

typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    int split;
    int gap;
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
    int gapSize;
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
    .acceleration = .001,
    .gapSize = 200
};

void generateRings(Ringmaster *rm){
    for (int i = 0; i <= 12; i++){
        ringList[i].x = 0;
        ringList[i].y = nomScreenHeight;
        ringList[i].width = nomScreenWidth;
        ringList[i].height = 180;
        ringList[i].color = &ringColor;
        ringList[i].velY = 1;
        ringList[i].split = (rand() % ((nomScreenWidth - rm->gapSize) + 1 ) + (rm->gapSize / 2));
        ringList[i].gap = 0;
        rm->rings[i] = &ringList[i];
    }
}

void reorderRingArray(Ringmaster *rm){
    Ring *ring = rm->rings[0];
    ring->y = nomScreenHeight;
    ring->height = 200;
    ring->velY = 0.1;
    ring->split = (rand() % ((nomScreenWidth - rm->gapSize) + 1 ) + (rm->gapSize/ 2));
    ring->gap = 0;
    for (int i = 0; i < rm->numRings; i++){
        rm->rings[i] = rm->rings[i+1];
    }
    rm->rings[rm->numRings] = ring;
}

void updateRingmaster(Ringmaster *rm){
    rm->count++; //Count between launches
    if (rm->active <= rm->numRings  && rm->count > 60){ //When to launch new rings
        rm->active++;
        rm->count = 0;
    }
    for(int i = 0; i <= rm->active; i++){ // Cycle through all active rings
        Ring *ring = rm->rings[i];
        if (ring->y < nomScreenHeight - 400 && ring->gap < rm->gapSize){
            ring->gap += 4;
        }
        if (ring->velY < rm->maxY){
            ring->velY += (nomScreenHeight - (ring->y)) * rm->acceleration;
            //ring->velY = rm->maxY * 1 - ((ring->y) / nomScreenHeight); // Accelerate speed
        }
        if (ring->height > 4){
            ring->height = 200 * (ring->y - 1000) / nomScreenHeight; //Decrease height
        }
        ring->y -= ring->velY; //Apply speed to Y value
        if (ring->y < playerHeight){ //Do this when you hit the top
            reorderRingArray(rm);
            rm->active--;
        }
    }
}

void drawRing(Ring *ring){
    int x = ring->x;
    int x2 = ring->split + ring->gap / 2;
    int y = ring->y;
    int width = ring->split - ring->gap / 2;
    int width2 = ring->width - (ring->split + ring->gap / 2);
    int height = ring->height;
    int width3 = ring->gap;
    int x3 = ring->split - ring->gap / 2;
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
    S2D_DrawQuad(
        // Upper left
        x2, y, color->r, color->g, color->b, color->a,
        // Upper right
        (x2 + width2), y, color->r, color->g, color->b, color->a,
        // Lower right
        (x2 + width2), (y + height), color->r, color->g, color->b, color->a,
        // Lower left
        x2, (y + height), color->r, color->g, color->b, color->a
    );
    S2D_DrawQuad(
        // Upper left
        x3, y, 1, 1, 1, 1,
        // Upper right
        (x3 + width3), y, 1, 1, 1, 1,
        // Lower right
        (x3 + width3), (y + height), 1, 1, 1, 1,
        // Lower left
        x3, (y + height), 1, 1, 1, 1
    );
}

void drawRingmaster(Ringmaster *rm){
    for(int i = 0; i <= rm->numRings; i++){
        drawRing(rm->rings[i]);
    }
}


///// OLD RINGSMASTER /////


// void randomizeRings (Ringmaster *ringmaster){
//     // Set an initial random X val for each ring.
//     ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
//     ringmaster->two->x = rand() % (nomScreenWidth - ringWidth) + 1;
//     ringmaster->three->x = rand() % (nomScreenWidth - ringWidth) + 1;
//     ringmaster->four->x = rand() % (nomScreenWidth - ringWidth) + 1;
//     ringmaster->five->x = rand() % (nomScreenWidth - ringWidth) + 1;
//     ringmaster->randomized = true;
// }

// void checkHit (Ringmaster *ringmaster){
//     // Define hit targets
//     int ringX = ringmaster->one->x;
//     int ringMax = ringX + ringmaster->one->width;
//     int capX = ringmaster->capsule->x;
//     int capMax = capX + ringmaster->capsule->width;
//     // Check for hits
//     if (ringX < capX && capMax < ringMax){
//         ringmaster->capsule->player->score += 100;
//         printf("HIT! Player score: %d\n", ringmaster->capsule->player->score);
//         ringmaster->rings--;
//         ringmaster->one->y = nomScreenHeight;
//         ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
//         reorderRings(ringmaster);
//     }
//     else {
//         ringmaster->capsule->heat += 60;
//         printf("MISS! Capsule heat: %d\n", ringmaster->capsule->heat);
//         ringmaster->rings--;
//         ringmaster->one->y = nomScreenHeight;
//         ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
//         reorderRings(ringmaster);
//     }
// }


// Update function for ring tracking
// void updateRingmaster(Ringmaster *ringmaster){
//     ringmaster->velY = ringmaster->capsule->velY;
//     int playArea = nomScreenHeight - ringmaster->capsule->y - ringmaster->capsule->height;
//     int ringCheckpoint = nomScreenHeight - playArea - ringHeight;
//     // Randomize ring starting X vals
//     if (ringmaster->randomized == false){
//         randomizeRings(ringmaster);
//     }
//     if (ringmaster->one->y < ringCheckpoint){
//         checkHit(ringmaster);
//     }
//
//
//     // Case switch for number of rings on display.
//     switch (ringmaster->rings){
//         case 0:
//             ringmaster->rings = 1;
//         case 1:
//             if (ringmaster->one->y < (nomScreenHeight - ringmaster->seperation)){
//                 ringmaster->rings = 2;
//             }
//             break;
//         case 2:
//             if (ringmaster->two->y < (nomScreenHeight - ringmaster->seperation)){
//                 ringmaster->rings = 3;
//             }
//             break;
//         case 3:
//             if (ringmaster->three->y < ringCheckpoint){
//                 ringmaster->rings = 4;
//             }
//             break;
//         case 4:
//             if (ringmaster->four->y < ringCheckpoint){
//                 ringmaster->rings = 5;
//             }
//             break;
//         case 5:
//             if (ringmaster->five->y < (nomScreenHeight - ringmaster->seperation)){
//                 ringmaster->rings = 5;
//             }
//             break;
//     }
// }

// void drawRingmaster (Ringmaster *ringmaster){
//     switch (ringmaster->rings) {
//         case 1:
//             if (ringmaster->delay == true){
//                 ringmaster->count++;
//                 if (ringmaster->count >= 50){
//                     ringmaster->delay = false;
//                 }
//             }
//             else {
//                 ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
//                 drawRing(ringmaster->one);
//             }
//             //printf("Drawing one ring\n");
//             //printf("Ring one Y: %d\n", ringmaster->one->y);
//             break;
//         case 2:
//             //printf("Drawing two rings\n");
//             //printf("Ring one Y: %d\n", ringmaster->one->y);
//             ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
//             ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
//             drawRing(ringmaster->one);
//             drawRing(ringmaster->two);
//             break;
//         case 3:
//             //printf("Drawing three rings\n");
//             //printf("Ring one Y: %d\n", ringmaster->one->y);
//             ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
//             ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
//             ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
//             drawRing(ringmaster->one);
//             drawRing(ringmaster->two);
//             drawRing(ringmaster->three);
//             break;
//         case 4:
//             //printf("Drawing three rings\n");
//             //printf("Ring one Y: %d\n", ringmaster->one->y);
//             ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
//             ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
//             ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
//             ringmaster->four->y = ringmaster->four->y - ringmaster->velY;
//             drawRing(ringmaster->one);
//             drawRing(ringmaster->two);
//             drawRing(ringmaster->three);
//             drawRing(ringmaster->four);
//             break;
//         case 5:
//             //printf("Drawing three rings\n");
//             //printf("Ring one Y: %d\n", ringmaster->one->y);
//             ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
//             ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
//             ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
//             ringmaster->four->y = ringmaster->four->y - ringmaster->velY;
//             ringmaster->five->y = ringmaster->five->y - ringmaster->velY;
//             drawRing(ringmaster->one);
//             drawRing(ringmaster->two);
//             drawRing(ringmaster->three);
//             drawRing(ringmaster->four);
//             drawRing(ringmaster->five);
//             break;
//     }
//
// }

#endif /* RINGS_H */
