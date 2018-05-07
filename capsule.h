#include "gameDef.h"
#include "color.h"
#include "drawing.h"
#include "particle.h"
#ifndef CAPSULE_H
#define CAPSULE_H

typedef struct Ship {
    Point (*shipPoints);
    int shipSize;
    float speed;
    float shield;
    float control;
    Animation *title;
    Animation *big;
} Ship;

typedef struct Capsule {
    int width;
    int height;
    float x;
    float y;
    float rotation;
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
    bool hollow;
    int shipSize;
    Ship *ship;
    struct Point *points[10];
    struct Point *transPoints[10];
    S2D_Color *color;
    Player *player;
    S2D_Sprite *spr;
    Movement *left;
    Movement *right;
    Movement *down;
    Movement *brake;
} Capsule;

Capsule capsule1 = {
    .width = 50,
    .height = 60,
    .x = 0,
    .y = 0,
    .rotation = 0,
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

Capsule capsule2 = {
    .width = 50,
    .height = 60,
    .x = nomScreenWidth - 100,
    .y = 100,
    .rotation = 0,
    .velX = 0,
    .velY = 0,
    .driftY = 0.5,
    .preDriftY = 0,
    .maxX = 20,
    .maxY = 10,
    .maxSpeed = 10,
    .heat = 0,
    .braking = false,
    .player = &player2,
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

///// SHIPS /////

Point shipOne[6] = {
    {.x = -25, .y = -30}, {.x = 25, .y = -30}, {.x = 0, .y = 30},
    {.x = -18, .y = -26}, {.x = 18, .y = -26}, {.x = 0, .y = 17}
};

Point shipTwo[10] = {
    {.x = -17, .y = -30}, {.x = 17, .y = -30}, {.x = 25, .y = -20}, {.x = 0, .y = 30}, {.x = -25, .y = -20},
    {.x = -15, .y = -25}, {.x = 15, .y = -25}, {.x = 19, .y = -20}, {.x = 0, .y = 19}, {.x = -19, .y = -20}
};

Point shipThree[10] = {
    {.x = -16, .y = -30}, {.x = 16, .y = -30}, {.x = 23, .y = 16}, {.x = 0, .y = 30}, {.x = -23, .y = 16},
    {.x = -12, .y = -25}, {.x = 12, .y = -25}, {.x = 18, .y = 14}, {.x = 0, .y = 24}, {.x = -18, .y = 14}
};

Point shipFour[10] = {
    {.x = -11, .y = -30}, {.x = 11, .y = -30}, {.x = 25, .y = 4}, {.x = 0, .y = 30}, {.x = -25, .y = 4},
    {.x = -8, .y = -25}, {.x = 8, .y = -25}, {.x = 19, .y = 3}, {.x = 0, .y = 23}, {.x = -19, .y = 3}
};

Point shipFive[10] = {
    {.x = -20, .y = -30}, {.x = 20, .y = -30}, {.x = 20, .y = 0}, {.x = 0, .y = 30}, {.x = -20, .y = 0},
    {.x = -15, .y = -25}, {.x = 15, .y = -25}, {.x = 15, .y = -2}, {.x = 0, .y = 21}, {.x = -15, .y = -2}
};

Ship ship1 = {
    .shipPoints = shipOne,
    .shipSize = 6,
    .speed = 1,
    .shield = .3,
    .control = .6,
    .title = &shipSquall,
    .big = &bgShip1
};

Ship ship2 = {
    .shipPoints = shipTwo,
    .shipSize = 10,
    .speed = .7,
    .shield = .4,
    .control = .8,
    .title = &shipTempest,
    .big = &bgShip2
};

Ship ship3 = {
    .shipPoints = shipThree,
    .shipSize = 10,
    .speed = .2,
    .shield = 1,
    .control = .5,
    .title = &shipBlizzard,
    .big = &bgShip3
};

Ship ship4 = {
    .shipPoints = shipFour,
    .shipSize = 10,
    .speed = .3,
    .shield = .6,
    .control = 1,
    .title = &shipTyphoon,
    .big = &bgShip4
};

Ship ship5 = {
    .shipPoints = shipFive,
    .shipSize = 10,
    .speed = .6,
    .shield = .5,
    .control = .5,
    .title = &shipHurricane,
    .big = &bgShip5
};

///// SHIP STORAGE /////

Point cpA1[10];
Point cpT1[10];
Point cpA2[10];
Point cpT2[10];

void generateCapPoints(Capsule *cap, Point cpArray[10], Point cpTransArray[10], int shipSize, bool hollow){
    //Point shipPoints[10] = cap->ship->shipPoints;
    for (int i=0; i<shipSize; i++){
        cpArray[i] = cap->ship->shipPoints[i];
        cpTransArray[i] = cap->ship->shipPoints[i];
        cap->points[i] = &cpArray[i];
        cap->transPoints[i] = &cpTransArray[i];
        cap->shipSize = shipSize;
        cap->hollow = hollow;
    }
}

///// TRIANGLE COLLISION MATH /////

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
    if (sameSide(p2, a, b, c) && sameSide(p2,b,a,c) && sameSide(p2,c,a,b)){
        check2 = true;
    }
    else {
        check2 = false;
    }
    if (sameSide(p3, a, b, c) && sameSide(p3,b,a,c) && sameSide(p3,c,a,b)){
        check3 = true;
    }
    else {
        check3 = false;
    }
    if (check1 || check2 || check3){
        return true;
    }
    else{
        return false;
    }

}

///// SHIP MOVEMENT /////

void rotateShip(Capsule *cap, float degrees){

    ///// HOLLOW RENDERING /////
    //int shipSize = sizeof(cap->points) / sizeof(cap->points[0]);
    int shipSize = cap->shipSize;
    for (int i = 0; i < shipSize; i++){
        //printf("Capsule pointsValue %d.x = %d \n", i, cap->points[i]->x);
         cap->transPoints[i]->x = cap->points[i]->x * cos(degrees) - cap->points[i]->y * sin(degrees) + cap->x + 25;
         cap->transPoints[i]->y = cap->points[i]->y * cos(degrees) + cap->points[i]->x * sin(degrees) + cap->y + 25;
    }
}

void drawShip(Capsule *cap){
    int shipSize = cap->shipSize / 2;
    if (cap->heat == 100){
        drawParticles(&kaboom);
    }
    else {
        if (cap->hollow == true){
            ///// HOLLOW RENDERING /////
            for (int i = 0; i < shipSize; i++){
                if (i == shipSize - 1){
                    drawTriangle(cap->transPoints[i], cap->transPoints[0], cap->transPoints[(i + shipSize)], cap->color);
                    drawTriangle(cap->transPoints[(i + shipSize)], cap->transPoints[0], cap->transPoints[(0 + shipSize)], cap->color);
                }
                else {
                    drawTriangle(cap->transPoints[i], cap->transPoints[(i + 1)], cap->transPoints[(i + shipSize)], cap->color);
                    drawTriangle(cap->transPoints[(i + shipSize)], cap->transPoints[(i + 1)], cap->transPoints[(i + 1 + shipSize)], cap->color);
                }
            }
        }
        else {
            ///// SOLID RENDERING /////
            if (shipSize == 3){
                drawTriangle(cap->transPoints[0], cap->transPoints[1], cap->transPoints[2], cap->color);
            }
            else {
                drawTriangle(cap->transPoints[4], cap->transPoints[2], cap->transPoints[3], cap->color);
                drawQuad(cap->transPoints[0], cap->transPoints[1], cap->transPoints[2], cap->transPoints[4], cap->color);
            }
        }
    }
}

void updateShip(Capsule *cap){
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
        cap->heat += 1;
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
    if ((y + 30) > nomScreenHeight - 500){
        y = nomScreenHeight - 30 - 500;
    }
    else if (y < 100) {
        y = 100;
    }
    // // Update capsule values to reflect location values
    cap->x = x;
    cap->y = y;

    // If velocity is close to zero, make it zero.
    if (cap->velX < 0.1 && cap->velX > -0.1){
        cap->velX = 0;
    }
    rotateShip(cap, (-cap->velX / 50));
}

#endif /* CAPSULE_H */
