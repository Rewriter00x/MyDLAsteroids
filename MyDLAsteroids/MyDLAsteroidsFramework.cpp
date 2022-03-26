#include "MyDLAsteroidsFramework.h"
#include "Entity.h"
#include <cmath>

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
    Character = new Entity(createSprite("data/spaceship.png"));
    Cursor = new Entity(createSprite("data/circle.tga"));
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    
    if (!(BackgroundSprite && Character->sprite()))
        return false;
    
    Character->x() = ScreenWidth / 2;
    Character->y() = ScreenHeight / 2;
    
    return true;
}

void MyDLAsteroidsFramework::Close() {
    // Removes all background plates
    destroySprite(BackgroundSprite);
    
    delete Character;
    delete Cursor;
}

bool MyDLAsteroidsFramework::Tick() {
    // Wanted to draw background one time, but framework does not seem to have suck feature, so I'm drawing it every frame
    // Could not resize sprite, so drew it a bunch of times untill it filled the screen
    drawBackground();
    
    // Drawing entities
    Character->drawCentered();
    Cursor->drawCentered();
    
    // Moving entities
    Character->move();
    
    return false;
}

void MyDLAsteroidsFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    Cursor->x() = x;
    Cursor->y() = y;
}

void MyDLAsteroidsFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
}

void MyDLAsteroidsFramework::onKeyPressed(FRKey k) {
    Entity::shootingManager[k] = true;
}

void MyDLAsteroidsFramework::onKeyReleased(FRKey k) {
    Entity::shootingManager[k] = false;
}

const char* MyDLAsteroidsFramework::GetTitle() {
    return Title;
}
