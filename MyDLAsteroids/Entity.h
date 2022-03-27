#pragma once
#include "Framework.h"

// Singleton instance for controlling shooting direction
struct ShootingDirectionManager {
    bool& operator[](FRKey k) {
        switch (k) {
            case FRKey::LEFT:
                return bLeftKeyPressed;
            case FRKey::RIGHT:
                return bRightKeyPressed;
            case FRKey::UP:
                return bUpKeyPressed;
            case FRKey::DOWN:
                return bDownKeyPressed;
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
    
    bool bLeftKeyPressed = false;
    bool bRightKeyPressed = false;
    bool bUpKeyPressed = false;
    bool bDownKeyPressed = false;
};

class Entity {
    
    Sprite* _sprite;
    float _x, _y;
    const float _constSpeedX, _constSpeedY;
    int _width, _height;
    
public:
    static float speedX, speedY;
    static const float speedStep;
    static const float maxSpeed;
    static ShootingDirectionManager& shootingManager;
    
public:
    Entity(Sprite* s);
    
    Entity(Sprite* s, float constSpeedX, float constSpeedY);
    
    Entity(Sprite* s, float constSpeedX, float constSpeedY, float x, float y);
    
    ~Entity();
    
public:
    static void updateSpeed();
    void draw() const;
    void drawCentered() const;
    void move();
    void moveReverse();
    bool colides(const Entity& e) const;
    bool colides(float x, float y, int width, int height) const;
    void setSprite(Sprite* s);
    Sprite* const getSprite() const { return _sprite; }
    float& x() { return _x; }
    float& y() { return _y; }
    const float& x() const { return _x; }
    const float& y() const { return _y; }
    int width() const { return _width; }
    int height() const { return _height; }
};
