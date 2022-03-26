#pragma once
#include "Framework.h"

class MyDLAsteroidsFramework : public Framework {
    
    static const char* Title;
    
    const float MaxSpeed = 5.0f;
    const float CharacterSpeed = 0.05f;
    
    int ScreenWidth;
    int ScreenHeight;
    
    float CharacterSpeedX = 0;
    float CharacterSpeedY = 0;
    
    int BackgroundSpriteWidth;
    int BackgroundSpriteHeight;
    int CharacterSpriteWidth;
    int CharacterSpriteHeight;
    int MouseSpriteWidth;
    int MouseSpriteHeight;
    
    float CharacterX;
    float CharacterY;
    int MouseX;
    int MouseY;
    
    bool LeftKeyPressed = false;
    bool RightKeyPressed = false;
    bool UpKeyPressed = false;
    bool DownKeyPressed = false;
    
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
