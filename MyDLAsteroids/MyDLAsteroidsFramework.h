#pragma once
#include "Framework.h"

// Singleton instance for controlling shooting direction
struct ShootingDirectionManager {
    bool& operator[](FRKey k) {
        switch (k) {
            case FRKey::LEFT:
                return LeftKeyPressed;
            case FRKey::RIGHT:
                return RightKeyPressed;
            case FRKey::UP:
                return UpKeyPressed;
            case FRKey::DOWN:
                return DownKeyPressed;
            default:
                throw k;
        }
    }
    
    static ShootingDirectionManager& Instance() {
        static ShootingDirectionManager Instance;
        return Instance;
    }
    
private:
    ShootingDirectionManager() {}
    ShootingDirectionManager(const ShootingDirectionManager&) = delete;
    ShootingDirectionManager& operator=(const ShootingDirectionManager&) = delete;
    
    bool LeftKeyPressed = false;
    bool RightKeyPressed = false;
    bool UpKeyPressed = false;
    bool DownKeyPressed = false;
};

class MyDLAsteroidsFramework : public Framework {
    
    static const char* Title;
    
    ShootingDirectionManager& ShootingManager = ShootingDirectionManager::Instance();
    
    const float MaxSpeed = 5.0f;
    const float CharacterSpeed = 0.05f;
    
    int ScreenWidth;
    int ScreenHeight;
    
    float CharacterSpeedX = 0.0f;
    float CharacterSpeedY = 0.0f;
    
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
