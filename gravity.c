#include <simple2d.h>

#define capsuleHeight 50
#define capsuleWidth 50

#define screenHeight 960
#define screenWidth 540

S2D_Window *window;


// GLOBAL VARIABLES
bool running = true;
bool capsulesDefined = false;
bool playersDefined = false;
float friction = 0.98;

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
    gray.r = 1.0;
    gray.g = 0.0;
    gray.b = 0.0;
    gray.a = 1.0;

    // Define white
    gray.r = 1.0;
    gray.g = 1.0;
    gray.b = 1.0;
    gray.a = 1.0;

    // Define black
    gray.r = 0.0;
    gray.g = 0.0;
    gray.b = 0.0;
    gray.a = 1.0;

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

}

// GAME STUCTURES

typedef struct Player {
    char name[50];
    int score;
    bool left;
    bool right;
    S2D_Image image;
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
//Capsule capsule2;

void defineCapsules(){
    if (capsulesDefined == false){
        capsule1.x = 0;
        capsule1.y =0;
        capsule1.width = capsuleWidth;
        capsule1.height = capsuleHeight;
        capsule1.velX = 0;
        capsule1.velY = 0;
        capsule1.maxX = 10;
        capsule1.maxY = 10;
        capsule1.heat = 0;

        //capsule2 = capsule1;

        capsule1.player = &player1;
        capsule1.color = &green;
        //capsule2.player = player2;
        //capsule2.color = blue;
        capsulesDefined = true;
    }

}


typedef struct Ring {
    int x;
    int y;
    int width;
    int height;
    int velY;
    int maxY;
    S2D_Color color;
} Ring;



// S2D_Color convertColor(int red, int green, int blue, int alpha, *S2D_Color color) {
//     //S2D_Color color;
//     color->r = red / 255;
//     color->g = green / 255;
//     color->b = blue / 255;
//     color->a = alpha / 100;
//     return color;
// }

void drawRectangle(int x, int y, int width, int height, S2D_Color *color) {
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
        cap->velX++;
        printf("New capsule velX = %f\n", cap->velX);
        //  if (cap.velX > cap.maxX){
        //      cap.velX = cap.maxX;
        //  }
    }

    if (cap->player->left == true){
        cap->velX--;
        printf("New capsule velX = %f\n", cap->velX);
        // if (cap.velX < -cap.maxX){
        //     cap.velX = -cap.maxX;
        // }
    }
    return;

}

void drawCapsule(Capsule *cap) {
    cap->velX *= friction;

    int x = cap->x + cap->velX;
    int y = cap->y + cap->velY;

    if ((x + cap->width) > screenWidth){
        x = screenWidth - cap->width;
        cap->velX = 0;
    } else if (x < 0) {
        x = 0;
        cap->velX = 0;
    }


    if ((y + cap->height) > screenHeight - 200){
        y = screenHeight - cap->height - 200;
    } else if (y < 100) {
        y = 100;
    }

    cap->x = x;
    cap->y = y;

    if (cap->velX < 0.1 && cap->velX > -0.1){
        cap->velX = 0;
    }

    S2D_DrawQuad(
        // Upper left
        x, y, cap->color->r, cap->color->g, cap->color->b, cap->color->a,
        // Upper right
        (x + cap->width), y, cap->color->r, cap->color->g, cap->color->b, cap->color->a,
        // Lower right
        (x + cap->width), (y + cap->height), cap->color->r, cap->color->g, cap->color->b, cap->color->a,
        // Lower left
        x, (y + cap->height), cap->color->r, cap->color->g, cap->color->b, cap->color->a
    );
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
      break;
  }
}

// UPDATE ALL PLAY PARAMETERS
void update() {
    defineCapsules();
    definePlayers();
    updateCapsule(&capsule1);
    //updateCapsule(&capsule2);

}

// DRAW UPDATED ART
void render() {
    drawCapsule(&capsule1);
    //drawCapsule(&capsule2);

}

int main() {
    // SETUP
    defineColors();
    //defineCapsules();


    S2D_Diagnostics(true);
    window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, S2D_RESIZABLE);
    window->on_key = on_key;
    //Cap the frame rate, 60 frames per second by default
    //window->fps_cap = 60;
    // Set the window background color, black by default
    window->background.r = 0.0;
    window->background.g = 0.0;
    window->background.b = 0.0;

    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}
