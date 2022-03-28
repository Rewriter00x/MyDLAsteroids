#pragma once
#include <vector>
#include "Framework.h"

class Entity;

class MyDLAsteroidsFramework : public Framework {
    
    static const int Grid = 4;
    static const int Threshold = 100;
    
    static const char* Title;
    static const int EnemyNumber = 100;
    
    bool bPaused = false;
    bool bGameOver = false;
    
    const bool bFullscreen = false;
    
    int ScreenWidth = 1024;
    int ScreenHeight = 768;
    
    int MapWidth = ScreenWidth * 2;
    int MapHeight = ScreenHeight * 2;
    
    int DeltaWidth = (MapWidth - ScreenWidth) / 2;
    int DeltaHeight = (MapHeight - ScreenHeight) / 2;
    
    int GridWidth = MapWidth / Grid;
    int GridHeight = MapHeight / Grid;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    
    Sprite* BackgroundSprite;
    Sprite* BigEnemySprite;
    Sprite* SmallEnemySprite;
    Sprite* GameOverSprite;
    Sprite* PauseSprite;
    
    Entity* Character;
    Entity* Cursor;
    
    std::vector<Entity*> Enemies;
    std::vector<Entity*> Zones[Grid * Grid];
    
protected:
    void inRange(Entity* e);
    
    void checkZoneCollision(int z);
    
    bool newColides(int x, int y, int width, int height);
    
    void sendBack(Entity* e);
    
    void split(Entity* e);
    
    void flyApart(Entity* e1, Entity* e2);
    
    void zoneEntity(Entity* e);
    
    void zone();
    
    void collided(Entity* e1, Entity* e2);
    
    void checkColisions();
    
    void moveEntity(Entity* e);
    
    void moveEntityReverse(Entity* e);
    
    void moveEnemies();
    
    void fillEnemies();
    
    void drawBackground();
    
    void drawEnemies();

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
