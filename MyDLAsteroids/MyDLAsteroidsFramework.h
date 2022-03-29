#pragma once
#include <vector>
#include "Framework.h"

class Entity;
struct Rect;

class MyDLAsteroidsFramework : public Framework {
    
    static const int Grid = 4;
    static const int Threshold = 100;
    
    static const char* Title;
    const int EnemyNumber = 100;
    
    const int Ammo = 3;
    
    const bool bFullscreen = false;
    
    int ScreenWidth = 1024;
    int ScreenHeight = 768;
    
    int MapWidth = ScreenWidth * 2;
    int MapHeight = ScreenHeight * 2;
    
    int DeltaWidth = (MapWidth - ScreenWidth) / 2;
    int DeltaHeight = (MapHeight - ScreenHeight) / 2;
    
    int GridWidth = MapWidth / Grid;
    int GridHeight = MapHeight / Grid;
    
    bool bPaused = false;
    bool bGameOver = false;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    
    int BulletSpriteWidth;
    int BulletSpriteHeight;
    
    Sprite* BackgroundSprite;
    Sprite* BigEnemySprite;
    Sprite* SmallEnemySprite;
    Sprite* BulletSprite;
    Sprite* GameOverSprite;
    Sprite* PauseSprite;
    
    Entity* Character;
    Entity* Cursor;
    
    std::vector<Entity*> Enemies;
    std::vector<Entity*> Zones[Grid * Grid];
    std::vector<Entity*> Bullets;
    
protected:
    void inRange(Entity* e);
    
    Rect getZones(int x, int y, int width, int height);
    
    Rect getZones(Entity* e);
    
    void checkZoneCollision(int z);
    
    bool collidesWithZone(int x, int y, int width, int height, int z);
    
    bool collidesWithZone(Entity* e, int z);
    
    bool newColides(int x, int y, int width, int height);
    
    void sendBack(Entity* e);
    
    void split(Entity* enemy, Entity* bullet);
    
    void flyApart(Entity* e1, Entity* e2);
    
    void zoneEntity(Entity* e);
    
    void zone();
    
    void collided(Entity* e1, Entity* e2);
    
    void checkColisions();
    
    void moveEntity(Entity* e);
    
    void moveEntityReverse(Entity* e);
    
    void moveEnemies();
    
    void moveBullets();
    
    void fillEnemies();
    
    void addBullet();
    
    void deleteBullet(Entity* e);
    
    void drawBackground();
    
    void drawEnemies();
    
    void drawBullets();
    
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
