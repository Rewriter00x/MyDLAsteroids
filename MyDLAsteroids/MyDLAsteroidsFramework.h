#pragma once
#include <vector>
#include "Framework.h"
#include "Entity.h"

struct Rect {
    int x1y1, x2y1, x1y2, x2y2;
};

struct Timer {
    const float end, step;
    float current;
    
    Timer(float end, float step) : end(end), step(step), current(end) {}
    
    void begin() {
        current = 0.0f;
    }
    
    void reset() {
        current = end;
    }
    
    void tick() {
        if (ended())
            return;
        current += step;
        if (ended())
            reset();
    }
    
    bool ended() {
        return current >= end;
    }
};

class MyDLAsteroidsFramework : public Framework {
    
    static const int Grid = 4;
    static const int Threshold = 100;
    
    static const char* Title;
    const int EnemyNumber;
    const float AbilityChance;
    
    const int Ammo;
    const int AutoAmmo = 3;
    
    const bool bFullscreen = false;
    
    int ScreenWidth;
    int ScreenHeight;
    
    int MapWidth;
    int MapHeight;
    
    int DeltaWidth = (MapWidth - ScreenWidth) / 2;
    int DeltaHeight = (MapHeight - ScreenHeight) / 2;
    
    int GridWidth = MapWidth / Grid;
    int GridHeight = MapHeight / Grid;
    
    bool bPaused = false;
    bool bGameOver = false;
    
    bool bAutoShooting = false;
    bool bPowerShield = false;
    bool bHasPowerUp = false;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    
    int BulletSpriteWidth;
    int BulletSpriteHeight;
        
    Timer ShootingDelay = Timer(1.0f, 0.05f);
    Timer AutoShootingDelay = Timer(1.0f, 0.05f);
    Timer AutoShootingDuration = Timer(1.0f, 0.005f);
    Timer PowerShieldDuration = Timer(1.0f, 0.005f);
    
    Rect CharacterZones;
    Rect CharacterThreshold;
    
    Sprite* BackgroundSprite;
    Sprite* BigEnemySprite;
    Sprite* SmallEnemySprite;
    Sprite* BulletSprite;
    Sprite* PowerShieldSprite;
    Sprite* GameOverSprite;
    Sprite* PauseSprite;
    Sprite* AutoShootingPowerUpSprite;
    Sprite* PowerShieldPowerUpSprite;
    
    Sprite* CurrentPowerUpSprite;
    
    Entity* Character;
    Entity* Cursor;
    
    std::vector<Entity*> Enemies;
    std::vector<Entity*> Zones[Grid * Grid];
    std::vector<Entity*> Bullets;
    std::vector<Entity*> AutoBullets;
    std::vector<Entity*> PowerUps;
    
public:
    MyDLAsteroidsFramework(int ScreenWidth, int ScreenHeight, int MapWidth, int MapHeight, int EnemyNumber, int Ammo, float AbilityChance);
    
protected:
    void inRange(Entity* e);
    
    Rect getZones(int x, int y, int width, int height);
    
    Rect getZones(Entity* e);
    
    void checkZoneCollision(int z);
    
    bool collidesWithZone(int x, int y, int width, int height, int z);
    
    bool collidesWithZone(Entity* e, int z);
    
    bool newCollides(int x, int y, int width, int height);
    
    void spawnAbility(int x, int y);
    
    void sendBack(Entity* e);
    
    void split(Entity* enemy, Entity* bullet);
    
    void flyApart(Entity* e1, Entity* e2);
    
    void zoneEntity(Entity* e);
    
    void zone();
    
    bool isAbility(Entity* e);
    
    void collided(Entity* e1, Entity* e2);
    
    void autoShoot();
    
    void checkCollisions();
    
    void moveEntity(Entity* e);
    
    void moveEntityReverse(Entity* e);
    
    void moveEntities(std::vector<Entity*>& from);
    
    void fillEnemies();
    
    Entity* createBullet(Entity* e);
    
    void addBullet();
    
    void addBullet(Entity* e);
    
    bool deleteEntity(Entity* e, std::vector<Entity*>& from);
    
    void updateTimers();
    
    void drawBackground();
    
    void drawEntities(std::vector<Entity*>& from);
    
    void activatePowerUp();
    
    void checkPowerUpsEnded();
    
    void restart();

public:

    virtual void PreInit(int& width, int& height, bool& fullscreen) override;

    virtual bool Init() override;

    virtual void Close() override;

    virtual bool Tick() override;

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

    virtual void onKeyPressed(FRKey k) override;

    virtual void onKeyReleased(FRKey k) override;

    virtual const char* GetTitle() override;
};
