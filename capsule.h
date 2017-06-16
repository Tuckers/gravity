#include "gameDef.h"
#include "color.h"
#ifndef CAPSULE_H
#define CAPSULE_H

// CAPSULES
typedef struct Capsule {
    int width;
    int height;
    float x;
    float y;
    float velX;
    float velY;
    float driftY;
    float preDriftY;
    int maxX;
    int maxY;
    int heat;
    bool braking;
    S2D_Color *color;
    Player *player;
    S2D_Sprite *spr;
    Movement *left;
    Movement *right;
    Movement *down;
    Movement *brake;
} Capsule;

Capsule capsule1 = {
    .width = capsuleWidth,
    .height = capsuleHeight,
    .x = 0,
    .y = 0,
    .velX = 0,
    .velY = 0,
    .driftY = 0.5,
    .preDriftY = 0,
    .maxX = 20,
    .maxY = 10,
    .heat = 0,
    .braking = false,
    .player = &player1,
    .color = &green,
#ifdef ROTATE
    .left = &capRight,
    .right = &capLeft,
#else
    .left = &capLeft,
    .right = &capRight,
#endif
    .down = &capDown,
    .brake = &capBrake
};

Capsule capsule2 = {
    .width = capsuleWidth,
    .height = capsuleHeight,
    .x = nomScreenWidth,
    .y = 0,
    .velX = 0,
    .velY = 0,
    .driftY = 0.5,
    .preDriftY = 0,
    .maxX = 20,
    .maxY = 10,
    .heat = 0,
    .braking = false,
    .player = &player2,
    .color = &blue,
#ifdef ROTATE
    .left = &capRight,
    .right = &capLeft,
#else
    .left = &capLeft,
    .right = &capRight,
#endif
    .down = &capDown,
    .brake = &capBrake
};

void defineCapsuleSpr(){
    #ifdef ROTATE
        capsule1.spr = S2D_CreateSprite("cap_spr_green_v.png");
        capsule2.spr = S2D_CreateSprite("cap_spr_blue_v.png");
    #else
        capsule1.spr = S2D_CreateSprite("cap_spr_green.png");
        capsule2.spr = S2D_CreateSprite("cap_spr_blue.png");
    #endif
}

typedef struct NewCapsule {
    int width;
    int height;
    float x;
    float y;
    float rotation;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float velX;
    float velY;
    float driftY;
    float preDriftY;
    int maxX;
    int maxY;
    int maxSpeed;
    int heat;
    bool braking;
    S2D_Color *color;
    Player *player;
    S2D_Sprite *spr;
    Movement *left;
    Movement *right;
    Movement *down;
    Movement *brake;
} NewCapsule;

NewCapsule capNew = {
    .width = 60,
    .height = 100,
    .x = 100,
    .y = 100,
    .rotation = 0,
    .x1 = 100,
    .y1 = 180,
    .x2 = 140,
    .y2 = 60,
    .x3 = 60,
    .y3 = 60,
    .velX = 0,
    .velY = 0,
    .driftY = 0.5,
    .preDriftY = 0,
    .maxX = 20,
    .maxY = 10,
    .maxSpeed = 10,
    .heat = 0,
    .braking = false,
    .player = &player1,
    .color = &green,
#ifdef ROTATE
    .left = &capRight,
    .right = &capLeft,
#else
    .left = &capLeft,
    .right = &capRight,
#endif
    .down = &capDown,
    .brake = &capBrake
};

void rotateShip(NewCapsule *cap, float degrees){
    // int x1 = cap->x;
    // int x2 = cap->x + cap->width / 2;
    // int x3 = cap->x - cap->width / 2;
    // int y1 = cap->y + cap->height / 2;
    // int y2 = cap->y - cap->height / 2;
    // int y3 = cap->y - cap->height / 2;
    cap->x1 = 0 * cos(degrees) - (cap->height / 2) * sin(degrees) + cap->x;
    cap->x2 = (cap->width / 2) * cos(degrees) - (-cap->height / 2) * sin(degrees) + cap->x;
    cap->x3 = (-cap->width / 2) * cos(degrees) - (-cap->height / 2) * sin(degrees) + cap->x;
    cap->y1 = (cap->height / 2) * cos(degrees) + 0 * sin(degrees) + cap->y;
    cap->y2 = (-cap->height / 2) * cos(degrees) + (cap->width / 2) * sin(degrees) + cap->y;
    cap->y3 = (-cap->height / 2) * cos(degrees) + (-cap->width / 2) * sin(degrees) + cap->y;



    // int x1 = (cap->x1 - cap->x) * cos(degrees) - (cap->y1 - cap->y) * sin(degrees) + cap->x;
    // int y1 = (cap->y1 - cap->y) * cos(degrees) + (cap->x1 - cap->x) * sin(degrees) + cap->y;
    // cap->x1 = x1;
    // cap->y1 = y1;
    // int x2 = (cap->x2 - cap->x) * cos(degrees) - (cap->y2 - cap->y) * sin(degrees) + cap->x;
    // int y2 = (cap->y2 - cap->y) * cos(degrees) + (cap->x2 - cap->x) * sin(degrees) + cap->y;
    // cap->x2 = x2;
    // cap->y2 = y2;
    // int x3 = (cap->x3 - cap->x) * cos(degrees) - (cap->y3 - cap->y) * sin(degrees) + cap->x;
    // int y3 = (cap->y3 - cap->y) * cos(degrees) + (cap->x3 - cap->x) * sin(degrees) + cap->y;
    // cap->x3 = x3;
    // cap->y3 = y3;
}

void drawShip(NewCapsule *cap){
    S2D_DrawTriangle( // Draw outer triangle
        cap->x1,  cap->y1, cap->color->r, cap->color->g, cap->color->b, cap->color->a,
        cap->x2, cap->y2, cap->color->r, cap->color->g, cap->color->b, cap->color->a,
        cap->x3, cap->y3, cap->color->r, cap->color->g, cap->color->b, cap->color->a
    );
}

void updateShip(NewCapsule *cap){
    //Level currentLevel = game.levels[game.level];

    // Braking
    if (cap->player->left == true && cap->player->right == true){
        if (cap->braking == false){
            cap->preDriftY = cap->driftY;
            cap->braking = true;
        }
        // If braking, slow capsule and add heat
        cap->driftY = cap->driftY - 1;
        cap->heat = cap->heat + 1;
        cap->velY = cap->velY - 0.1;
        if (cap->heat > 100){
            cap->heat = 100;
        }
        if (cap->driftY < -cap->maxY){
            cap->driftY = -cap->maxY;
        }
        if (cap->velY < 0){
            cap->velY = 0;
        }
    }
    else {
        // If not braking, resume previous speed and reduce heat
        cap->braking = false;
        cap->heat--;
        cap->velY = cap->velY + 0.01;
        if (cap->heat < 0){
            cap->heat = 0;
        }
        if (cap->driftY < cap->preDriftY){
            cap->driftY = cap->driftY + 0.5;
        }
        if (cap->velY > cap->maxSpeed){
            cap->velY = 10;
        }
    }
    // Invert player movement if vertical orientation
    // Update capsule velocity based on player input
    #ifdef ROTATE
        if (cap->player->right == true){
            cap->velX = cap->velX - 1;
            if (cap->velX < -cap->maxX){
                cap->velX = -cap->maxX;
            }
        }
        if (cap->player->left == true){
            cap->velX = cap->velX + 1;
            if (cap->velX > cap->maxX){
                cap->velX = cap->maxX;
            }
        }
    // Update capsule velocity based on player input
    #else
        if (cap->player->right == true){
            cap->velX = cap->velX + 1;
            if (cap->velX > cap->maxX){
                cap->velX = cap->maxX;
            }
        }
        if (cap->player->left == true){
            cap->velX = cap->velX - 1;
            if (cap->velX < -cap->maxX){
                cap->velX = -cap->maxX;
            }
        }
    #endif
    // Add friction quotiant to slow movement
    cap->velX *= friction;
    // Temp variables to hold velocity + current location
    float x = cap->x + cap->velX;
    float y = cap->y + cap->driftY;
    // If new x is outside field of play, bring it in, kill excess velocity (improves responsiveness)
    if ((x + cap->width) > nomScreenWidth){
        x = nomScreenWidth - cap->width;
        cap->velX = 0;
    }
    else if (x < 0) {
        x = 0;
        cap->velX = 0;
    }
    // If new y is outside field of play, bring it in.
    if ((y + cap->height) > nomScreenHeight - 500){
        y = nomScreenHeight - cap->height - 500;
    }
    else if (y < 100) {
        y = 100;
    }
    // Update capsule values to reflect temp values
    cap->x = x;
    cap->y = y;
    cap->x1 = cap->x;
    cap->x2 = cap->x + cap->width / 2;
    cap->x3 = cap->x - cap->width / 2;
    cap->y1 = cap->y + cap->height / 2;
    cap->y2 = cap->y - cap->height / 2;
    cap->y3 = cap->y - cap->height / 2;

    // If velocity is close to zero, make it zero.
    if (cap->velX < 0.1 && cap->velX > -0.1){
        cap->velX = 0;
    }
    rotateShip(cap, (-cap->velX / 50));
}



#endif /* CAPSULE_H */
