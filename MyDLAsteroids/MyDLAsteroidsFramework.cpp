#include <cmath>
#include <queue>
#include "MyDLAsteroidsFramework.h"
#include "Entity.h"

const char* MyDLAsteroidsFramework::Title = "MyDLAsteroids";

// Comparator for priority_queue for autoshoooting
struct DistanceCompare {
    static Entity* Character;

    bool operator()(Entity* lhs, Entity* rhs) {
        return Character->distance(*lhs) > Character->distance(*rhs);
    }
};

Entity* DistanceCompare::Character = nullptr;

MyDLAsteroidsFramework::MyDLAsteroidsFramework(int ScreenWidth, int ScreenHeight, int MapWidth, int MapHeight, int EnemyNumber, int Ammo, float AbilityChance)
    : ScreenWidth(ScreenWidth), ScreenHeight(ScreenHeight), MapWidth(MapWidth),
    MapHeight(MapHeight), EnemyNumber(EnemyNumber), Ammo(Ammo), AbilityChance(AbilityChance)
    {}

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

Rect MyDLAsteroidsFramework::getZones(int x, int y, int width, int height) {
    int x1 = x <= -DeltaWidth || x + width >= ScreenWidth + DeltaWidth ? 0 : (int)(x + DeltaWidth) / GridWidth;
    int x2 = x <= -DeltaWidth || x + width >= ScreenWidth + DeltaWidth ? 0 : (int)(x + width + DeltaWidth) / GridWidth;
    int y1 = y <= -DeltaHeight || y + height >= ScreenHeight + DeltaHeight ? 0 : (int)(y + DeltaHeight) / GridHeight;
    int y2 = y <= -DeltaHeight || y + height >= ScreenHeight + DeltaHeight ? 0 : (int)(y + height + DeltaHeight) / GridHeight;
    int x1y1 = y1 * Grid + x1;
    int x2y1 = y1 * Grid + x2;
    int x1y2 = y2 * Grid + x1;
    int x2y2 = y2 * Grid + y2;
    return Rect{x1y1, x2y1, x1y2, x2y2};
}

Rect MyDLAsteroidsFramework::getZones(Entity* e) {
    return getZones(e->x(), e->y(), e->width(), e->height());
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

bool MyDLAsteroidsFramework::newCollides(int x, int y, int width, int height) {
    Rect r = getZones(x, y, width, height);
    for (int j = r.x1y1; j <= r.x1y2; j += Grid)
        for (int i = j; i <= j + (r.x2y1 - r.x1y1); i++)
            if (collidesWithZone(x, y, width, height, i))
                return true;
    return false;
}

void MyDLAsteroidsFramework::spawnAbility(int x, int y) {
    Sprite* powerUpSprite;
    switch(rand() % 3) {
        case 0:
            powerUpSprite = AutoShootingPowerUpSprite;
            break;
        case 1:
            powerUpSprite = PowerShieldPowerUpSprite;
            break;
        case 2:
            powerUpSprite = HomingBulletPowerUpSprite;;
            break;
        default:
            return;
    }
    PowerUps.push_back(new Entity(powerUpSprite, 0.0f, 0.0f, x, y));
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
    } while (Character->collides(x - Threshold, y - Threshold,
        width + Threshold * 2, height + Threshold * 2) || newCollides(x, y, width, height));
    float constSpeedX = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
    float constSpeedY = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
    constSpeedX = rand() % 2 ? constSpeedX : -constSpeedX;
    constSpeedY = rand() % 2 ? constSpeedY : -constSpeedY;
    if (rand() % 101 <= (int)(AbilityChance * 100))
        spawnAbility(e->x(), e->y());
    e->x() = x;
    e->y() = y;
    e->constSpeedX() = constSpeedX;
    e->constSpeedY() = constSpeedY;
    e->setSprite(isBig ? BigEnemySprite : SmallEnemySprite);
}

void MyDLAsteroidsFramework::split(Entity* enemy, Entity* bullet) {
    enemy->x() -= enemy->width() / 2;
    enemy->y() -= enemy->height() / 2;
    enemy->setSprite(SmallEnemySprite);
    bullet->constSpeedX() /= Entity::maxSpeed / 2;
    bullet->constSpeedY() /= Entity::maxSpeed / 2;
    enemy->constSpeedX() = (enemy->constSpeedX() + bullet->constSpeedX()) / 2;
    enemy->constSpeedY() = (enemy->constSpeedY() + bullet->constSpeedY()) / 2;
    Enemies.push_back(
        new Entity(SmallEnemySprite, -enemy->constSpeedX(), -enemy->constSpeedY(),
        enemy->x() + enemy->width(), enemy->y() + enemy->height()));
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
    Rect r = getZones(e);
    for (int j = r.x1y1; j <= r.x1y2; j += Grid)
        for (int i = j; i <= j + (r.x2y1 - r.x1y1); i++)
            Zones[i].push_back(e);
}

void MyDLAsteroidsFramework::zoneEntities(std::vector<Entity*>& from) {
    for (Entity* e : from)
        zoneEntity(e);
}

void MyDLAsteroidsFramework::zone() {
    for (int i = 0; i < Grid * Grid; i++)
        Zones[i].clear();

    // Zone all enemies
    zoneEntities(Enemies);
    
    // Zone all bullets
    zoneEntities(Bullets);
    zoneEntities(AutoBullets);
    zoneEntities(HomingBullets);
    
    // Zone all powerUps
    zoneEntities(PowerUps);
    
    // Zone character
    for (int j = CharacterZones.x1y1; j <= CharacterZones.x1y2; j += Grid)
        for (int i = j; i <= j + (CharacterZones.x2y1 - CharacterZones.x1y1); i++)
            Zones[i].push_back(Character);
}

bool MyDLAsteroidsFramework::isAbility(Entity* e) {
    return e->getSprite() == AutoShootingPowerUpSprite || e->getSprite() == PowerShieldPowerUpSprite || e->getSprite() == HomingBulletPowerUpSprite;
}

void swap(Entity*& e1, Entity*& e2) {
    Entity* temp = e1;
    e1 = e2;
    e2 = temp;
}

void MyDLAsteroidsFramework::collided(Entity* e1, Entity* e2) {
    if ((e1 == Character && e2->getSprite() == BulletSprite) || (e2 == Character && e1->getSprite() == BulletSprite) || (e1->getSprite() == BulletSprite && e2->getSprite() == BulletSprite) || (isAbility(e1) && e2 != Character) || (e1 != Character && isAbility(e2)))
        return;
    
    if (isAbility(e2))
        swap(e1, e2);
    
    if (isAbility(e1)) {
        CurrentPowerUpSprite = e1->getSprite();
        bHasPowerUp = true;
        deleteEntity(e1, PowerUps);
        return;
    }
    
    if (e2 == Character)
        swap(e1, e2);
    
    if (e1 == Character) {
        if (bPowerShield) {
            e2->x() += e2->constSpeedX();
            e2->y() += e2->constSpeedY();
            return;
        }
        bPaused = true;
        bGameOver = true;
        return;
    }
    
    if (e2->getSprite() == BulletSprite)
        swap(e1, e2);
    
    if (e1->getSprite() == BulletSprite) {
        if (e2->getSprite() == SmallEnemySprite)
            sendBack(e2);
        else
            split(e2, e1);
        
        if (!deleteEntity(e1, Bullets))
            if (!deleteEntity(e1, AutoBullets))
                deleteEntity(e1, HomingBullets);
        return;
    }
    
    flyApart(e1, e2);
}

void MyDLAsteroidsFramework::autoShoot() {
    static std::priority_queue<Entity*, std::vector<Entity*>, DistanceCompare> distances;
    distances = std::priority_queue<Entity*, std::vector<Entity*>, DistanceCompare>();
    if (AutoShootingDelay.ended()) {
        for (int j = CharacterThreshold.x1y1; j <= CharacterThreshold.x1y2; j += Grid) {
            for (int i = j; i <= j + (CharacterThreshold.x2y1 - CharacterThreshold.x1y1); i++) {
                for (Entity* enemy : Zones[i]) {
                    if (enemy == Character || enemy->getSprite() == BulletSprite)
                        continue;
                    if (enemy->collides(Character->x() - Threshold, Character->y() - Threshold, Character->width() + Threshold * 2, Character->height() + Threshold * 2))   {
                        distances.push(enemy);
                    }
                }
            }
        }
        if (!distances.empty()) {
            Entity* t = distances.top();
            addAutoBullet(t);
            AutoShootingDelay.begin();
            distances.pop();
        }
    }
}

void MyDLAsteroidsFramework::checkCollisions() {
    zone();

    for (int z = 0; z < Grid * Grid; z++)
        checkZoneCollision(z);
    
    if (bAutoShooting)
        autoShoot();
}

void MyDLAsteroidsFramework::moveEntity(Entity* e) {
    e->move();
    inRange(e);
}

void MyDLAsteroidsFramework::moveEntityReverse(Entity* e) {
    e->moveReverse();
    inRange(e);
}

void MyDLAsteroidsFramework::moveEntities(std::vector<Entity*>& from) {
    for (Entity* e : from)
        moveEntityReverse(e);
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
            width + Threshold * 2, height + Threshold * 2) || newCollides(x, y, width, height));
        float constSpeedX = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        float constSpeedY = (float)(rand() % (int)(Entity::maxSpeed * 20.0f)) / 100.0f;
        constSpeedX = rand() % 2 ? constSpeedX : -constSpeedX;
        constSpeedY = rand() % 2 ? constSpeedY : -constSpeedY;
        Enemies.push_back(new Entity(isBig ? BigEnemySprite
            : SmallEnemySprite, constSpeedX, constSpeedY, x, y));
    }
}

Entity* MyDLAsteroidsFramework::createBullet(Entity* e) {
    static float x = Character->x() + (Character->width() - BulletSpriteWidth) / 2;
    static float y = Character->y() + (Character->height() - BulletSpriteHeight) / 2;
    float constSpeedX = e->x() - x;
    float constSpeedY = e->y() - y;
    float len = sqrtf(constSpeedX * constSpeedX + constSpeedY * constSpeedY);
    constSpeedX *= Entity::maxSpeed / -len;
    constSpeedY *= Entity::maxSpeed / -len;
    return new Entity(BulletSprite, constSpeedX, constSpeedY, x, y);
}

void MyDLAsteroidsFramework::addBullet() {
    if (Bullets.size() >= Ammo)
        Bullets.erase(Bullets.begin());
    Bullets.push_back(createBullet(Cursor));
}

void MyDLAsteroidsFramework::addAutoBullet(Entity* e) {
    if (AutoBullets.size() >= AutoAmmo)
        AutoBullets.erase(AutoBullets.begin());
    AutoBullets.push_back(createBullet(e));
}

void MyDLAsteroidsFramework::addHomingBullet(Entity* target) {
    Entity* bullet = createBullet(Cursor);
    if (target != nullptr ) {
        bullet->constSpeedX() += target->constSpeedX();
        bullet->constSpeedY() += target->constSpeedY();
    }
    HomingBullets.push_back(bullet);
}

bool MyDLAsteroidsFramework::deleteEntity(Entity* e, std::vector<Entity*>& from) {
    for (int i = 0; i < from.size(); i++)
        if (from[i] == e) {
            from.erase(from.begin() + i);
            return true;
        }
    return false;
}

void MyDLAsteroidsFramework::updateTimers() {
    ShootingDelay.tick();
    AutoShootingDelay.tick();
    AutoShootingDuration.tick();
    PowerShieldDuration.tick();
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

void MyDLAsteroidsFramework::drawEntities(std::vector<Entity *>& from) {
    for (Entity* e : from)
        e->draw();
}

void MyDLAsteroidsFramework::activatePowerUp() {
    if (CurrentPowerUpSprite == AutoShootingPowerUpSprite) {
        bAutoShooting = true;
        bHasPowerUp = false;
        AutoShootingDuration.begin();
        return;
    }
    if (CurrentPowerUpSprite == PowerShieldPowerUpSprite) {
        bPowerShield = true;
        bHasPowerUp = false;
        PowerShieldDuration.begin();
        return;
    }
    if (CurrentPowerUpSprite == HomingBulletPowerUpSprite) {
        bHasPowerUp = false;
        int zone = getZones(Cursor).x1y1;
        Entity* target = nullptr;
        for (Entity* enemy : Zones[zone]) {
            if (enemy->getSprite() != SmallEnemySprite && enemy->getSprite() != BigEnemySprite)
                continue;
            if (Cursor->collides(*enemy))
                target = enemy;
        }
        addHomingBullet(target);
    }
}

void MyDLAsteroidsFramework::checkPowerUpsEnded() {
    if (bAutoShooting && AutoShootingDuration.ended())
        bAutoShooting = false;
    if (bPowerShield && PowerShieldDuration.ended())
        bPowerShield = false;
}

void MyDLAsteroidsFramework::restart() {
    fillEnemies();
    Bullets.clear();
    AutoBullets.clear();
    HomingBullets.clear();
    PowerUps.clear();
    ShootingDelay.reset();
    AutoShootingDelay.reset();
    Entity::speedX = 0.0f;
    Entity::speedY = 0.0f;
    bGameOver = false;
    bPaused = false;
    bHasPowerUp = false;
}

void MyDLAsteroidsFramework::PreInit(int& width, int& height, bool& fullscreen) {
    width = ScreenWidth;
    height = ScreenHeight;
    fullscreen = bFullscreen;
}

bool MyDLAsteroidsFramework::Init() {
    if (bFullscreen)
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
    CharacterZones = getZones(Character);
    CharacterThreshold = getZones(Character->x() - Threshold, Character->y() - Threshold, Character->width() + Threshold * 2, Character->height() + Threshold * 2);
    DistanceCompare::Character = Character;
    
    PowerShieldSprite = createSprite("data/power_shield.png");
    
    Cursor = new Entity(createSprite("data/circle.tga"));
    
    GameOverSprite = createSprite("data/game_over.png");
    PauseSprite = createSprite("data/pause.png");
    
    BigEnemySprite = createSprite("data/big_asteroid.png");
    SmallEnemySprite = createSprite("data/small_asteroid.png");
    
    BulletSprite = createSprite("data/bullet.png");
    getSpriteSize(BulletSprite, BulletSpriteWidth, BulletSpriteHeight);
    
    getSpriteSize(BackgroundSprite, BackgroundSpriteWidth, BackgroundSpriteHeight);
    
    AutoShootingPowerUpSprite = createSprite("data/reticle.png");
    PowerShieldPowerUpSprite = createSprite("data/enemy.png");
    HomingBulletPowerUpSprite = createSprite("data/reticle_2.png");
    
    if (!(BackgroundSprite && Character->getSprite() && PowerShieldSprite && Cursor->getSprite() && BigEnemySprite && SmallEnemySprite && BulletSprite && AutoShootingPowerUpSprite && PowerShieldPowerUpSprite && HomingBulletPowerUpSprite))
        return false;
    
    restart();
    
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
    
    Enemies.clear();
    Bullets.clear();
    AutoBullets.clear();
    HomingBullets.clear();
    PowerUps.clear();
}

bool MyDLAsteroidsFramework::Tick() {
    if (bPaused) {
        static int width, height;
        getSpriteSize(bGameOver ? GameOverSprite : PauseSprite, width, height);
        drawSprite(bGameOver ? GameOverSprite : PauseSprite,
            (ScreenWidth - width) / 2, (ScreenHeight - height) / 2);
    }
    else {
        drawBackground();
        
        // Drawing entities
        drawEntities(Bullets);
        drawEntities(AutoBullets);
        drawEntities(HomingBullets);
        Character->draw();
        if (bPowerShield)
            drawSprite(PowerShieldSprite, Character->x(), Character->y());
        drawEntities(PowerUps);
        drawEntities(Enemies);
        
        // Moving entities
        moveEntities(Enemies);
        moveEntities(Bullets);
        moveEntities(AutoBullets);
        moveEntities(HomingBullets);
        moveEntities(PowerUps);
        
        if (bHasPowerUp)
            drawSprite(CurrentPowerUpSprite, 0, 0);
        
        checkCollisions();
        
        checkPowerUpsEnded();
        
        Entity::updateSpeed();
        
        updateTimers();
    }
    
    Cursor->drawCentered();
    
    return false;
}

void MyDLAsteroidsFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    Cursor->x() = x;
    Cursor->y() = y;
}

void MyDLAsteroidsFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (isReleased)
        return;
    
    if (bGameOver) {
        restart();
        return;
    }
    
    switch (button) {
        case FRMouseButton::LEFT:
            if (ShootingDelay.ended()) {
                addBullet();
                ShootingDelay.begin();
            }
            return;
            
        case FRMouseButton::MIDDLE:
            bPaused = !bPaused;
            return;
            
        case FRMouseButton::RIGHT:
            if (bHasPowerUp)
                activatePowerUp();
            return;
            
        default:
            return;
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
