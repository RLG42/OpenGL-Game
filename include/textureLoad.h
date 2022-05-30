#pragma once

#include "SDL_image.h"


// Load Renderer
SDL_Renderer* renderer = NULL;

// Press Space Text
SDL_Surface* pressSpace = NULL;
SDL_Texture* pressSpacetexture = NULL;

// Score Number Text
SDL_Surface* score = NULL;
SDL_Texture* scoretexture = NULL;
SDL_Surface* score0 = NULL;
SDL_Texture* scoretexture0 = NULL;
SDL_Surface* score1 = NULL;
SDL_Texture* scoretexture1 = NULL;
SDL_Surface* score2 = NULL;
SDL_Texture* scoretexture2 = NULL;
SDL_Surface* score3 = NULL;
SDL_Texture* scoretexture3 = NULL;
SDL_Surface* score4 = NULL;
SDL_Texture* scoretexture4 = NULL;
SDL_Surface* score5 = NULL;
SDL_Texture* scoretexture5 = NULL;
SDL_Surface* score6 = NULL;
SDL_Texture* scoretexture6 = NULL;
SDL_Surface* score7 = NULL;
SDL_Texture* scoretexture7 = NULL;
SDL_Surface* score8 = NULL;
SDL_Texture* scoretexture8 = NULL;
SDL_Surface* score9 = NULL;
SDL_Texture* scoretexture9 = NULL;

// Level Text
SDL_Surface* level1 = NULL;
SDL_Texture* leveltexture1 = NULL;
SDL_Surface* level2 = NULL;
SDL_Texture* leveltexture2 = NULL;
SDL_Surface* level3 = NULL;
SDL_Texture* leveltexture3 = NULL;

// Life Text
SDL_Surface* lifes3 = NULL;
SDL_Texture* lifestexture3 = NULL;
SDL_Surface* lifes2 = NULL;
SDL_Texture* lifestexture2 = NULL;
SDL_Surface* lifes1 = NULL;
SDL_Texture* lifestexture1 = NULL;
SDL_Surface* lifes0 = NULL;
SDL_Texture* lifestexture0 = NULL;

// Ball Textures
SDL_Surface* ball = NULL;
SDL_Texture* balltexture = NULL;
SDL_Surface* ball2 = NULL;
SDL_Texture* balltexture2 = NULL;

// Bonus Laser
SDL_Surface* laser = NULL;
SDL_Texture* lasertexture = NULL;

// Extra Ball Text
SDL_Surface* bonusball = NULL;
SDL_Texture* bonusballtexture = NULL;

// Laser Text
SDL_Surface* bonuslaser = NULL;
SDL_Texture* bonuslasertexture = NULL;

// Lifelost
SDL_Surface* lifelost = NULL;
SDL_Texture* lifelosttexture = NULL;

// floor
SDL_Surface* floor1 = NULL;
SDL_Texture* floortexture1 = NULL;

// Brick1
SDL_Surface* brick1 = NULL;
SDL_Texture* bricktexture1 = NULL;

// Brick2
SDL_Surface* brick2 = NULL;
SDL_Texture* bricktexture2 = NULL;

// Winner
SDL_Surface* winner = NULL;
SDL_Texture* winnertexture = NULL;

// Gameover
SDL_Surface* gameover = NULL;
SDL_Texture* gameovertexture = NULL;

// Next Level
SDL_Surface* nextlevel = NULL;
SDL_Texture* nextleveltexture = NULL;

// Paddle
SDL_Surface* player = NULL;
SDL_Texture* playertexture = NULL;

// Background
SDL_Surface* background = NULL;
SDL_Texture* backgroundtexture = NULL;

// Size and position of images //

SDL_Rect pbackground = { 0,0,1920,1024 };
SDL_Rect pscore = { 550, 10, 120, 42 };
SDL_Rect pgameover = { 280, 280, 240, 100 };
SDL_Rect pscore3 = { 710, 10, 60, 42 };
SDL_Rect pwinner = { 280, 280, 240, 100 };

void loadTextures()

{

    // player
    player = IMG_Load("Images/player.png");
    playertexture = SDL_CreateTextureFromSurface(renderer, player);

    // Background
    background = IMG_Load("Images/background.png");
    backgroundtexture = SDL_CreateTextureFromSurface(renderer, background);

    // Floor
    floor1 = IMG_Load("Images/floor.png");
    floortexture1 = SDL_CreateTextureFromSurface(renderer, floor1);

    // Brick1
    brick1 = IMG_Load("Images/brick1.png");
    bricktexture1 = SDL_CreateTextureFromSurface(renderer, brick1);

    // Brick2
    brick2 = IMG_Load("Images/brick2.png");
    bricktexture2 = SDL_CreateTextureFromSurface(renderer, brick2);

    // Lives
    lifes3 = IMG_Load("Images/lifes3.png");
    lifestexture3 = SDL_CreateTextureFromSurface(renderer, lifes3);
    lifes2 = IMG_Load("Images/lifes2.png");
    lifestexture2 = SDL_CreateTextureFromSurface(renderer, lifes2);
    lifes1 = IMG_Load("Images/lifes1.png");
    lifestexture1 = SDL_CreateTextureFromSurface(renderer, lifes1);
    lifes0 = IMG_Load("Images/lifes0.png");
    lifestexture0 = SDL_CreateTextureFromSurface(renderer, lifes0);

    // Level
    level1 = IMG_Load("Images/level1.png");
    leveltexture1 = SDL_CreateTextureFromSurface(renderer, level1);
    level2 = IMG_Load("Images/level2.png");
    leveltexture2 = SDL_CreateTextureFromSurface(renderer, level2);
    level3 = IMG_Load("Images/level3.png");
    leveltexture3 = SDL_CreateTextureFromSurface(renderer, level3);

    // Score
    score = IMG_Load("Images/Score.png");
    scoretexture = SDL_CreateTextureFromSurface(renderer, score);

    // Score Numbers
    score0 = IMG_Load("Images/Score0.png");
    scoretexture0 = SDL_CreateTextureFromSurface(renderer, score0);
    score1 = IMG_Load("Images/Score1.png");
    scoretexture1 = SDL_CreateTextureFromSurface(renderer, score1);
    score2 = IMG_Load("Images/Score2.png");
    scoretexture2 = SDL_CreateTextureFromSurface(renderer, score2);
    score3 = IMG_Load("Images/Score3.png");
    scoretexture3 = SDL_CreateTextureFromSurface(renderer, score3);
    score4 = IMG_Load("Images/Score4.png");
    scoretexture4 = SDL_CreateTextureFromSurface(renderer, score4);
    score5 = IMG_Load("Images/Score5.png");
    scoretexture5 = SDL_CreateTextureFromSurface(renderer, score5);
    score6 = IMG_Load("Images/Score6.png");
    scoretexture6 = SDL_CreateTextureFromSurface(renderer, score6);
    score7 = IMG_Load("Images/Score7.png");
    scoretexture7 = SDL_CreateTextureFromSurface(renderer, score7);
    score8 = IMG_Load("Images/Score8.png");
    scoretexture8 = SDL_CreateTextureFromSurface(renderer, score8);
    score9 = IMG_Load("Images/Score9.png");
    scoretexture9 = SDL_CreateTextureFromSurface(renderer, score9);

    // Winner
    winner = IMG_Load("Images/winner.png");
    winnertexture = SDL_CreateTextureFromSurface(renderer, winner);

    // Gameover
    gameover = IMG_Load("Images/gameover.png");
    gameovertexture = SDL_CreateTextureFromSurface(renderer, gameover);

    // BonusLaser Text
    bonuslaser = IMG_Load("Images/bonuslaser.png");
    bonuslasertexture = SDL_CreateTextureFromSurface(renderer, bonuslaser);

    // BonusLaser
    laser = IMG_Load("Images/laser.png");
    lasertexture = SDL_CreateTextureFromSurface(renderer, laser);

    // Lifelost
    lifelost = IMG_Load("Images/lifelost.png");
    lifelosttexture = SDL_CreateTextureFromSurface(renderer, lifelost);

    // Next Level
    nextlevel = IMG_Load("Images/nextlevel.png");
    nextleveltexture = SDL_CreateTextureFromSurface(renderer, nextlevel);

    // PressSpace
    pressSpace = IMG_Load("Images/pressSpace.png");
    pressSpacetexture = SDL_CreateTextureFromSurface(renderer, pressSpace);

}

void levelText()
{
    // Level Text Render

    SDL_Rect plevel = { 350, 10, 120, 42 };

    if (level == 1) {
        SDL_RenderCopy(renderer, leveltexture1, NULL, &plevel);
    }
    else if (level == 2) {
        SDL_RenderCopy(renderer, leveltexture2, NULL, &plevel);
    }
    else if (level == 3) {
        SDL_RenderCopy(renderer, leveltexture3, NULL, &plevel);
    }
}

void lifeText()
{
    // Life Text Render

    SDL_Rect plifes = { 10, 10, 120, 42 };

    if (life == 3) {
        SDL_RenderCopy(renderer, lifestexture3, NULL, &plifes);
    }
    else if (life == 2) {
        SDL_RenderCopy(renderer, lifestexture2, NULL, &plifes);
    }
    else if (life == 1) {
        SDL_RenderCopy(renderer, lifestexture1, NULL, &plifes);
    }
    else {
        SDL_RenderCopy(renderer, lifestexture0, NULL, &plifes);
    }
}

void scoreRender()
{
    SDL_Rect pscore1 = { 670, 10, 60, 42 };
    SDL_Rect pscore2 = { 690, 10, 60, 42 };
    SDL_Rect pscore4 = { 650, 10, 60, 42 };

    // Player Score Render 10s

    if (playerScore / 10 == 1 || playerScore / 10 % 10 == 1) {
        SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore2);
    }
    else if (playerScore / 10 == 2 || playerScore / 10 % 10 == 2) {
        SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore2);
    }
    else if (playerScore / 10 == 3 || playerScore / 10 % 10 == 3) {
        SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore2);
    }
    else if (playerScore / 10 == 4 || playerScore / 10 % 10 == 4) {
        SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore2);
    }
    else if (playerScore / 10 == 5 || playerScore / 10 % 10 == 5) {
        SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore2);
    }
    else if (playerScore / 10 == 6 || playerScore / 10 % 10 == 6) {
        SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore2);
    }
    else if (playerScore / 10 == 7 || playerScore / 10 % 10 == 7) {
        SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore2);
    }
    else if (playerScore / 10 == 8 || playerScore / 10 % 10 == 8) {
        SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore2);
    }
    else if (playerScore / 10 == 9 || playerScore / 10 % 10 == 9) {
        SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore2);
    }
    else if (playerScore / 10 == 10 || playerScore / 10 % 10 == 0) {
        SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore2);
    }

    // Player Score Render 100s

    if (playerScore / 100 == 1 || playerScore / 100 % 10 == 1) {
        SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore1);
    }
    else if (playerScore / 100 == 2 || playerScore / 100 % 10 == 2) {
        SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore1);
    }
    else if (playerScore / 100 == 3 || playerScore / 100 % 10 == 3) {
        SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore1);
    }
    else if (playerScore / 100 == 4 || playerScore / 100 % 10 == 4) {
        SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore1);
    }
    else if (playerScore / 100 == 5 || playerScore / 100 % 10 == 5) {
        SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore1);
    }
    else if (playerScore / 100 == 6 || playerScore / 100 % 10 == 6) {
        SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore1);
    }
    else if (playerScore / 100 == 7 || playerScore / 100 % 10 == 7) {
        SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore1);
    }
    else if (playerScore / 100 == 8 || playerScore / 100 % 10 == 8) {
        SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore1);
    }
    else if (playerScore / 100 == 9 || playerScore / 100 % 10 == 9) {
        SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore1);
    }
    else if (playerScore / 100 == 10 || playerScore / 100 % 10 == 0) {
        SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore1);
    }

    // Player Score Render 1000s

    if (playerScore / 1000 == 1 || playerScore / 1000 % 10 == 1) {
        SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 2 || playerScore / 1000 % 10 == 2) {
        SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 3 || playerScore / 1000 % 10 == 3) {
        SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 4 || playerScore / 1000 % 10 == 4) {
        SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 5 || playerScore / 1000 % 10 == 5) {
        SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 6 || playerScore / 1000 % 10 == 6) {
        SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 7 || playerScore / 1000 % 10 == 7) {
        SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 8 || playerScore / 1000 % 10 == 8) {
        SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 9 || playerScore / 1000 % 10 == 9) {
        SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore4);
    }
    else if (playerScore / 1000 == 10 || playerScore / 1000 % 10 == 0) {
        SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore4);
    }
}