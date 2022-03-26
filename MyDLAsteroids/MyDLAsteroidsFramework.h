#pragma once
#include "Framework.h"

class MyDLAsteroidsFramework : public Framework {
    
    static const char* Title;
    
    const int MaxSpeedX = 10;
    const int MaxSpeedY = 10;
    
    int ScreenWidth;
    int ScreenHeight;
    
    int CharacterSpeedX = 0;
    int CharacterSpeedY = 0;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    int CharacterSpriteWidth;
    int CharacterSpriteHeight;
    int MouseSpriteWidth;
    int MouseSpriteHeight;
    
    int CharacterX;
    int CharacterY;
    int MouseX;
    int MouseY;
    
    int KeyPressed = 0;
    
    Sprite* BackgroundSprite;
    Sprite* CharacterSprite;
    Sprite* MouseSprite;
    
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

};
