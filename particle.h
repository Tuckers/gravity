#include "gameDef.h"
#include "color.h"
#include "drawing.h"
#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct Particle {
    int x;
    int y;
    int size;
    float velX;
    float velY;
    float acceleration;
    int life;
} Particle;

typedef struct Explosion {
    int x;
    int y;
    int startSize;
    float maxVelX;
    float maxVelY;
    int maxLife;
    int minLife;
    int magnitude;
    int quantity;
    Particle particles[100];
    bool generated;
    int count;
} Explosion;

Explosion kaboom = {
    .startSize = 50,
    .maxVelX = 10,
    .maxVelY = 20,
    .maxLife = 120,
    .minLife = 20,
    .magnitude = 200,
    .quantity = 100,
    .count = 0,
    .generated = false
};

void explode(Explosion *e, int x, int y){
    if (e->count == e->maxLife){
        e->generated = false;
        e->count = 0;
    }
    if (e->generated == false){
        e->x = x;
        e->y = y;
        for (int i = 0; i < e->quantity; i++){
            if (i % 4 == 0){
                e->particles[i].x = x + rand() % (e->startSize) + 1;
                e->particles[i].y = -(y + rand() % (e->startSize) + 1);
                e->particles[i].velX = ((float)rand() / (float)(RAND_MAX)) * 5;
                e->particles[i].velY = -((float)rand() / (float)(RAND_MAX)) * 5;
            }
            if (i % 4 == 1){
                e->particles[i].x = -(x + rand() % (e->startSize) + 1);
                e->particles[i].y = -(y + rand() % (e->startSize) + 1);
                e->particles[i].velX = -((float)rand() / (float)(RAND_MAX)) * 5;
                e->particles[i].velY = -((float)rand() / (float)(RAND_MAX)) * 5;
            }
            if (i % 4 == 2){
                e->particles[i].x = -(x + rand() % (e->startSize) + 1);
                e->particles[i].y = y + rand() % (e->startSize) + 1;
                e->particles[i].velX = -((float)rand() / (float)(RAND_MAX)) * 5;
                e->particles[i].velY = ((float)rand() / (float)(RAND_MAX)) * 5;
            }
            if (i % 4 == 3){
                e->particles[i].x = x + rand() % (e->startSize) + 1;
                e->particles[i].y = y + rand() % (e->startSize) + 1;
                e->particles[i].velX = ((float)rand() / (float)(RAND_MAX)) * 5;
                e->particles[i].velY = ((float)rand() / (float)(RAND_MAX)) * 5;
            }
            e->particles[i].x = x + rand() % (e->startSize) + 1;
            e->particles[i].y = y + rand() % (e->startSize) + 1;
            e->particles[i].size = rand() % (e->startSize / 4) + 1;
            e->particles[i].life = rand() % (e->maxLife) + 1;
            if (e->particles[i].life < e->minLife){
                e->particles[i].life = e->minLife;
            }
            //e->particles[i].acceleration = ((float)rand() / (float)(RAND_MAX)) + 0.7;
        }
        e->generated = true;
    }
    else {
        if (e->count < e->maxLife + 1){
            for (int i = 0; i < e->quantity; i++){
                //e->particles[i].velX *= e->particles[i].acceleration;
                //e->particles[i].velY *= e->particles[i].acceleration;
                e->particles[i].x += e->particles[i].velX;
                e->particles[i].y += e->particles[i].velY;
                e->particles[i].life--;
            }
        }
        e->count++;
    }
}

void drawParticles(Explosion *e){
    for (int i = 0; i < e->quantity; i++){
        if (e->particles[i].life > 0){
            if (e->particles[i].x < (e->x + e->magnitude) && e->particles[i].x > (e->x - e->magnitude)){
                if (e->particles[i].y < (e->y + e->magnitude) && e->particles[i].y > (e->x - e->magnitude)){
                    partColor.a = e->particles[i].life / 10;
                    partColor.g = (e->maxLife / 6) / e->particles[i].life;
                    partColor.b = (e->maxLife / 6) / e->particles[i].life;
                    drawParticle(e->particles[i].size, e->particles[i].x, e->particles[i].y, &partColor);
                }
            }
        }
    }
}


#endif /* CAPSULE_H */
