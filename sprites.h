#include "gameDef.h"

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

Sprite gameSprite;
S2D_Sprite *gameImg;
double gameSheet[11][4] = {
    {	0	,	0	,	720	,	160	}, // 0 - Select players
    {	0	,	160	,   720	,	160	}, // 1 - Select your ship
    {	720	,	0	,   325	,	380	}, // 2 - 1 player selected
    {	1045,	0	,	325	,	380	}, // 3 - 1 player unselected
    {	1370,	0	,	325	,	380	}, // 4 - 2 player selected
    {	1695,	0	,   325	,	380	}, // 5 - 2 player unselected
    {	0	,	320	,	720	,	160	}, // 6 - Troposphere
    {	0	,	480	,	720	,	160	}, // 7 - Stratosphere
    {	0	,	640	,   720	,	160	}, // 8 - Mesosphere
    {	0	,	800	,	720	,	160	}, // 9 - Thermosphere
    {	0	,	960	,	720	,	160	}, // 10 - Exosphere
};

void defineImages() {
    #ifdef ROTATE
        numberFont80img = S2D_CreateSprite("number_font_80px_v.png");
    #else
        numberFont80img = S2D_CreateSprite("number_font_80px.png");
    #endif
    numberFont80img->x = 65;
    numberFont80img->y = 65;
    numberFont80.spr = numberFont80img;
    numberFont80.frames = 10;
    numberFont80.sheet = &nf80Sheet[0];
    numberFont80.width = 650;
    numberFont80.height = 65;

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

Animation still = {
    .frame = 0,
    .first = 0,
    .last = 0
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
