#include <simple2d.h>

// Define to enable 90degree rotation.
//#define ROTATE

#define capsuleHeight 50
#define capsuleWidth 50

#define ringHeight 10
#define ringWidth 150

#define nomScreenHeight 1920
#define nomScreenWidth 1080

S2D_Window *window;


////////// GLOBAL VARIABLES //////////
bool running = true;
bool capsulesDefined = false;
bool playersDefined = false;
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


////////// GAME STRUCTURES //////////

// LEVELS
typedef struct Level {
    char name[50];
    int duration;
    int multiplier;
    int bonus;
    S2D_Color *startingColor;
    S2D_Color *endingColor;
    bool completed;
} Level;

Level exosphere = {
    .name = "exosphere",
    .duration = 15,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level thermosphere = {
    .name = "thermosphere",
    .duration = 15,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level mesosphere = {
    .name = "thermosphere",
    .duration = 15,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level stratosphere = {
    .name = "thermosphere",
    .duration = 15,
    .multiplier = 1,
    .bonus = 1000,
    .startingColor = &black,
    .endingColor = &gray,
    .completed = false
};

Level troposphere = {
    .name = "thermosphere",
    .duration = 15,
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
    int x;
    int y;
    int width;
    int height;
    float velX;
    float velY;
    float preVelY;
    int maxX;
    int maxY;
    int heat;
    bool braking;
    S2D_Color *color;
    Player *player;
} Capsule;

Capsule capsule1 = {
    .x = 0,
    .y = 0,
    .width = capsuleWidth,
    .height = capsuleHeight,
    .velX = 0,
    .velY = 1,
    .preVelY = 0,
    .maxX = 20,
    .maxY = 10,
    .heat = 0,
    .braking = false,
    .player = &player1,
    .color = &green
};

Capsule capsule2 = {
    .x = nomScreenWidth,
    .y = 0,
    .width = capsuleWidth,
    .height = capsuleHeight,
    .velX = 0,
    .velY = 1,
    .preVelY = 0,
    .maxX = 20,
    .maxY = 10,
    .heat = 0,
    .braking = false,
    .player = &player2,
    .color = &blue
};

// RINGS
typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    S2D_Color *color;
} Ring;

// Player 1
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

// GAME
typedef struct Game {
    int gameMode;
    bool gameOver;
    int level;
    int players;
    Level *levelOne;
    Level *levelTwo;
    Level *levelThree;
    Level *levelFour;
    Level *levelFive;
    Player *player1;
    Player *player2;
    Capsule *capsule1;
    Capsule *capsule2;
} Game;

Game game = {
    .gameMode = 3,
    .gameOver = false,
    .level = 1,
    .players = 2,
    .levelOne = &exosphere,
    .levelTwo = &thermosphere,
    .levelThree = &mesosphere,
    .levelFour = &stratosphere,
    .levelFive = &troposphere
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

void updateCapsule(Capsule *cap){
    // Check for player input
    //printf("Player 1 left = %s \n", player1->left ? "true" : "false");
    //printf("Player 1 right = %s \n", player1->right ? "true" : "false");

    // Braking
    if (cap->player->left == true && cap->player->right == true){
        if (cap->braking == false){
            cap->preVelY = cap->velY;
            cap->braking = true;
        }
        // If braking, slow capsule and add heat
        cap->velY = cap->velY - 1;
        cap->heat = cap->heat + 1;
        if (cap->heat > 300){
            cap->heat = 300;
        }
        if (cap->velY < -cap->maxY){
            cap->velY = -cap->maxY;
        }
    }
    else {
        // If not braking, resume previous speed and reduce heat
        cap->braking = false;
        cap->heat--;
        if (cap->heat < 0){
            cap->heat = 0;
        }
        if (cap->velY < cap->preVelY){
            cap->velY = cap->velY + 0.5;
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


}

void drawCapsule(Capsule *cap){
    // Add friction quotiant to slow movement
    cap->velX *= friction;
    // Temp variables to hold velocity + current location
    int x = cap->x + cap->velX;
    int y = cap->y + cap->velY;
    // Color change for heat buildup.
    float r = (1.0 - cap->color->r / 300) * cap->heat;
    float g = (0.0 - cap->color->g / 300) * cap->heat;
    float b = (0.0 - cap->color->b / 300) * cap->heat;
    S2D_Color colorTemp = {.r = r + cap->color->r, .g = g + cap->color->g, .b = b + cap->color->b, .a = cap->color->a};
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
    // Draw the capsule at the updated location.
    drawRectangle(x, y, cap->width, cap->height, &colorTemp);
}

void drawRing(Ring *ring){
    drawRectangle(ring->x, ring->y, ring->width, ring->height, ring->color);
}

void reorderRings (Ringmaster *ringmaster){
    Ring *one = ringmaster->one;
    Ring *two = ringmaster->two;
    Ring *three = ringmaster->three;
    ringmaster->one = two;
    ringmaster->two = three;
    ringmaster->three = one;
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
        ringmaster->one->y = nomScreenHeight;
        ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
        reorderRings(ringmaster);
    }
    else {
        ringmaster->capsule->heat += 60;
        printf("MISS! Capsule heat: %d\n", ringmaster->capsule->heat);
        ringmaster->one->y = nomScreenHeight;
        ringmaster->one->x = rand() % (nomScreenWidth - ringWidth) + 1;
        reorderRings(ringmaster);
    }
}


// Update function for ring tracking
void updateRingmaster(Ringmaster *ringmaster){
    int playArea = nomScreenHeight - ringmaster->capsule->y - ringmaster->capsule->height;
    if (ringmaster->randomized == false){
        randomizeRings(ringmaster);
    }
    switch (ringmaster->rings){
        int ringCheckpoint = nomScreenHeight - playArea - ringHeight;
        case 1:
            if (ringmaster->one->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 2;
            }
            if (ringmaster->one->y < ringCheckpoint){
                checkHit(ringmaster);
            }
            break;
        case 2:
            if (ringmaster->two->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 3;
            }
            if (ringmaster->one->y < ringCheckpoint){
                checkHit(ringmaster);
            }
            break;
        case 3:
            if (ringmaster->three->y < ringCheckpoint){
                ringmaster->rings = 4;
            }
            if (ringmaster->one->y < ringCheckpoint){
                checkHit(ringmaster);
            }
            break;
        case 4:
            if (ringmaster->four->y < ringCheckpoint){
                ringmaster->rings = 5;
            }
            if (ringmaster->one->y < (nomScreenHeight - playArea - ringmaster->one->height)){
                checkHit(ringmaster);
            }
            break;
        case 5:
            if (ringmaster->five->y < (nomScreenHeight - ringmaster->seperation)){
                ringmaster->rings = 5;
            if (ringmaster->one->y < (nomScreenHeight - playArea - ringmaster->one->height)){
                checkHit(ringmaster);
                }
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

//const char *font = "SanFranciscoText-Regular.otf";
//int font_size = 20;

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

// UPDATE ALL PLAY PARAMETERS
void update() {
    switch (game.gameMode){
        case 1: //Looping display
            break;
        case 2: //Player input, game selection
            break;
        case 3: //Gameplay
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
    drawCapsule(&capsule1);
    drawCapsule(&capsule2);
    drawRingmaster(&ringmaster1);
    drawRingmaster(&ringmaster2);

}

int main() {
    // SETUP
    defineColors();
    // Enable verbose output
    S2D_Diagnostics(true);
    // Create game window, fullscreen.
    window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, S2D_FULLSCREEN);
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
