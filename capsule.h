#include "gameDef.h"
#include "color.h"
#ifndef CAPSULE_H
#define CAPSULE_H


int capPoints[6][2] = {
    {-20,-30}, {20,-30}, {0,30}, {-15,-26}, {15,-26}, {0,19}
};

int capTransPoints[6][2] = {
    {-20,-30}, {20,-30}, {0,30}, {-15,-26}, {15,-26}, {0,19}
};

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
    bool passNose;
    bool passMid;
    bool passTail;
    int (*points)[2];
    int (*transPoints)[2];
    S2D_Color *color;
    Player *player;
    S2D_Sprite *spr;
    Movement *left;
    Movement *right;
    Movement *down;
    Movement *brake;
} NewCapsule;

NewCapsule capNew = {
    .width = 40,
    .height = 60,
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
    .points = capPoints,
    .transPoints = capTransPoints,
    .player = &player1,
    .color = &white,
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


typedef struct Point{
    int x;
    int y;
} Point;

Point vector(Point a, Point b){
    Point c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

int crossProduct(Point a, Point b){
    int product = a.x * b.y - b.x * a.y;
    return product;
}

int dotProduct(Point a, Point b){
    int product = a.x * b.x + a.y * b.y;
    return product;
}

bool sameSide(Point p, Point a, Point b, Point c){
    int cp1 = crossProduct(vector(b,a),vector(p,a));
    int cp2 = crossProduct(vector(b,a),vector(c,a));
    if (cp1 * cp2 >= 0){
        return true;
    }
    else {
        return false;
    }
}

bool triCollide(Point p1, Point p2, Point p3, Point a, Point b, Point c){
    bool check1;
    bool check2;
    bool check3;
    if (sameSide(p1, a, b, c) && sameSide(p1,b,a,c) && sameSide(p1,c,a,b)){
        check1 = true;
    }
    else {
        check1 = false;
    }
    return true;
}

void rotateShip(NewCapsule *cap, float degrees){
    ///// HOLLOW RENDERING /////
    for (int i = 0; i < 6; i++){
        cap->transPoints[i][0] = cap->points[i][0] * cos(degrees) - cap->points[i][1] * sin(degrees) + cap->x + 100;
        cap->transPoints[i][1] = cap->points[i][1] * cos(degrees) + cap->points[i][0] * sin(degrees) + cap->y + 100;
    }

    ///// SOLID RENDERING /////
    cap->x1 = 0 * cos(degrees) - (cap->height / 2) * sin(degrees) + cap->x;
    cap->x2 = (cap->width / 2) * cos(degrees) - (-cap->height / 2) * sin(degrees) + cap->x;
    cap->x3 = (-cap->width / 2) * cos(degrees) - (-cap->height / 2) * sin(degrees) + cap->x;
    cap->y1 = (cap->height / 2) * cos(degrees) + 0 * sin(degrees) + cap->y;
    cap->y2 = (-cap->height / 2) * cos(degrees) + (cap->width / 2) * sin(degrees) + cap->y;
    cap->y3 = (-cap->height / 2) * cos(degrees) + (-cap->width / 2) * sin(degrees) + cap->y;
}


void drawTriangle(int v1[2], int v2[2], int v3[2], S2D_Color *color){
    S2D_DrawTriangle(
        v1[0], v1[1], color->r, color->g, color->b, color->a,
        v2[0], v2[1], color->r, color->g, color->b, color->a,
        v3[0], v3[1], color->r, color->g, color->b, color->a
    );
}


void drawShip(NewCapsule *cap){
    ///// HOLLOW RENDERING /////
    int v1[2], v2[2], v3[2], v4[2], v5[2], v6[2];
    for (int i = 0; i < 2; i++){
        v1[i] = cap->transPoints[0][i];
        v2[i] = cap->transPoints[1][i];
        v3[i] = cap->transPoints[2][i];
        v4[i] = cap->transPoints[3][i];
        v5[i] = cap->transPoints[4][i];
        v6[i] = cap->transPoints[5][i];
    }

    drawTriangle(v1, v2, v4, cap->color);
    drawTriangle(v2, v4, v5, cap->color);
    drawTriangle(v2, v5, v3, cap->color);
    drawTriangle(v1, v4, v3, cap->color);
    drawTriangle(v4, v6, v3, cap->color);
    drawTriangle(v5, v6, v3, cap->color);

    ///// SOLID RENDERING /////
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
            braking = true;
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
        braking = false;
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
