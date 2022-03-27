#include <cmath>
#include "MyDLAsteroidsFramework.h"
#include "Entity.h"

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
        float constSpeedX = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        float constSpeedY = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        constSpeedX = rand() % 2 ? constSpeedX : -constSpeedX;
        constSpeedY = rand() % 2 ? constSpeedY : -constSpeedY;
        enemy = new Entity(isBig ? bigEnemySprite : smallEnemySprite,
            constSpeedX, constSpeedY, x, y);
    }
}

void MyDLAsteroidsFramework::drawBackground() {
    static float deltaX = 0.0f;
    static float deltaY = 0.0f;
    deltaX += Entity::speedX;
    deltaY += Entity::speedY;
    
    if (deltaX > BackgroundSpriteWidth)
        deltaX -= BackgroundSpriteWidth;
    else if (deltaX < -BackgroundSpriteWidth)
        deltaX += BackgroundSpriteWidth;
    if (deltaY > BackgroundSpriteHeight)
        deltaY -= BackgroundSpriteHeight;
    else if (deltaY < -BackgroundSpriteHeight)
        deltaY += BackgroundSpriteHeight;
    
    for (int j = -1; j < ScreenHeight / BackgroundSpriteHeight + 2; j++) {
        for (int i = -1; i < ScreenWidth / BackgroundSpriteWidth + 2; i++) {
            drawSprite(BackgroundSprite,
                BackgroundSpriteWidth * i - deltaX - 3 * (i + 1),
                BackgroundSpriteHeight * j - deltaY - 3 * (j + 1));
        }
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
    // Removes all entities with these sprites
    destroySprite(BackgroundSprite);
    destroySprite(bigEnemySprite);
    destroySprite(smallEnemySprite);
    
    delete Character;
    delete Cursor;
}

bool MyDLAsteroidsFramework::Tick() {
    drawBackground();
    
    // Drawing entities
    Character->draw();
    Cursor->drawCentered();
    drawEnemies();
    
    // Moving entities
    moveEnemies();
    
    Entity::updateSpeed();
    
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
