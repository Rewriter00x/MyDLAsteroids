#include "MyDLAsteroidsFramework.h"
#include <iostream>

const char* MyDLAsteroidsFramework::Title = "MyDLAsteroids";

void MyDLAsteroidsFramework::drawBackground() {
    int curWidth, curHeight;
    curWidth = curHeight = 0;
    while (curHeight < ScreenHeight) {
        while (curWidth < ScreenWidth) {
            drawSprite(BackgroundSprite, curWidth, curHeight);
            curWidth+=BackgroundSpriteWidth;
        }
        curHeight+=BackgroundSpriteHeight;
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
    // Removes all background plates
    destroySprite(BackgroundSprite);
    destroySprite(CharacterSprite);
    destroySprite(MouseSprite);
}

bool MyDLAsteroidsFramework::Tick() {
    // Wanted to draw background one time, but framework does not seem to have suck feature, so I'm drawing it every frame
    // Could not resize sprite, so drew it a bunch of times untill it filled the screen
    drawBackground();
    
    // Drawing character
    drawSprite(CharacterSprite, CharacterX - CharacterSpriteWidth / 2, CharacterY - CharacterSpriteHeight / 2);
    
    // Drawing cursor
    drawSprite(MouseSprite, MouseX - MouseSpriteWidth / 2, MouseY - MouseSpriteHeight / 2);
    
    // Character movenent
    CharacterX += CharacterSpeedX;
    CharacterY += CharacterSpeedY;
    
    // Character speed changing
    if (LeftKeyPressed) {
        if (abs(CharacterSpeedX) < MaxSpeed)
            CharacterSpeedX += -CharacterSpeed;
    }
    else {
        if (CharacterSpeedX < 0) {
            CharacterSpeedX -= -CharacterSpeed;
            if (CharacterSpeedX > 0)
                CharacterSpeedX = 0;
        }
    }
    if (RightKeyPressed) {
        if (abs(CharacterSpeedX) < MaxSpeed)
            CharacterSpeedX += CharacterSpeed;
    }
    else {
        if (CharacterSpeedX > 0) {
            CharacterSpeedX -= CharacterSpeed;
            if (CharacterSpeedX < 0)
                CharacterSpeedX = 0;
        }
    }
    if (UpKeyPressed) {
        if (abs(CharacterSpeedY) < MaxSpeed)
            CharacterSpeedY += -CharacterSpeed;
    }
    else {
        if (CharacterSpeedY < 0) {
            CharacterSpeedY -= -CharacterSpeed;
            if (CharacterSpeedY > 0)
                CharacterSpeedY = 0;
        }
    }
    if (DownKeyPressed) {
        if (abs(CharacterSpeedY) < MaxSpeed)
            CharacterSpeedY += CharacterSpeed;
    }
    else {
        if (CharacterSpeedY > 0) {
            CharacterSpeedY -= CharacterSpeed;
            if (CharacterSpeedY < 0)
                CharacterSpeedY = 0;
        }
    }
    return false;
}

void MyDLAsteroidsFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    MouseX = x;
    MouseY = y;
}

void MyDLAsteroidsFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
}

void MyDLAsteroidsFramework::onKeyPressed(FRKey k) {
    switch (k) {
        case FRKey::LEFT:
            LeftKeyPressed = true;
            break;
        case FRKey::RIGHT:
            RightKeyPressed = true;
            break;
        case FRKey::UP:
            UpKeyPressed = true;
            break;
        case FRKey::DOWN:
            DownKeyPressed = true;
            break;
    }
}

void MyDLAsteroidsFramework::onKeyReleased(FRKey k) {
    switch (k) {
        case FRKey::LEFT:
            LeftKeyPressed = false;
            break;
        case FRKey::RIGHT:
            RightKeyPressed = false;
            break;
        case FRKey::UP:
            UpKeyPressed = false;
            break;
        case FRKey::DOWN:
            DownKeyPressed = false;
            break;
    }
}

const char* MyDLAsteroidsFramework::GetTitle() {
    return Title;
}
