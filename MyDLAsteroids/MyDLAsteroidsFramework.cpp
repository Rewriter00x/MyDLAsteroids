#include "MyDLAsteroidsFramework.h"
#include <iostream>

const char* MyDLAsteroidsFramework::Title = "MyDLAsteroids";

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
    
    showCursor(false);
    
    BackgroundSprite = createSprite("data/background.png");
    CharacterSprite = createSprite("data/spaceship.png");
    MouseSprite = createSprite("data/circle.tga");
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    getSpriteSize(CharacterSprite, CharacterSpriteWidth, CharacterSpriteHeight);
    getSpriteSize(MouseSprite, MouseSpriteWidth, MouseSpriteHeight);
    
    if (!(BackgroundSprite && CharacterSprite))
        return false;
    
    CharacterX = ScreenWidth / 2;
    CharacterY = ScreenHeight / 2;
    
    return true;
}

void MyDLAsteroidsFramework::Close() {
    
}

bool MyDLAsteroidsFramework::Tick() {
    // Wanted to draw background one time, but framework does not seem to have suck feature, so I'm drawing it every frame
    // Could not resize sprite, so drew it a bunch of times untill it filled the screen
    drawBackground();
    
    // Drawing character
    drawSprite(CharacterSprite, CharacterX - CharacterSpriteWidth / 2, CharacterY - CharacterSpriteHeight / 2);
    
    // Drawing cursor
    drawSprite(MouseSprite, MouseX - MouseSpriteWidth / 2, MouseY - MouseSpriteHeight / 2);
    
    return false;
}

void MyDLAsteroidsFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    MouseX = x;
    MouseY = y;
}

void MyDLAsteroidsFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
}

void MyDLAsteroidsFramework::onKeyPressed(FRKey k) {
    
}

void MyDLAsteroidsFramework::onKeyReleased(FRKey k) {
    
}

const char* MyDLAsteroidsFramework::GetTitle() {
    return Title;
}
