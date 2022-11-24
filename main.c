#include "raylib.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
// TODO make mapSectionMargin work to modify room sizes, add rooms and connect them
const int screenHeight = 720;
const int screenWidth = 1280;
const int targetFPS = 60;
const float mapSectionMargin = 0.2; // how many % magin from other map sections (1 = 100%)
const int iterations = 4;           // iterations for the generator

typedef struct mapSection_t
{
    Vector2 startPos;
    Vector2 endPos;
    struct mapSection_t *splitMapSections;
} mapSection_t;

void FreeBSPMap(int iterationCount, int desiredIterations, mapSection_t *mapSection)
{
    if (iterationCount < desiredIterations)
    {
        iterationCount++;
        FreeBSPMap(iterationCount, desiredIterations, (mapSection->splitMapSections));
        FreeBSPMap(iterationCount, desiredIterations, (mapSection->splitMapSections + 1));
    }
}

void DrawBSPMapSections(int iterationCount, int desiredIterations, mapSection_t mapSection)
{
    // printf("draw iteration: %d\n", iterationCount);
    //  getchar();
    //  fflush(stdin);
    DrawLineV(mapSection.splitMapSections[0].endPos, mapSection.splitMapSections[1].startPos, RED);
    if (iterationCount >= desiredIterations)
    {
    }
    else
    {
        iterationCount++;

        DrawBSPMapSections(iterationCount, desiredIterations, mapSection.splitMapSections[0]);
        // puts("wee");
        DrawBSPMapSections(iterationCount, desiredIterations, mapSection.splitMapSections[1]);
        // puts("wee 2");
    }
}

void GenerateBSPMapSections(int iterationCount, int desiredIterations, mapSection_t *mapSection)
{
    mapSection->splitMapSections = (mapSection_t *)calloc(2, sizeof(mapSection_t));
    printf("gen iteration: %d\n", iterationCount);

    if (rand() % 2)
    {
        puts("split in x");
        // splits in random place with atleast a 20% margin to the top/bottom
        // float xSplit = (((rand() % (int)(mapSection->endPos.x * (1 - (mapSectionMargin * 2)))) * 100) / 100) + (mapSection->endPos.x * mapSectionMargin);
        float xSplit = (mapSection->startPos.x + mapSection->endPos.x) / 2;
        mapSection->splitMapSections[0] = (mapSection_t){
            .startPos = (Vector2){mapSection->startPos.x, mapSection->startPos.y},
            .endPos = (Vector2){xSplit, mapSection->endPos.y}};

        mapSection->splitMapSections[1] = (mapSection_t){
            .startPos = (Vector2){xSplit, mapSection->startPos.y},
            .endPos = (Vector2){mapSection->endPos.x, mapSection->endPos.y}};
    }
    else
    {
        puts("split in y");
        // splits in random place with atleast a 20% margin to the left/right
        // float ySplit = (((rand() % (int)(mapSection->endPos.y * ( 1 - (mapSectionMargin * 2)))) * 100) / 100) + (mapSection->endPos.y * mapSectionMargin);
        float ySplit = (mapSection->startPos.y + mapSection->endPos.y) / 2;
        mapSection->splitMapSections[0] = (mapSection_t){
            .startPos = (Vector2){mapSection->startPos.x, mapSection->startPos.y},
            .endPos = (Vector2){mapSection->endPos.x, ySplit}};

        mapSection->splitMapSections[1] = (mapSection_t){
            .startPos = (Vector2){mapSection->startPos.x, ySplit},
            .endPos = (Vector2){mapSection->endPos.x, mapSection->endPos.y}};
    }
    if (iterationCount >= desiredIterations)
    {
        printf("all iterations complete: iterations: %d, desired iterations: %d\n",
               iterationCount, desiredIterations);
        // return;
    }
    else
    {
        iterationCount++;
        GenerateBSPMapSections(iterationCount, desiredIterations, (mapSection->splitMapSections));
        GenerateBSPMapSections(iterationCount, desiredIterations, (mapSection->splitMapSections + 1));
    }
}

int main()
{
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "map generation test");
    SetTargetFPS(targetFPS);

    int desiredIterations = 4;
    mapSection_t map = (mapSection_t){
        .startPos = (Vector2){0, 0},
        .endPos = (Vector2){screenWidth, screenHeight},
        .splitMapSections = NULL};

    GenerateBSPMapSections(0, desiredIterations, &map);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawBSPMapSections(0, desiredIterations, map);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}