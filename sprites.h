#include "gameDef.h"
#include "color.h"
#ifndef SPRITES_H
#define SPRITES_H

typedef struct Sprite {
    S2D_Sprite *spr;
    int frames;
    double (*sheet)[4];
    int height;
    int width;
} Sprite;

Sprite numberFont80;
S2D_Sprite *numberFont80img;
double nf80Sheet[10][4] = {
    {	0	,	0	,	65	,	65	},
    {	65	,	0	,   65	,	65	},
    {	130	,	0	,	65	,	65	},
    {	195	,	0	,	65	,	65	},
    {	260	,   0	,	65	,	65	},
    {	325	,	0	,	65	,	65	},
    {	390	,	0	,	65	,	65	},
    {   455	,	0	,	65	,	65	},
    {	520	,	0	,	65	,	65	},
    {	585	,	0	,	65	,	65  }
};

// Sprite gameSprite;
// S2D_Sprite *gameImg;
// double gameSheet[11][4] = {
//     {	0	,	0	,	720	,	160	}, // 0 - Select players
//     {	0	,	160	,   720	,	160	}, // 1 - Select your ship
//     {	720	,	0	,   325	,	380	}, // 2 - 1 player selected
//     {	1045,	0	,	325	,	380	}, // 3 - 1 player unselected
//     {	1370,	0	,	325	,	380	}, // 4 - 2 player selected
//     {	1695,	0	,   325	,	380	}, // 5 - 2 player unselected
//     {	0	,	320	,	720	,	160	}, // 6 - Troposphere
//     {	0	,	480	,	720	,	160	}, // 7 - Stratosphere
//     {	0	,	640	,   720	,	160	}, // 8 - Mesosphere
//     {	0	,	800	,	720	,	160	}, // 9 - Thermosphere
//     {	0	,	960	,	720	,	160	} // 10 - Exosphere
// };

Sprite gameSprite;
S2D_Sprite *gameImg;
double gameSheet[10][4] = {
    {	0	,	0	,	280	,	180	}, // 0 - Select players
    {	0	,	180	,   280	,	180	}, // 1 - Select your ship
    {	0	,	360	,   152	,	36	}, // 2 - Ship stat - Control
    {	0   ,	396	,	152	,	36	}, // 3 - Ship stat - Speed
    {	0   ,	432	,	152	,	36	}, // 4 - Ship stat - Shield
    {	0   ,	469	,   550	,	143	}, // 5 - Ship class "Squall"
    {	0	,	612	,	550	,	143	}, // 6 - Ship class "Tempest"
    {	0	,	755	,	550	,	143	}, // 7 - Ship class "Blizzard"
    {	0	,	898	,   550	,	143	}, // 8 - Ship class "Typhoon"
    {	0	,	1041,	720	,	160	}, // 9 - Ship class "Hurricane"
    //{	0	,	960	,	720	,	160	} // 10 - Ship class "Hurricane"
    // {	0	,	320	,	550	,	143	}, // 6 - Troposphere
    // {	0	,	480	,	550	,	143	}, // 7 - Stratosphere
    // {	0	,	640	,   550	,	143	}, // 8 - Mesosphere
    // {	0	,	800	,	720	,	160	}, // 9 - Thermosphere
    // {	0	,	960	,	720	,	160	} // 10 - Exosphere
};

Sprite numberFont300;
S2D_Sprite *numberFont300img;
double nf300Sheet[10][4] = {
    {	0	,	0	,	170	,	250	},
    {	180	,	0	,   170	,	250	},
    {	360	,	0	,	170	,	250	},
    {	540	,	0	,	170	,	250	},
    {	720	,   0	,	170	,	250	},
    {	900	,	0	,	170	,	250	},
    {	1080,	0	,	170	,	250	},
    {   1260,	0	,	170	,	250	},
    {	1440,	0	,	170	,	250	},
    {	1620,	0	,	170	,	250  }
};

void defineImages() {
    #ifdef ROTATE
        numberFont80img = S2D_CreateSprite("number_font_80px_v.png");
        numberFont300img = S2D_CreateSprite("number_font_300px_v.png");
    #else
        numberFont80img = S2D_CreateSprite("number_font_80px.png");
        numberFont300img = S2D_CreateSprite("number_font_300px.png");
    #endif
    numberFont80img->x = 65;
    numberFont80img->y = 65;
    numberFont80.spr = numberFont80img;
    numberFont80.frames = 10;
    numberFont80.sheet = &nf80Sheet[0];
    numberFont80.width = 650;
    numberFont80.height = 65;

    numberFont300img->x = 65;
    numberFont300img->y = 65;
    numberFont300.spr = numberFont300img;
    numberFont300.frames = 10;
    numberFont300.sheet = &nf300Sheet[0];
    numberFont300.width = 1800;
    numberFont300.height = 250;

    #ifdef ROTATE
        gameImg = S2D_CreateSprite("game_sheet_v.png");
    #else
        gameImg = S2D_CreateSprite("game_sheet.png");
    #endif
    gameImg->x = 0;
    gameImg->y = 0;
    gameSprite.spr = gameImg;
    gameSprite.frames = 11;
    gameSprite.sheet = &gameSheet[0];
    gameSprite.width = 2048;
    gameSprite.height = 2058;

}

int numPlaces(int n){
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

void drawNumber(Sprite *sprite, int n, int x, int y){
    int digits = numPlaces(n);
    for (int i = digits; i>0; i--){
        // draw digits in order from right to left

        int digit = n % 10;
        n = n / 10;
        int currentX = x + ((i - 1) * sprite->sheet[0][3]);

        #ifdef ROTATE
            currentX = nomScreenWidth - currentX;
            S2D_ClipSprite(sprite->spr, sprite->sheet[digit][1], (sprite->width - sprite->sheet[digit][0] - sprite->sheet[digit][2]), sprite->sheet[digit][3], sprite->sheet[digit][2]);
            sprite->spr->y = currentX;
            sprite->spr->x = y;
            sprite->spr->height = sprite->sheet[0][2];
            sprite->spr->width = sprite->sheet[0][3];
        #else
            S2D_ClipSprite(sprite->spr, sprite->sheet[digit][0], sprite->sheet[digit][1], sprite->sheet[digit][2], sprite->sheet[digit][3]);
            sprite->spr->x = currentX;
            sprite->spr->y = y;
            sprite->spr->width = sprite->sheet[0][2];
            sprite->spr->height = sprite->sheet[0][3];
        #endif
        S2D_DrawSprite(sprite->spr);
    }
}

typedef struct Animation {
    int frame;
    int first;
    int last;
} Animation;

Animation titlePlayerSelect = {
    .frame = 0,
    .first = 0,
    .last = 0
};

Animation titleShipSelect = {
    .frame = 0,
    .first = 1,
    .last = 1
};

Animation onePAni = {
    .frame = 0,
    .first = 2,
    .last = 3
};

Animation twoPAni = {
    .frame = 0,
    .first = 4,
    .last = 5
};


void drawSprite2(Sprite *sprite, Animation *ani, int x, int y){
    int frame = ani->first + ani->frame;
    #ifdef ROTATE
        S2D_ClipSprite(sprite->spr, sprite->sheet[frame][1], (sprite->width - sprite->sheet[frame][0] - sprite->sheet[frame][2]), sprite->sheet[frame][3], sprite->sheet[frame][2]);
        sprite->spr->x = y;
        sprite->spr->y = nomScreenWidth - x - sprite->sheet[frame][2];
    #else
        S2D_ClipSprite(sprite->spr, sprite->sheet[frame][0], sprite->sheet[frame][1], sprite->sheet[frame][2], sprite->sheet[frame][3]);
        sprite->spr->x = x;
        sprite->spr->y = y;
    #endif
    S2D_DrawSprite(sprite->spr);
}


// OLD SPRITES
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

#endif /* SPRITES_H */
