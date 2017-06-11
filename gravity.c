#include <simple2d.h>
#include <sys/time.h>
#include "sprites.h"
#include "gameDef.h"



S2D_Window *window;


////////// GLOBAL VARIABLES //////////
bool running = true;
bool setupDefined = false;
float friction = 0.98;
float entropy = 0.8;

#ifdef ROTATE
    int screenHeight = 1080;
    int screenWidth = 1920;
    int orientation = 1;
#else
    int screenHeight = 1920;
    int screenWidth = 1080;
    int orientation = 0;
#endif


////////// COLOR DEFINITIONS //////////
S2D_Color gray = {.r = 0.5, .g = 0.5, .b = 0.5, .a = 1.0};
S2D_Color green = {.r = 0.0, .g = 1.0, .b = 0.0, .a = 1.0};
S2D_Color red = {.r = 1.0, .g = 0.0, .b = 0.0, .a = 1.0};
S2D_Color black = {.r = 0.0, .g = 0.0, .b = 0.0, .a = 1.0};
S2D_Color white = {.r = 1.0, .g = 1.0, .b = 1.0, .a = 1.0};
S2D_Color blue = {.r = 0.0, .g = 0.0, .b = 1.0, .a = 1.0};
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


// SPRITES
typedef struct Movement {
    int frames;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int startingX;
    int startingY;
} Movement;

Movement capDown= {
    .frames = 30,
    .currentFrame = 0,
    .frameWidth = 50,
    .frameHeight = 50,
    .startingX = 0,
    .startingY = 300
};

Movement capLeft = {
    .frames = 30,
    .currentFrame = 0,
    .frameWidth = 100,
    .frameHeight = 100,
    .startingX = 0,
    .startingY = 0
};

Movement capRight = {
    .frames = 30,
    .currentFrame = 0,
    .frameWidth = 100,
    .frameHeight = 100,
    .startingX = 0,
    .startingY = 200
};

Movement capBrake = {
    .frames = 30,
    .currentFrame = 0,
    .frameWidth = 100,
    .frameHeight = 100,
    .startingX = 0,
    .startingY = 100
};

////////// GAME STRUCTURES //////////

// LEVELS
typedef struct Level {
    char name[50];
    int duration;
    int count;
    int maxSpeed;
    int multiplier;
    int bonus;
    S2D_Color *startingColor;
    S2D_Color *endingColor;
    bool completed;
} Level;

Level exosphere = {
    .name = "exosphere",
    .duration = 15,
    .count = 0,
    .maxSpeed = 10,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level thermosphere = {
    .name = "thermosphere",
    .duration = 15,
    .count = 0,
    .maxSpeed = 10,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level mesosphere = {
    .name = "thermosphere",
    .duration = 15,
    .count = 0,
    .maxSpeed = 10,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level stratosphere = {
    .name = "thermosphere",
    .duration = 15,
    .count = 0,
    .maxSpeed = 10,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level troposphere = {
    .name = "thermosphere",
    .duration = 15,
    .count = 0,
    .maxSpeed = 10,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

// PLAYERS
typedef struct Player {
    char name[50];
    int score;
    bool left;
    bool right;
    S2D_Image *image;
} Player;

Player player1 = {
    .name = "Tucker",
    .score = 0,
    .left = false,
    .right = false
};

Player player2 = {
    .name = "Spencer",
    .score = 0,
    .left = false,
    .right = false
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

// RINGS
typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    S2D_Color *color;
} Ring;

// Player 1
Ring capOneRings[5];
Ring ring1 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightGreen
};
Ring ring2 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightGreen
};
Ring ring3 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightGreen
};
Ring ring4 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightGreen
};
Ring ring5 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightGreen
};

// Player 2
Ring capTwoRings[5];
Ring ring6 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightBlue
};
Ring ring7 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightBlue
};
Ring ring8 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightBlue
};
Ring ring9 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightBlue
};
Ring ring10 = {
    .x = 0,
    .y = nomScreenHeight,
    .width = ringWidth,
    .height = ringHeight,
    .color = &lightBlue
};

// RINGMASTER
typedef struct Ringmaster {
    int rings;
    Ring *allRings;
    Ring *one;
    Ring *two;
    Ring *three;
    Ring *four;
    Ring *five;
    float velY;
    int maxY;
    int seperation;
    bool delay;
    int count;
    bool randomized;
    S2D_Color *color;
    Capsule *capsule;
} Ringmaster;

Ringmaster ringmaster1 = {
    .rings = 1,
    .allRings = &capOneRings[0],
    .one = &ring1,
    .two = &ring2,
    .three = &ring3,
    .four = &ring4,
    .five = &ring5,
    .velY = 5.0,
    .maxY = 10,
    .seperation = 600,
    .delay = false,
    .count = 0,
    .randomized = false,
    .color = &lightGreen,
    .capsule = &capsule1
};

Ringmaster ringmaster2 = {
    .rings = 1,
    .allRings = &capTwoRings[0],
    .one = &ring6,
    .two = &ring7,
    .three = &ring8,
    .four = &ring9,
    .five = &ring10,
    .velY = 5.0,
    .maxY = 10,
    .seperation = 600,
    .delay = true,
    .count = 0,
    .randomized = false,
    .color = &lightBlue,
    .capsule = &capsule2
};

// GAME STRUCTURES
typedef struct Game {
    int gameMode;
    bool gameOver;
    int level;
    int players;
    Level *levels;
    Player *player1;
    Player *player2;
    Capsule *capsule1;
    Capsule *capsule2;
} Game;

Level gameLevels[5];
void defineGameLevels() {
    gameLevels[0] = exosphere;
    gameLevels[1] = thermosphere;
    gameLevels[2] = mesosphere;
    gameLevels[3] = stratosphere;
    gameLevels[4] = troposphere;
}

Game game = {
    .gameMode = 2,
    .gameOver = false,
    .level = 0,
    .players = 2,
    .levels = &gameLevels[0],
};

////////// DRAWING FUNCTIONS //////////

// Simplify the S2D_DrawQuad command.
void drawRectangle(int x, int y, int width, int height, S2D_Color *color) {
    // Change orientation if enabled
    if (orientation == 1){
        int tempY = y;
        y = x;
        x = tempY;
        int tempWidth = width;
        width = height;
        height = tempWidth;
    }
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

S2D_Color* mixColor(S2D_Color *colorOne, S2D_Color *colorTwo, int balance){
    S2D_Color *color;
    color->r = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->g = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->b = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    color->a = (colorOne->r / 100 * balance) + (colorTwo->r / 100 * (100-balance));
    return color;
}

void drawBkg(Capsule *cap1, Capsule *cap2) {
    Level *currentLevel = &game.levels[game.level];
    //mixColor(currentLevel->startingColor, currentLevel->endingColor, 50);
    int x = 0;
    int y = 0;
    int width = nomScreenWidth;
    int height = nomScreenHeight;

    float color1 = cap1->heat / 100;
    float color2 = cap2->heat / 100;

    // Change orientation if enabled
    if (orientation == 1){
        int tempY = y;
        y = x;
        x = tempY;
        int tempWidth = width;
        width = height;
        height = tempWidth;
    }
    S2D_DrawQuad(
        // Upper left
        x, y, color1, 0, 0, 1,
        // Upper right
        (x + width), y, color2, 0, 0, 1,
        // Lower right
        (x + width), (y + height), color2, 0, 0, 1,
        // Lower left
        x, (y + height), color1, 0, 0, 1
    );
}

void updateCapsule(Capsule *cap){
    // Check for player input
    //printf("Player 1 left = %s \n", player1->left ? "true" : "false");
    //printf("Player 1 right = %s \n", player1->right ? "true" : "false");
    Level currentLevel = game.levels[game.level];

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
        if (cap->velY > currentLevel.maxSpeed){
            cap->velY = 10;
        }
    }
    // Invert player movement if vertical orientation
    // Update capsule velocity based on player input
    if (orientation == 1){
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
    }
    // Update capsule velocity based on player input
    else {
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
    }
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
    // If velocity is close to zero, make it zero.
    if (cap->velX < 0.1 && cap->velX > -0.1){
        cap->velX = 0;
    }
}

void drawSprite(S2D_Sprite *spr, Movement *mov, int frame){
    #ifdef ROTATE
        int y = (mov->frameWidth * mov->frames) - (mov->frameWidth * frame);
        S2D_ClipSprite(spr, mov->startingY, y, mov->frameHeight, mov->frameWidth);
    #else
        int x = mov->frameWidth * frame;
        S2D_ClipSprite(spr, x, mov->startingY, mov->frameWidth, mov->frameHeight);
    #endif
    S2D_DrawSprite(spr);
}

void drawCapsule(Capsule *cap){
    // Color change for heat buildup.
    // float r = (1.0 - cap->color->r / 100) * cap->heat;
    // float g = (0.0 - cap->color->g / 100) * cap->heat;
    // float b = (0.0 - cap->color->b / 100) * cap->heat;
    // S2D_Color colorTemp = {.r = r + cap->color->r, .g = g + cap->color->g, .b = b + cap->color->b, .a = cap->color->a};
    // Draw the capsule at the updated location rotation function.
    #ifdef ROTATE
        cap->spr->x = cap->y;
        cap->spr->y = cap->x;
    #else
        cap->spr->x = cap->x;
        cap->spr->y = cap->y;
    #endif
    // Draw left movement sprite
    if (cap->heat > 1){
        int frame = (cap->heat * cap->brake->frames / 100);
        drawSprite(cap->spr, cap->brake, frame);
    }
    else if (cap->velX < -0.5){
        int frame = (-cap->velX * cap->left->frames / cap->maxX);
        drawSprite(cap->spr, cap->left, frame);
    }
    else if (cap->velX > 0.5){
        int frame = (cap->velX * cap->right->frames / cap->maxX);
        drawSprite(cap->spr, cap->right, frame);
    }
    else {
        if (cap->down->currentFrame > cap->down->frames){
            cap->down->currentFrame = 0;
        }
        drawSprite(cap->spr, cap->down, cap->down->currentFrame);
        cap->down->currentFrame++;
    }
}

void drawRing(Ring *ring){
    drawRectangle(ring->x, ring->y, ring->width, ring->height, ring->color);
}

void reorderRings (Ringmaster *ringmaster){
    Ring *one = ringmaster->one;
    Ring *two = ringmaster->two;
    Ring *three = ringmaster->three;
    Ring *four = ringmaster->four;
    Ring *five = ringmaster->five;
    ringmaster->one = two;
    ringmaster->two = three;
    ringmaster->three = four;
    ringmaster->four = five;
    ringmaster->five = one;
}

void randomizeRings (Ringmaster *ringmaster){
    // Set an initial random X val for each ring.
    ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
    ringmaster->two->x = rand() % (nomScreenWidth - ringWidth) + 1;
    ringmaster->three->x = rand() % (nomScreenWidth - ringWidth) + 1;
    ringmaster->four->x = rand() % (nomScreenWidth - ringWidth) + 1;
    ringmaster->five->x = rand() % (nomScreenWidth - ringWidth) + 1;
    ringmaster->randomized = true;
}

void checkHit (Ringmaster *ringmaster){
    // Define hit targets
    int ringX = ringmaster->one->x;
    int ringMax = ringX + ringmaster->one->width;
    int capX = ringmaster->capsule->x;
    int capMax = capX + ringmaster->capsule->width;
    // Check for hits
    if (ringX < capX && capMax < ringMax){
        ringmaster->capsule->player->score += 100;
        printf("HIT! Player score: %d\n", ringmaster->capsule->player->score);
        ringmaster->rings--;
        ringmaster->one->y = nomScreenHeight;
        ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
        reorderRings(ringmaster);
    }
    else {
        ringmaster->capsule->heat += 60;
        printf("MISS! Capsule heat: %d\n", ringmaster->capsule->heat);
        ringmaster->rings--;
        ringmaster->one->y = nomScreenHeight;
        ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
        reorderRings(ringmaster);
    }
}


// Update function for ring tracking
void updateRingmaster(Ringmaster *ringmaster){
    ringmaster->velY = ringmaster->capsule->velY;
    int playArea = nomScreenHeight - ringmaster->capsule->y - ringmaster->capsule->height;
    int ringCheckpoint = nomScreenHeight - playArea - ringHeight;
    // Randomize ring starting X vals
    if (ringmaster->randomized == false){
        randomizeRings(ringmaster);
    }
    if (ringmaster->one->y < ringCheckpoint){
        checkHit(ringmaster);
    }


    // Case switch for number of rings on display.
    switch (ringmaster->rings){
        case 0:
            ringmaster->rings = 1;
        case 1:
            if (ringmaster->one->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 2;
            }
            break;
        case 2:
            if (ringmaster->two->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 3;
            }
            break;
        case 3:
            if (ringmaster->three->y < ringCheckpoint){
                ringmaster->rings = 4;
            }
            break;
        case 4:
            if (ringmaster->four->y < ringCheckpoint){
                ringmaster->rings = 5;
            }
            break;
        case 5:
            if (ringmaster->five->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 5;
            }
            break;
    }
}

void drawRingmaster (Ringmaster *ringmaster){
    switch (ringmaster->rings) {
        case 1:
            if (ringmaster->delay == true){
                ringmaster->count++;
                if (ringmaster->count >= 50){
                    ringmaster->delay = false;
                }
            }
            else {
                ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
                drawRing(ringmaster->one);
            }
            //printf("Drawing one ring\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            break;
        case 2:
            //printf("Drawing two rings\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
            ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
            drawRing(ringmaster->one);
            drawRing(ringmaster->two);
            break;
        case 3:
            //printf("Drawing three rings\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
            ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
            ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
            drawRing(ringmaster->one);
            drawRing(ringmaster->two);
            drawRing(ringmaster->three);
            break;
        case 4:
            //printf("Drawing three rings\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
            ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
            ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
            ringmaster->four->y = ringmaster->four->y - ringmaster->velY;
            drawRing(ringmaster->one);
            drawRing(ringmaster->two);
            drawRing(ringmaster->three);
            drawRing(ringmaster->four);
            break;
        case 5:
            //printf("Drawing three rings\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
            ringmaster->two->y = ringmaster->two->y - ringmaster->velY;
            ringmaster->three->y = ringmaster->three->y - ringmaster->velY;
            ringmaster->four->y = ringmaster->four->y - ringmaster->velY;
            ringmaster->five->y = ringmaster->five->y - ringmaster->velY;
            drawRing(ringmaster->one);
            drawRing(ringmaster->two);
            drawRing(ringmaster->three);
            drawRing(ringmaster->four);
            drawRing(ringmaster->five);
            break;
    }

}

/////////// KEYBOARD INPUT //////////
void on_key(S2D_Event e, const char *key) {
  switch (e) {
    case S2D_KEYDOWN:
        if(strcmp(key, "Left") == 0){
            player1.left = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(key, "Right") == 0){
            player1.right = true;
            //printf("Player 1 right = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(key, "A") == 0){
            player2.left = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(key, "D") == 0){
            player2.right = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(key, "Escape") == 0){
             S2D_Close(window);
        }
        //printf("Key %s pressed\n", key);
      break;

    case S2D_KEY:
      //printf("Key %s held down\n", key);
      break;

    case S2D_KEYUP:
      //printf("Key %s released\n", key);
      if(strcmp(key, "Left") == 0){
          player1.left = false;
      }
      if(strcmp(key, "Right") == 0){
          player1.right = false;
      }
      if(strcmp(key, "A") == 0){
          player2.left = false;
          //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
      }
      if(strcmp(key, "D") == 0){
          player2.right = false;
          //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
      }
      break;
  }
}

typedef struct Selector {
    bool arrived;
    int items;
    int currentSelection;
    bool wrap;
    int timeLimit;
    int timeRemaining;
    int count;
    bool selected;
} Selector;



////////// PLAYER SELECTION //////////
Selector playerSelect = {
    .arrived = false,
    .items = 2,
    .currentSelection = 1,
    .wrap = false,
    .timeLimit = 10,
    .timeRemaining = 10,
    .count = 0,
    .selected = false
};

void updatePlayerSelect (Player *player, Selector *selector){
    if (selector->selected == true){
        game.gameMode = 5;
    }
    else {
        selector->count++;
        if ((selector->count / 60) > selector->timeLimit - selector->timeRemaining){
            selector->timeRemaining--;
            if (selector->timeRemaining < 0){
                selector->selected = true;
            }
        }
        if (selector->currentSelection == 1){ // 1 player selected
            game.players = 1;
            if (player->left == false && player->right == true){
                selector->currentSelection = 2;
            }
        }
        else {
            game.players = 2; // 2 player selected
            if (player->left == true && player->right == false){
                selector->currentSelection = 1;
            }
        }
        if (player->left == true && player->right == true){
            selector->selected = true;
        }
    }
}

void drawPlayerSelect(Selector *selector){
    if (selector->timeRemaining < 10){
        drawNumber(&numberFont80, 0, 482, 1675);
        drawNumber(&numberFont80, selector->timeRemaining, 533, 1675);
    }
    else {
        drawNumber(&numberFont80, 1, 482, 1675);
        drawNumber(&numberFont80, 0, 533, 1675);
    }
    if (selector->currentSelection == 1){
        onePAni.frame = 0;
        twoPAni.frame = 1;
    }
    if (selector->currentSelection == 2){
        onePAni.frame = 1;
        twoPAni.frame = 0;
    }

    drawSprite2(&gameSprite, &onePAni, 215, 500);
    drawSprite2(&gameSprite, &twoPAni, 540, 500);
    drawSprite2(&gameSprite, &still, 180, 180);

}

/////////// GAME //////////
// UPDATE ALL PLAY PARAMETERS
void update() {
    switch (game.gameMode){
        case 1: //Looping display
            break;
        case 2: //Player # selection
            updatePlayerSelect(&player1,&playerSelect);
            break;
        case 3: //Ship selection
            break;
        case 4: //Introduction
            break;
        case 5: //Gameplay
            updateCapsule(&capsule1);
            updateRingmaster(&ringmaster1);
            if (game.players == 2){
                updateCapsule(&capsule2);
                updateRingmaster(&ringmaster2);
            }
            break;
    }
}

// DRAW UPDATED ART
void render() {
    switch (game.gameMode){
        case 1: //Looping display
            break;
        case 2: //Player # selection
            drawPlayerSelect(&playerSelect);
            break;
        case 3: //Ship selection
            break;
        case 4: //Introduction
            break;
        case 5: //Gameplay
            //drawBkg(&capsule1, &capsule2);
            drawNumber(&numberFont80, player1.score, 100, 100);
            drawCapsule(&capsule1);
            drawRingmaster(&ringmaster1);
            if (game.players == 2){
                drawCapsule(&capsule2);
                drawRingmaster(&ringmaster2);
            }
            break;

    }
}

int main() {
    // SETUP
    defineColors();
    if (setupDefined == false) {
        defineImages();
        defineCapsuleSpr();
        defineGameLevels();
        setupDefined = true;
    }
    // Enable verbose output
    S2D_Diagnostics(true);
    // Create game window, fullscreen.
    window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, 0);
    // Temporary method for disabling cursor.
    SDL_ShowCursor(SDL_DISABLE);
    // Enable keyboard input
    window->on_key = on_key;
    //Cap the frame rate, 60 frames per second by default
    window->fps_cap = 60;
    // Set the window background color, black by default
    window->background.r = 0.0;
    window->background.g = 0.0;
    window->background.b = 0.0;
    // Standard S2D
    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}
