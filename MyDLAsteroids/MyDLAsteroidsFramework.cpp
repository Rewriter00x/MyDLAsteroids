#include "MyDLAsteroidsFramework.h"
#include "Entity.h"
#include <cmath>

const char* MyDLAsteroidsFramework::Title = "MyDLAsteroids";

void MyDLAsteroidsFramework::inRange(Entity* e) {
    if (e->x() < -e->width())
        e->x() += e->width() + ScreenWidth;
    else if (e->x() > ScreenWidth)
        e->x() -= e->width() + ScreenWidth;
    if (e->y() < -e->height())
        e->y() += e->height() + ScreenHeight;
    else if (e->y() > ScreenHeight)
        e->y() -= e->height() + ScreenHeight;
}

void MyDLAsteroidsFramework::moveEntity(Entity* e) {
    e->move();
    inRange(e);
}

void MyDLAsteroidsFramework::moveEntityReverse(Entity* e) {
    e->moveReverse();
    inRange(e);
}

void MyDLAsteroidsFramework::moveEnemies() {
    for (Entity*& enemy : Enemies)
        moveEntityReverse(enemy);
}

void MyDLAsteroidsFramework::fillEnemies() {
    for (Entity*& enemy : Enemies) {
        bool isBig = rand() % 2;
        int x, y, width, height;
        do {
            x = rand() % ScreenWidth;
            y = rand() % ScreenHeight;
            getSpriteSize(isBig ? bigEnemySprite : smallEnemySprite, width, height);
        } while (Character->colides(x, y, width, height));
        enemy = new Entity(isBig ? bigEnemySprite : smallEnemySprite,
            (float)(rand() % (int)(Entity::maxSpeed / 10 * 100)) / 100,
            (float)(rand() % (int)(Entity::maxSpeed / 10 * 100)) / 100, x, y);
    }
}

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

void MyDLAsteroidsFramework::drawEnemies() {
    for (Entity*& enemy : Enemies)
        enemy->draw();
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
    
    Sprite* characterSprite = createSprite("data/spaceship.png");
    int characterWidth, characterHeight;
    getSpriteSize(characterSprite, characterWidth, characterHeight);
    Character = new Entity(characterSprite, 0.0f, 0.0f,
        (ScreenWidth - characterWidth) / 2, (ScreenHeight - characterHeight) / 2);
    
    Cursor = new Entity(createSprite("data/circle.tga"));
    
    bigEnemySprite = createSprite("data/big_asteroid.png");
    smallEnemySprite = createSprite("data/small_asteroid.png");
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    
    if (!(BackgroundSprite && Character->getSprite() && Cursor->getSprite())
        && bigEnemySprite && smallEnemySprite)
        return false;
    
    fillEnemies();
    
    return true;
}

void MyDLAsteroidsFramework::Close() {
    // Removes all background plates
    destroySprite(BackgroundSprite);
    
    delete Character;
    delete Cursor;
    destroySprite(bigEnemySprite);
    destroySprite(smallEnemySprite);
}

bool MyDLAsteroidsFramework::Tick() {
    // Wanted to draw background one time, but framework does not seem to have suck feature, so I'm drawing it every frame
    // Could not resize sprite, so drew it a bunch of times untill it filled the screen
    drawBackground();
    
    // Drawing entities
    Character->draw();
    Cursor->drawCentered();
    
    drawEnemies();
    
    // Moving entities
    // moveEntity(Character);
    moveEnemies();
    
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
