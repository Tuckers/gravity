#include "gameDef.h"
#ifndef DRAWING_H
#define DRAWING_H

///// BAR /////

///// POLYGONS /////
Point psPlayer1[6] = {
    {.x = 204, .y = 552}, {.x = 376, .y = 552}, {.x = 290, .y = 768},
    {.x = 221, .y = 564}, {.x = 359, .y = 564}, {.x = 290, .y = 726}
};

Point psPlayer2a[6] = {
    {.x = 708, .y = 393}, {.x = 880, .y = 393}, {.x = 794, .y = 610},
    {.x = 725, .y = 405}, {.x = 863, .y = 405}, {.x = 794, .y = 578}
};

Point psPlayer2b[6] = {
    {.x = 708, .y = 711}, {.x = 880, .y = 711}, {.x = 794, .y = 928},
    {.x = 725, .y = 723}, {.x = 863, .y = 723}, {.x = 794, .y = 896}
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

void drawTriangle(Point *v1, Point *v2, Point *v3, S2D_Color *color){
    #ifdef ROTATE
        S2D_DrawTriangle(
            v1->y, (nomScreenWidth - v1->x), color->r, color->g, color->b, color->a,
            v2->y, (nomScreenWidth - v2->x), color->r, color->g, color->b, color->a,
            v3->y, (nomScreenWidth - v3->x), color->r, color->g, color->b, color->a
        );
    #else
        S2D_DrawTriangle(
            v1->x, v1->y, color->r, color->g, color->b, color->a,
            v2->x, v2->y, color->r, color->g, color->b, color->a,
            v3->x, v3->y, color->r, color->g, color->b, color->a
        );
    #endif
}

void rotatePoint(Point *point, float degrees){
  int x = point->x;
  int y = point->y;
  point->x = x * cos(degrees) - y * sin(degrees);
  point->y = y * cos(degrees) + x * sin(degrees);
}

void drawShockwave(int x, int y, int width, int height, float degrees, S2D_Color *color){
  Point v1 = {
    .x = (-width / 2),
    .y = (-height)
  };
  Point v2 = {
    .x = (width / 2),
    .y = (-height)
  };
  Point v3 = {
    .x = 0,
    .y = (25)
  };
  rotatePoint(&v1, degrees);
  rotatePoint(&v2, degrees);
  rotatePoint(&v3, degrees);
  //
  // v1.x += x + width / 2 - rand() % 50;
  // v2.x += x + width / 2 - rand() % 50;
  // v3.x += x + width / 2;
  // v1.y += y + height / 2 - rand() % 50;
  // v2.y += y + height / 2 - rand() % 50;
  // v3.y += y + height / 2;
  v1.x += x - rand() % 25 + 25;
  v2.x += x + rand() % 25 + 25;
  v3.x += x + 25;
  v1.y += y - rand() % 5 + 25;
  v2.y += y - rand() % 5 + 25;
  v3.y += y + 40;

  float bMod = (rand() % 5 / 1) + .4;
  #ifdef ROTATE
      S2D_DrawTriangle(
          v1.y, (nomScreenWidth - v1.x), color->r, color->g, bMod, 0,
          v2.y, (nomScreenWidth - v2.x), color->r, color->g, bMod, 0,
          v3.y, (nomScreenWidth - v3.x), color->r, color->g, bMod, .75
      );
  #else
      S2D_DrawTriangle(
          v1.x, v1.y, color->r, color->g, bMod, 0,
          v2.x, v2.y, color->r, color->g, bMod, 0,
          v3.x, v3.y, color->r, color->g, bMod, .75
      );
  #endif
}

void drawParticle(int size, int x, int y, S2D_Color *color){
    #ifdef ROTATE
    S2D_DrawTriangle(
        y - (size / 2), (nomScreenWidth - x + (size / 2)), color->r, color->g, color->b, color->a,
        y - (size / 2), (nomScreenWidth - x - (size / 2)), color->r, color->g, color->b, color->a,
        y + (size / 2), (nomScreenWidth - x), color->r, color->g, color->b, color->a
    );
    #else
        S2D_DrawTriangle(
            x + (size / 2), y - (size / 2), color->r, color->g, color->b, color->a,
            x - (size / 2), y - (size / 2), color->r, color->g, color->b, color->a,
            x, y + (size / 2), color->r, color->g, color->b, color->a
        );
    #endif
}

void drawQuad(Point *v1, Point *v2, Point *v3, Point *v4, S2D_Color *color){
    #ifdef ROTATE
        S2D_DrawQuad(
            v1->y, (nomScreenWidth - v1->x), color->r, color->g, color->b, color->a,
            v2->y, (nomScreenWidth - v2->x), color->r, color->g, color->b, color->a,
            v3->y, (nomScreenWidth - v3->x), color->r, color->g, color->b, color->a,
            v4->y, (nomScreenWidth - v4->x), color->r, color->g, color->b, color->a
        );
    #else
        S2D_DrawQuad(
            v1->x, v1->y, color->r, color->g, color->b, color->a,
            v2->x, v2->y, color->r, color->g, color->b, color->a,
            v3->x, v3->y, color->r, color->g, color->b, color->a,
            v4->x, v4->y, color->r, color->g, color->b, color->a
        );
    #endif


}

void drawBar(int x, int y, int width, int height, float percent, S2D_Color *color){
    color->a = 0.5;
    drawRectangle(x, y, width, height, color);
    color->a = 1;
    drawRectangle(x, y, (width * percent), height, color);
}


void drawPolygon(Point (*points), int size, S2D_Color *color, bool hollow){
    size = size / 2;
    if (hollow == true){
        ///// HOLLOW RENDERING /////
        for (int i = 0; i < size; i++){
            if (i == size - 1){
                drawTriangle(&points[i], &points[0], &points[(i + size)], color);
                drawTriangle(&points[(i + size)], &points[0], &points[(0 + size)], color);
            }
            else {
                drawTriangle(&points[i], &points[(i + 1)], &points[(i + size)], color);
                drawTriangle(&points[(i + size)], &points[(i + 1)], &points[(i + 1 + size)], color);
            }
        }
    }
    else {
        ///// SOLID RENDERING /////
        if (size == 3){
            drawTriangle(&points[0], &points[1], &points[2], color);
        }
        else {
            drawTriangle(&points[4], &points[2], &points[3], color);
            drawQuad(&points[0], &points[1], &points[2], &points[4], color);
        }
    }
}



#endif /* DRAWING_H */
