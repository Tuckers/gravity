#include <simple2d.h>
#include "sprites.h"
#include "gameDef.h"
#include "color.h"
#include "bkg.h"
#include "rings.h"
#include "capsule.h"
#include "particle.h"

S2D_Window *window;

////////// GAME STRUCTURES //////////
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


// GAME STRUCTURES
typedef struct Game {
    int gameMode;
    bool gameOver;
    int level;
    int players;
    int altitude;
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
    .altitude = 500000,
    .level = 0,
    .players = 2,
    .levels = &gameLevels[0],
};

/////////// KEYBOARD INPUT //////////
void on_key(S2D_Event e) {
  switch (e.type) {
    case S2D_KEY_DOWN:
        if(strcmp(e.key, "Left") == 0){
            player1.left = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(e.key, "Right") == 0){
            player1.right = true;
            //printf("Player 1 right = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(e.key, "A") == 0){
            player2.left = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(e.key, "D") == 0){
            player2.right = true;
            //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
        }
        if(strcmp(e.key, "Escape") == 0){
             S2D_Close(window);
        }
        //printf("Key %s pressed\n", key);
      break;

    case S2D_KEY_HELD:
      //printf("Key %s held down\n", key);
      break;

    case S2D_KEY_UP:
      //printf("Key %s released\n", key);
      if(strcmp(e.key, "Left") == 0){
          player1.left = false;
      }
      if(strcmp(e.key, "Right") == 0){
          player1.right = false;
      }
      if(strcmp(e.key, "A") == 0){
          player2.left = false;
          //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
      }
      if(strcmp(e.key, "D") == 0){
          player2.right = false;
          //printf("Player 1 left = %s \n", player1.left ? "true" : "false");
      }
      break;
  }
}

typedef struct Selector {
    bool arrived;
    int items;
    int p1Selection;
    int p2Selection;
    int p1LastMoved;
    int p2LastMoved;
    int timeLimit;
    int timeRemaining;
    int count;
    bool p1Selected;
    bool p2Selected;
} Selector;

////////// PLAYER SELECTION //////////
Selector playerSelect = {
    .arrived = false,
    .items = 2,
    .p1Selection = 1,
    .timeLimit = 5,
    .timeRemaining = 5,
    .count = 0,
    .p1Selected = false
};

void updatePlayerSelect (Player *player, Selector *selector){
    if (selector->p1Selected == true){
        game.gameMode = 3;
    }
    else {
        selector->count++;
        if ((selector->count / 60) > selector->timeLimit - selector->timeRemaining){
            selector->timeRemaining--;
            if (selector->timeRemaining < 0){
                selector->p1Selected = true;
                game.gameMode = 3;
            }
        }
        if (selector->p1Selection == 1){ // 1 player selected
            game.players = 1;
            if (player->left == false && player->right == true){
                selector->p1Selection = 2;
            }
        }
        else {
            game.players = 2; // 2 player selected
            if (player->left == true && player->right == false){
                selector->p1Selection = 1;
            }
        }
        if (player->left == true && player->right == true){
            selector->p1Selected = true;
        }
    }
}

void drawPlayerSelect(Selector *selector){
    drawRectangle(0,0, nomScreenWidth, nomScreenHeight, &darkBlue);
    if (selector->timeRemaining < 10){
        drawNumber(&numberFont300, 0, 40, 1340);
        drawNumber(&numberFont300, selector->timeRemaining, 210, 1340);
    }
    else {
        drawNumber(&numberFont300, 1, 70, 1340);
        drawNumber(&numberFont300, 0, 210, 1340);
    }
    if (selector->p1Selection == 1){
        drawRectangle(40, 40, 500, 1242, &blue);
        drawPolygon(&psPlayer1[0], 6, &white, false);
        drawPolygon(&psPlayer2a[0], 6, &white, true);
        drawPolygon(&psPlayer2b[0], 6, &white, true);
        //drawTriangle(&psPlayer1[0], &psPlayer1[1], &psPlayer1[2], &white);
        //onePAni.frame = 0;
        //twoPAni.frame = 1;
    }
    if (selector->p1Selection == 2){
        drawRectangle(540, 40, 500, 1242, &blue);
        drawPolygon(&psPlayer1[0], 6, &white, true);
        drawPolygon(&psPlayer2a[0], 6, &white, false);
        drawPolygon(&psPlayer2b[0], 6, &white, false);
        onePAni.frame = 1;
        twoPAni.frame = 0;
    }
    drawRectangle(40, 1282, nomScreenWidth - 80, 8, &yellow);
    drawSprite2(&gameSprite, &titlePlayerSelect, 65, 1604);

}

////////// SHIP SELECTION //////////
Selector shipSelect = {
    .arrived = false,
    .items = 5,
    .p1Selection = 1,
    .p2Selection = 1,
    .timeLimit = 5,
    .timeRemaining = 5,
    .count = 0,
    .p1Selected = false,
    .p2Selected = false
};

void updateShipSelect (Selector *selector){
    if (selector->p1Selected == true && selector->p2Selected == true){
        game.gameMode = 5;
    }
    else {
        selector->count++;
        if ((selector->count / 60) > selector->timeLimit - selector->timeRemaining){
            selector->timeRemaining--;
            if (selector->timeRemaining < 0){
                selector->p1Selected = true;
                selector->p2Selected = true;
                game.gameMode = 5;
            }
        }
    }
}

void capsuleSelect (Capsule *cap, Selector *selector){
    int selection;
    if (cap->player->number == 1){
        if ((selector->count - selector->p1LastMoved) > 5){
            selector->p1LastMoved = selector->count;
            if (cap->player->left == false && cap->player->right == true){ //what if right?
                selector->p1Selection++;
                if (selector->p1Selection > selector->items){
                    selector->p1Selection = selector->items;
                }
            }
            else if (cap->player->left == true && cap->player->right == false){ //what if left?
                selector->p1Selection--;
                if (selector->p1Selection < 1){
                    selector->p1Selection = 1;
                }
            }
            else if (cap->player->left == true && cap->player->right == true){ //what if select?
                selector->p1Selected = true;
            }
        }
        selection = selector->p1Selection;
    }
    else {
        if ((selector->count - selector->p2LastMoved) > 5){
            selector->p2LastMoved = selector->count;
            if (cap->player->left == false && cap->player->right == true){ //what if right?
                selector->p2Selection++;
                if (selector->p2Selection > selector->items){
                    selector->p2Selection = selector->items;
                }
            }
            else if (cap->player->left == true && cap->player->right == false){ //what if left?
                selector->p2Selection--;
                if (selector->p2Selection < 1){
                    selector->p2Selection = 1;
                }
            }
            else if (cap->player->left == true && cap->player->right == true){ //what if select?
                selector->p2Selected = true;
            }
        }
        selection = selector->p2Selection;
    }
    switch(selection){
        case 1:
            shipList.first = 10;
            cap->ship = &ship1;
            break;
        case 2:
            shipList.first = 11;
            cap->ship = &ship2;
            break;
        case 3:
            shipList.first = 12;
            cap->ship = &ship3;
            break;
        case 4:
            shipList.first = 13;
            cap->ship = &ship4;
            break;
        case 5:
            shipList.first = 14;
            cap->ship = &ship5;
            break;
    }
}

void drawStats(Ship *ship){
    drawSprite2(&gameSprite, &shipSpeed, 667, 574);
    drawBar(667, 620, 260, 24, ship->speed, &blue);
    drawSprite2(&gameSprite, &shipShield, 667, 684);
    drawBar(667, 730, 260, 24, ship->shield, &blue2);
    drawSprite2(&gameSprite, &shipControl, 667, 794);
    drawBar(667, 840, 260, 24, ship->control, &blue3);
    drawSprite2(&gameSprite, ship->title, 265, 203);
    drawSprite2(&gameSprite, ship->big, 120, 520);
}

void drawShipSelect(Selector *selector){
    drawRectangle(0,0, nomScreenWidth, nomScreenHeight, &darkBlue);
    if (selector->timeRemaining < 10){
        drawNumber(&numberFont300, 0, 700, 1618);
        drawNumber(&numberFont300, selector->timeRemaining, 870, 1618);
    }
    else {
        drawNumber(&numberFont300, 1, 730, 1618);
        drawNumber(&numberFont300, 0, 870, 1618);
    }
    switch(selector->p1Selection){
        case 1:
            drawStats(&ship1);
            break;
        case 2:
            drawStats(&ship2);
            break;
        case 3:
            drawStats(&ship3);
            break;
        case 4:
            drawStats(&ship4);
            break;
        case 5:
            drawStats(&ship5);
            break;
    }
    drawSprite2(&gameSprite, &shipList, 208, 1228);
    drawRectangle(40, 1565, nomScreenWidth - 80, 8, &yellow);
    drawSprite2(&gameSprite, &titleShipSelect, 40, 1613);

}

/////////// GAME //////////
// UPDATE ALL PLAY PARAMETERS
float deg = 0.1;
void update() {
    switch (game.gameMode){
        case 1: //Looping display
            break;
        case 2: //Player # selection
            updatePlayerSelect(&player1, &playerSelect);
            break;
        case 3: //Ship selection
            updateShipSelect(&shipSelect);
            capsuleSelect(&capsule1, &shipSelect);
            if (game.players == 2){ // If two player update second capsule selection
                capsuleSelect(&capsule2, &shipSelect);
            }
            break;
        case 4: //Introduction
            if (firstTime == false){
                generateRings(&rm1);
                firstTime = true;
            }
            updateRingmaster(&rm1);
            updateBKG(&background);
            break;
        case 5: //Gameplay
            if (firstTime == true){
                generateRings(&rm1);
                generateCapPoints(&capsule1, cpA1, cpT1, 10, false);
                if (game.players == 2){ // If two player generate extra cap points
                    generateCapPoints(&capsule2, cpA2, cpT2, 10, true);
                }
                firstTime = false;
            }
            updateRingmaster(&rm1);
            updateShip(&capsule1);
            checkHit(&rm1, &capsule1);
            if (game.players == 2){ // If two player update capsule 2 and check for hits
                updateShip(&capsule2);
                checkHit(&rm1, &capsule2);
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
            drawShipSelect(&shipSelect);
            break;
        case 4: //Introduction
            //drawBKG(&background);
            //drawRingmaster(&rm1);
            //drawRingDemo(&rm1, &ringTest);
            break;
        case 5: //Gameplay
            if (firstTime == false){
                drawRingmaster(&rm1);
                drawShip(&capsule1);
                drawHeatBar(&capsule1, 40, nomScreenHeight - 154);
                drawNumber(&numberFont50, player1.score, 40, nomScreenHeight - 88);
                //drawNumber(&numberFont50, capsule1.heat, 40, nomScreenHeight - 48);
                if (game.players == 2){
                    drawShip(&capsule2);
                    drawNumber(&numberFont50, player2.score, nomScreenWidth - 100, nomScreenHeight - 88);
                    drawHeatBar(&capsule2, nomScreenWidth - 320, nomScreenHeight - 154);
                }
            }
            break;
    }
}

int main() {
    // SETUP
    defineColors();
    if (setupDefined == false) {
        defineImages();
        defineGameLevels();
        setupDefined = true;
    }
    // Enable verbose output
    S2D_Diagnostics(true);
    // Create game window, fullscreen.
    #ifdef ROTATE
        window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, 0);
    #else
        window = S2D_CreateWindow("Gravity", screenWidth, screenHeight, update, render, S2D_RESIZABLE);
    #endif
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
