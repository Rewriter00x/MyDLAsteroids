#include <cmath>
#include "MyDLAsteroidsFramework.h"
#include "Entity.h"

const char* MyDLAsteroidsFramework::Title = "MyDLAsteroids";

void MyDLAsteroidsFramework::inRange(Entity* e) {
    if (e->x() < -(e->width() + DeltaWidth))
        e->x() += e->width() + MapWidth;
    else if (e->x() > ScreenWidth + DeltaWidth)
        e->x() -= e->width() + MapWidth;
    if (e->y() < -(e->height() + DeltaHeight))
        e->y() += e->height() + MapHeight;
    else if (e->y() > ScreenHeight + DeltaHeight)
        e->y() -= e->height() + MapHeight;
}

void MyDLAsteroidsFramework::checkZoneCollision(int z) {
    for (int i = 0; i < Zones[z].size() == 0 ? 0 : Zones[z].size() - 1; i++)
        for (int j = i + 1; j < Zones[z].size(); j++)
            if (Zones[z][i]->collides(*Zones[z][j]))
                collided(Zones[z][i], Zones[z][j]);
}

bool MyDLAsteroidsFramework::collidesWithZone(int x, int y, int width, int height, int z) {
    for (Entity* enemy : Zones[z]) {
        if (enemy->collides(x, y, width, height))
            return true;
    }
    return false;
}

bool MyDLAsteroidsFramework::collidesWithZone(Entity* e, int z) {
    return collidesWithZone(e->x(), e->y(), e->width(), e->height(), z);
}

bool MyDLAsteroidsFramework::newColides(int x, int y, int width, int height) {
    int x1 = x <= -DeltaWidth || x + width >= ScreenWidth + DeltaWidth ? 0 : (int)(x + DeltaWidth) / GridWidth;
    int x2 = x <= -DeltaWidth || x + width >= ScreenWidth + DeltaWidth ? 0 : (int)(x + width + DeltaWidth) / GridWidth;
    int y1 = y <= -DeltaHeight || y + height >= ScreenHeight + DeltaHeight ? 0 : (int)(y + DeltaHeight) / GridHeight;
    int y2 = y <= -DeltaHeight || y + height >= ScreenHeight + DeltaHeight ? 0 : (int)(y + height + DeltaHeight) / GridHeight;
    int x1y1 = y1 * Grid + x1;
    int x2y1 = y1 * Grid + x2;
    int x1y2 = y2 * Grid + x1;
    for (int j = x1y1; j <= x1y2; j += Grid)
        for (int i = j; i <= j + (x2y1 - x1y1); i++)
            if (collidesWithZone(x, y, width, height, i))
                return true;
    return false;
}

void MyDLAsteroidsFramework::sendBack(Entity* e) {
    bool isBig = rand() % 2;
    int x, y, width, height , entityWidth, entityHeight, r;
    getSpriteSize(isBig ? BigEnemySprite : SmallEnemySprite, entityWidth, entityHeight);
    do {
        if (rand() % 2) {
            x = rand() % (MapWidth * 2) - MapWidth;
            r = DeltaHeight == 0 ? 0 : rand() % DeltaHeight;
            y = rand() % 2 ? -(r + entityHeight) : ScreenHeight + r;
        }
        else {
            r = DeltaWidth == 0 ? 0 : rand() % DeltaWidth;
            x = rand() % 2 ? -(r + entityWidth) : ScreenWidth + r;
            y = rand() % (MapHeight * 2) - MapHeight;
        }
        getSpriteSize(isBig ? BigEnemySprite : SmallEnemySprite, width, height);
    } while (newColides(x, y, width, height));
    float constSpeedX = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
    float constSpeedY = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
    constSpeedX = rand() % 2 ? constSpeedX : -constSpeedX;
    constSpeedY = rand() % 2 ? constSpeedY : -constSpeedY;
    e->x() = x;
    e->y() = y;
    e->constSpeedX() = constSpeedX;
    e->constSpeedY() = constSpeedY;
    e->setSprite(isBig ? BigEnemySprite : SmallEnemySprite);
}

void MyDLAsteroidsFramework::split(Entity* e) {
    
}

void MyDLAsteroidsFramework::flyApart(Entity* e1, Entity* e2) {
    float speedX = e1->constSpeedX();
    float speedY = e1->constSpeedY();
    e1->constSpeedX() = e2->constSpeedX();
    e1->constSpeedY() = e2->constSpeedY();
    e2->constSpeedX() = speedX;
    e2->constSpeedY() = speedY;
    while (e1->collides(*e2)) {
        e1->x() -= e1->constSpeedX();
        e2->x() -= e2->constSpeedX();
        e1->y() -= e1->constSpeedY();
        e2->y() -= e2->constSpeedY();
    }
}

void MyDLAsteroidsFramework::zoneEntity(Entity* e) {
    int x1 = e->x() <= -DeltaWidth || e->x() + e->width() >= ScreenWidth + DeltaWidth ? 0 : (int)(e->x() + DeltaWidth) / GridWidth;
    int x2 = e->x() <= -DeltaWidth || e->x() + e->width() >= ScreenWidth + DeltaWidth ? 0 : (int)(e->x() + e->width() + DeltaWidth) / GridWidth;
    int y1 = e->y() <= -DeltaHeight || e->y() + e->height() >= ScreenHeight + DeltaHeight ? 0 : (int)(e->y() + DeltaHeight) / GridHeight;
    int y2 = e->y() <= -DeltaHeight || e->y() + e->height() >= ScreenHeight + DeltaHeight ? 0 : (int)(e->y() + e->height() + DeltaHeight) / GridHeight;
    int x1y1 = y1 * Grid + x1;
    int x2y1 = y1 * Grid + x2;
    int x1y2 = y2 * Grid + x1;
    for (int j = x1y1; j <= x1y2; j += Grid)
        for (int i = j; i <= j + (x2y1 - x1y1); i++)
            Zones[i].push_back(e);
}

void MyDLAsteroidsFramework::zone() {
    for (int i = 0; i < Grid * Grid; i++)
        Zones[i].clear();

    // Zone all enemies
    for (Entity* enemy : Enemies)
        zoneEntity(enemy);
    
    // Zone character
    static int x1 = (int)(Character->x() + DeltaWidth) / GridWidth;
    static int x2 = (int)(Character->x() + Character->width() + DeltaWidth) / GridWidth;
    static int y1 = (int)(Character->y() + DeltaHeight) / GridHeight;
    static int y2 = (int)(Character->y() + Character->height() + DeltaHeight) / GridHeight;
    static int x1y1 = y1 * Grid + x1;
    static int x2y1 = y1 * Grid + x2;
    static int x1y2 = y2 * Grid + x1;
    for (int j = x1y1; j <= x1y2; j += Grid)
        for (int i = j; i <= j + (x2y1 - x1y1); i++)
            Zones[i].push_back(Character);
}

void MyDLAsteroidsFramework::collided(Entity* e1, Entity* e2) {
    // Actually, if any is character end game
    if (e1 == Character || e2 == Character) { // and now equals bullet
        bPaused = true;
        bGameOver = true;
        return;
    }
//    // If isBullet and smallEnemy sendback if big split
//    if (e1->getSprite() == smallEnemySprite)
//        sendBack(e1);
//    else
//        split(e1);
//    if (e2->getSprite() == smallEnemySprite)
//        sendBack(e2);
//    else
//        split(e2);
    flyApart(e1, e2);
}

void MyDLAsteroidsFramework::checkColisions() {
    zone();

    for (int z = 0; z < Grid * Grid; z++)
        checkZoneCollision(z);
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
    Enemies.clear();
    for (int i = 0; i < EnemyNumber; i++) {
        bool isBig = rand() % 2;
        int x, y, width, height;
        do {
            x = rand() % MapWidth - DeltaWidth * 2;
            y = rand() % MapHeight - DeltaHeight * 2;
            getSpriteSize(isBig ? BigEnemySprite : SmallEnemySprite, width, height);
        } while (Character->collides(x - Threshold, y - Threshold,
            width + Threshold * 2, height + Threshold * 2)
            || newColides(x, y, width, height));
        float constSpeedX = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        float constSpeedY = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        constSpeedX = rand() % 2 ? constSpeedX : -constSpeedX;
        constSpeedY = rand() % 2 ? constSpeedY : -constSpeedY;
        Enemies.push_back(new Entity(isBig ? BigEnemySprite
            : SmallEnemySprite, constSpeedX, constSpeedY, x, y));
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
    width = ScreenWidth;
    height = ScreenHeight;
    fullscreen = bFullscreen;
}

bool MyDLAsteroidsFramework::Init() {
    // if fullscreen update
    getScreenSize(ScreenWidth, ScreenHeight);
    
    if (MapWidth < ScreenWidth || MapHeight < ScreenHeight)
        return false;
    
    showCursor(false);
    
    BackgroundSprite = createSprite("data/background.png");
    
    Sprite* characterSprite = createSprite("data/spaceship.png");
    int characterWidth, characterHeight;
    getSpriteSize(characterSprite, characterWidth, characterHeight);
    Character = new Entity(characterSprite, 0.0f, 0.0f,
        (ScreenWidth - characterWidth) / 2, (ScreenHeight - characterHeight) / 2);
    
    Cursor = new Entity(createSprite("data/circle.tga"));
    
    GameOverSprite = createSprite("data/game_over.png");
    PauseSprite = createSprite("data/pause.png");
    
    BigEnemySprite = createSprite("data/big_asteroid.png");
    SmallEnemySprite = createSprite("data/small_asteroid.png");
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    
    if (!(BackgroundSprite && Character->getSprite() && Cursor->getSprite())
        && BigEnemySprite && SmallEnemySprite)
        return false;
    
    fillEnemies();
    
    return true;
}

void MyDLAsteroidsFramework::Close() {
    
    // Removes all entities with these sprites
    destroySprite(BackgroundSprite);
    destroySprite(GameOverSprite);
    destroySprite(PauseSprite);
    destroySprite(BigEnemySprite);
    destroySprite(SmallEnemySprite);
    destroySprite(Character->getSprite());
    destroySprite(Cursor->getSprite());
    
    delete Character;
    delete Cursor;
    for (Entity* enemy : Enemies)
        delete enemy;
}

bool MyDLAsteroidsFramework::Tick() {
    if (bPaused) {
        static int width, height;
        getSpriteSize(bGameOver ? GameOverSprite : PauseSprite, width, height);
        drawSprite(bGameOver ? GameOverSprite : PauseSprite,
            (ScreenWidth - width) / 2, (ScreenHeight - height) / 2);
        return false;
    }
    
    drawBackground();
    
    checkColisions();
    
    // Drawing entities
    Character->draw();
    drawEnemies();
    Cursor->drawCentered();
    
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
    if (isReleased)
        return;
    
    if (button == FRMouseButton::MIDDLE) {
        if (!bGameOver)
            bPaused = !bPaused;
        else {
            Entity::speedX = 0.0f;
            Entity::speedY = 0.0f;
            fillEnemies();
            bGameOver = false;
            bPaused = false;
        }
    }
        
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
