#pragma once
#include <array>
#include <vector>
#include "Framework.h"

class Entity;

class MyDLAsteroidsFramework : public Framework {
    
    static const int Grid = 4;
    
    static const char* Title;
    static const int EnemyNumber = 50;
    
    int ScreenWidth;
    int ScreenHeight;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    
    Sprite* BackgroundSprite;
    Sprite* bigEnemySprite;
    Sprite* smallEnemySprite;
    
    Entity* Character;
    Entity* Cursor;
    
    std::array<Entity*, EnemyNumber> Enemies;
    std::vector<Entity*> Zones[Grid * Grid];
    
protected:
    void inRange(Entity* e);
    
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
