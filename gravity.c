#include <simple2d.h>

//#define ROTATE

#define capsuleHeight 50
#define capsuleWidth 50

#define ringHeight 10
#define ringWidth 150

#define nomScreenHeight 1920
#define nomScreenWidth 1080

S2D_Window *window;


// GLOBAL VARIABLES
bool running = true;
bool capsulesDefined = false;
bool playersDefined = false;
bool setupDefined = false;
float friction = 0.98;

#ifdef ROTATE
    int screenHeight = 1080;
    int screenWidth = 1920;
    int orientation = 1;
#else
    int screenHeight = 1920;
    int screenWidth = 1080;
    int orientation = 0;
#endif



// COLOR DEFINITION
S2D_Color gray;
S2D_Color green;
S2D_Color red;
S2D_Color black;
S2D_Color white;
S2D_Color blue = {.r = 0.0, .g = 0.0, .b = 1.0, .a = 1.0};

void defineColors(){
    // Define green
    green.r = 0.0;
    green.g = 1.0;
    green.b = 0.0;
    green.a = 1.0;

    // Define red
    red.r = 1.0;
    red.g = 0.0;
    red.b = 0.0;
    red.a = 1.0;

    // Define white
    white.r = 1.0;
    white.g = 1.0;
    white.b = 1.0;
    white.a = 1.0;

    // Define black
    black.r = 0.0;
    black.g = 0.0;
    black.b = 0.0;
    black.a = 1.0;

    // Define gray
    gray.r = 0.5;
    gray.g = 0.5;
    gray.b = 0.5;
    gray.a = 1.0;

    // Define blue
    blue.r = 0.0;
    blue.g = 0.0;
    blue.b = 1.0;
    blue.a = 1.0;

    S2D_Color darkGreen;

    //convertColor(&darkGreen);

}

// GAME STUCTURES

typedef struct Player {
    char name[50];
    int score;
    bool left;
    bool right;
    S2D_Image *image;
} Player;

Player player1;
Player player2;

void definePlayers(){
    if (playersDefined == false){
        strcpy(player1.name, "Tucker");
        player1.score = 0;
        player1.left = false;
        player1.right = false;

        strcpy(player2.name, "Spencer");
        player2.score = 0;
        player2.left = false;
        player2.right = false;
        playersDefined = true;
    }
}

typedef struct Capsule {
    int x;
    int y;
    int width;
    int height;
    float velX;
    float velY;
    int maxX;
    int maxY;
    int heat;
    S2D_Color *color;
    Player *player;
} Capsule;

Capsule capsule1;
Capsule capsule2;

void defineCapsules(){
    if (capsulesDefined == false){
        capsule1.x = 0;
        capsule1.y = 0;
        capsule1.width = capsuleWidth;
        capsule1.height = capsuleHeight;
        capsule1.velX = 0;
        capsule1.velY = 0;
        capsule1.maxX = 20;
        capsule1.maxY = 10;
        capsule1.heat = 0;

        capsule2 = capsule1;

        capsule1.player = &player1;
        capsule1.color = &green;
        capsule2.player = &player2;
        capsule2.color = &blue;
        capsulesDefined = true;
    }

}

// RINGS
typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    S2D_Color *color;
} Ring;

Ring ring1 = {.x = 100, .y = nomScreenHeight, .width = ringWidth, .height = ringHeight, .color = &red};
Ring ring2 = {.x = 300, .y = nomScreenHeight, .width = ringWidth, .height = ringHeight, .color = &red};
Ring ring3 = {.x = 400, .y = nomScreenHeight, .width = ringWidth, .height = ringHeight, .color = &red};

typedef struct Ringmaster {
    int rings;
    Ring *one;
    Ring *two;
    Ring *three;
    float velY;
    int maxY;
    S2D_Color *color;
    Capsule *capsule;
} Ringmaster;

Ringmaster ringmaster1 = {.rings = 1, .one = &ring1, .two = &ring2, .three = &ring3, .velY = 5.0, .maxY = 10, .color = &red, .capsule = &capsule1};

void convertColor(int red, int green, int blue, int alpha, S2D_Color *color) {
    color->r = red / 255;
    color->g = green / 255;
    color->b = blue / 255;
    color->a = alpha / 100;
}

void drawRectangle(int x, int y, int width, int height, S2D_Color *color) {
    if (orientation == 1){
        int tempY = y;
        y = x;
        x = nomScreenHeight - tempY;
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
    //printf("Player 1 left = %s \n", player1->left ? "true" : "false");
    //printf("Player 1 right = %s \n", player1->right ? "true" : "false");
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

void drawCapsule(Capsule *cap){
    cap->velX *= friction;

    int x = cap->x + cap->velX;
    int y = cap->y + cap->velY;

    if ((x + cap->width) > nomScreenWidth){
        x = nomScreenWidth - cap->width;
        cap->velX = 0;
    } else if (x < 0) {
        x = 0;
        cap->velX = 0;
    }


    if ((y + cap->height) > nomScreenHeight - 200){
        y = nomScreenHeight - cap->height - 200;
    } else if (y < 100) {
        y = 100;
    }

    cap->x = x;
    cap->y = y;

    if (cap->velX < 0.1 && cap->velX > -0.1){
        cap->velX = 0;
    }

    drawRectangle(x, y, cap->width, cap->height, cap->color);
}

void drawRing(Ring *ring){
    if (orientation == 1){
        drawRectangle(ring->x, ring->y, ring->height, ring->width, ring->color);
    } else {
        drawRectangle(ring->x, ring->y, ring->width, ring->height, ring->color);
    }

}

void reorderRings (Ringmaster *ringmaster){
    Ring *one = ringmaster->one;
    Ring *two = ringmaster->two;
    Ring *three = ringmaster->three;
    ringmaster->one = two;
    ringmaster->two = three;
    ringmaster->three = one;
}

// Update function for ring tracking
void updateRingmaster(Ringmaster *ringmaster){
    int playArea = nomScreenHeight - ringmaster->capsule->y - ringmaster->capsule->height;
    int ringSpacing =  playArea / 3;
    // Only draw first ring until at 1/3 playArea
    if (ringmaster->rings == 1){
        if (ringmaster->one->y < (nomScreenHeight - ringSpacing)){
            ringmaster->rings = 2;
        }
    }
    // Only draw two rings until at 2/3 playArea
    else if (ringmaster->rings == 2){
        if (ringmaster->two->y < (nomScreenHeight - ringSpacing)){
            ringmaster->rings = 3;
        }
    }
    // Draw all three rings and check for hits
    else if (ringmaster->rings == 3){
        if (ringmaster->one->y < (nomScreenHeight - playArea - ringmaster->one->height)){
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
                reorderRings(ringmaster);
            }
            else {
                ringmaster->capsule->heat += 100;
                ringmaster->one->y = nomScreenHeight;
                ringmaster->one->x = 100;
                printf("MISS! Capsule heat: %d\n", ringmaster->capsule->heat);
                ringmaster->one->y = nomScreenHeight;
                reorderRings(ringmaster);
            }
        }
    }
}

void drawRingmaster (Ringmaster *ringmaster){
    switch (ringmaster->rings) {
        case 1:
            //printf("Drawing one ring\n");
            //printf("Ring one Y: %d\n", ringmaster->one->y);
            ringmaster->one->y = ringmaster->one->y - ringmaster->velY;
            drawRing(ringmaster->one);
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
    if (setupDefined == false){
        defineCapsules();
        definePlayers();
        setupDefined = true;
    }

    updateCapsule(&capsule1);
    updateCapsule(&capsule2);
    updateRingmaster(&ringmaster1);

}

// DRAW UPDATED ART
void render() {
    drawCapsule(&capsule1);
    drawCapsule(&capsule2);
    drawRingmaster(&ringmaster1);

}

int main() {
    // SETUP
    defineColors();

    S2D_Diagnostics(true);

    window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, 0);

    // Temporary method for disabling cursor.
    SDL_ShowCursor(SDL_DISABLE);

    //S2D_FULLSCREEN

    window->on_key = on_key;
    //Cap the frame rate, 60 frames per second by default
    window->fps_cap = 60;
    // Set the window background color, black by default
    window->background.r = 0.0;
    window->background.g = 0.0;
    window->background.b = 0.0;

    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}
