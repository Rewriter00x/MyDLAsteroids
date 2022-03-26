#pragma once
#include "Framework.h"

class Entity;

class MyDLAsteroidsFramework : public Framework {
    
    static const char* Title;
    
    int ScreenWidth;
    int ScreenHeight;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    
    Sprite* BackgroundSprite;
    
    Entity* Character;
    Entity* Cursor;
    
protected:
    void drawBackground();

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
    
    void inRange(Entity* e);
    
    void moveEntity(Entity* e);

};
