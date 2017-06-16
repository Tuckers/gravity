#ifndef GAMEDEF_H
#define GAMEDEF_H

// Define to enable 90degree rotation.
//#define ROTATE

#define capsuleHeight 100
#define capsuleWidth 100

#define ringHeight 10
#define ringWidth 150

#define nomScreenHeight 1920
#define nomScreenWidth 1080

#ifdef ROTATE
    int screenHeight = 1080;
    int screenWidth = 1920;
    int orientation = 1;
#else
    int screenHeight = 1920;
    int screenWidth = 1080;
    int orientation = 0;
#endif

////////// GLOBAL VARIABLES //////////
bool running = true;
bool setupDefined = false;
float friction = 0.98;
float entropy = 0.8;

int firstTime = false;

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



// PLAYERS
typedef struct Player {
    char name[50];
    int score;
    bool left;
    bool right;
    S2D_Image *image;
    int ship;
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


#endif /* GAMEDEF_H */

///// STRUCTURES /////
