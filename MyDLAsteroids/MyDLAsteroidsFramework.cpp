#include <cmath>
#include "MyDLAsteroidsFramework.h"
#include "Entity.h"
#include <iostream>

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

//void MyDLAsteroidsFramework::zone() {
//    for (int i = 0; i < Grid * Grid; i++)
//        Zones[i].clear();
//
//    static int row = ScreenWidth / Grid;
//    static int col = ScreenHeight / Grid;
//
//    // Zone all enemies
//    for (Entity* enemy : Enemies) {
//        int x1 = (int)enemy->x() / row;
//        int x2 = (int)(enemy->x() + enemy->width()) / row;
//        int y1 = (int)enemy->y() / col;
//        int y2 = (int)(enemy->y() + enemy->height()) / col;
//        int x1y1 = y1 * Grid + x1;
//        int x2y1 = y1 * Grid + x2;
//        int x1y2 = y2 * Grid + x1;
//        for (int j = x1y1; j <= x1y2; j += Grid)
//            for (int i = j; i <= j + (x2y1 - x1y1); i++)
//                Zones[i].emplace_back(enemy);
//    }
//
//    // Zone characters
//    static int x1 = (int)Character->x() / row;
//    static int x2 = (int)(Character->x() + Character->width()) / row;
//    static int y1 = (int)Character->y() / col;
//    static int y2 = (int)(Character->y() + Character->height()) / col;
//    static int x1y1 = y1 * Grid + x1;
//    static int x2y1 = y1 * Grid + x2;
//    static int x1y2 = y2 * Grid + x1;
//    for (int j = x1y1; j <= x1y2; j += Grid)
//        for (int i = j; i <= j + (x2y1 - x1y1); i++)
//            Zones[i].emplace_back(Character);
//    std::cout << "----ZONED----\n";
//}

void MyDLAsteroidsFramework::checkColisions() {
//    zone();
//
//    for (int z = 0; z < Grid * Grid; z++) {
//        for (int i = 0; i < Zones[z].size() - 1; i++) {
//            for (int j = i + 1; j < Zones[z].size(); j++) {
//                if (Zones[z][i]->colides(*Zones[z][j])) {
//                    std::cout << "Colision\n" << Zones[z][i]->x() << " " << Zones[z][i]->y() << "\n" << Zones[z][j]->x() << " " << Zones[z][j]->y() << std::endl;
//                }
//            }
//        }
//    }
    for (int i = 0; i < Enemies.size() - 1; i++) {
        for (int j = i + 1; j < Enemies.size(); j++) {
            if (Enemies[i]->colides(*Enemies[j])) {
                std::cout << "Colision\n" << Enemies[i]->x() << " " << Enemies[i]->y() << "\n" << Enemies[j]->x() << " " << Enemies[j]->y() << std::endl;
            }
        }
    }
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
    
    checkColisions();
    
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
