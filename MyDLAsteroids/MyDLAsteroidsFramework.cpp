#include "MyDLAsteroidsFramework.h"
#include <iostream>

void MyDLAsteroidsFramework::drawBackground() {
    int bgWidth, bgHeight;
    getSpriteSize(BackgroundSprite, bgWidth, bgHeight);
    int curWidth, curHeight;
    curWidth = curHeight = 0;
    while (curHeight < ScreenHeight) {
        while (curWidth < ScreenWidth) {
            drawSprite(BackgroundSprite, curWidth, curHeight);
            curWidth+=bgWidth;
        }
        curHeight+=bgHeight;
        curWidth = 0;
    }
}

void MyDLAsteroidsFramework::PreInit(int& width, int& height, bool& fullscreen) {
    width = 1024;
    height = 768;
    fullscreen = false;
}

bool MyDLAsteroidsFramework::Init() {
    getScreenSize(ScreenWidth, ScreenHeight);
    
    BackgroundSprite = createSprite("data/background.png");
    CharacterSprite = createSprite("data/spaceship.png");
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    getSpriteSize(CharacterSprite, CharacterSpriteWidth, CharacterSpriteHeight);
    
    if (!(BackgroundSprite && CharacterSprite))
        return false;
    
    return true;
}

void MyDLAsteroidsFramework::Close() {
    
}

bool MyDLAsteroidsFramework::Tick() {
    // Wanted to draw background one time, but framework does not seem to have suck feature, so I'm drawing it every frame
    // Could not resize sprite, so drew it a bunch of times untill it filled the screen
    drawBackground();
    
    // Drawing character
    drawSprite(CharacterSprite, (ScreenWidth - CharacterSpriteWidth) / 2, (ScreenHeight - CharacterSpriteHeight) / 2);
    
    return false;
}

void MyDLAsteroidsFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    
}

void MyDLAsteroidsFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
}

void MyDLAsteroidsFramework::onKeyPressed(FRKey k) {
    
}

void MyDLAsteroidsFramework::onKeyReleased(FRKey k) {
    
}

const char* MyDLAsteroidsFramework::GetTitle() {
    return "MyDLAsteroids";
}
