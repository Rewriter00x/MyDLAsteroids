#include <cmath>
#include "Entity.h"

const float Entity::speedStep = 0.05f;
const float Entity::maxSpeed = 5.0f;

float Entity::speedX = 0.0f;
float Entity::speedY = 0.0f;

ShootingDirectionManager& Entity::shootingManager = ShootingDirectionManager::Instance();

Entity::Entity(Sprite* s) : _sprite(s), _constSpeedX(0.0f), _constSpeedY(0.0f) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::Entity(Sprite* s, float constSpeedX, float constSpeedY)
    : _sprite(s), _constSpeedX(constSpeedX), _constSpeedY(constSpeedY), _x(0.0f), _y(0.0f) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::Entity(Sprite* s, float constSpeedX, float constSpeedY, float x, float y)
    : _sprite(s), _constSpeedX(constSpeedX), _constSpeedY(constSpeedY), _x(x), _y(y) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::~Entity() {
    destroySprite(_sprite);
}

void Entity::updateSpeed() {
    if (shootingManager[FRKey::LEFT]) {
        if (speedX > -maxSpeed)
            speedX += -speedStep;
    }
    else {
        if (speedX < 0.0f) {
            speedX -= -speedStep;
            speedX = speedX > 0.0f ? 0.0f : speedX;
        }
    }
    if (shootingManager[FRKey::RIGHT]) {
        if (speedX < maxSpeed)
            speedX += speedStep;
    }
    else {
        if (speedX > 0.0f) {
            speedX -= speedStep;
            speedX = speedX < 0.0f ? 0.0f : speedX;
        }
    }
    if (shootingManager[FRKey::UP]) {
        if (speedY > -maxSpeed)
            speedY += -speedStep;
    }
    else {
        if (speedY < 0.0f) {
            speedY -= -speedStep;
            speedY = speedY > 0.0f ? 0.0f : speedY;
        }
    }
    if (shootingManager[FRKey::DOWN]) {
        if (speedY < maxSpeed)
            speedY += speedStep;
    }
    else {
        if (speedY > 0.0f) {
            speedY -= speedStep;
            speedY = speedY < 0.0f ? 0.0f : speedY;
        }
    }
}

void Entity::draw() const {
    drawSprite(_sprite, _x, _y);
}

void Entity::drawCentered() const {
    drawSprite(_sprite, _x - _width / 2, _y - _height / 2);
}

void Entity::move() {
    _x += speedX + _constSpeedX;
    _y += speedY + _constSpeedY;
}

void Entity::moveReverse() {
    _x -= speedX + _constSpeedX;
    _y -= speedY + _constSpeedY;
}

bool Entity::colides(const Entity& e) const {
    return _x < e._x + e._width && _x + _width > e._x
        && _y < e._y + e._height && _y + _height > e._y;
}

bool Entity::colides(float x, float y, int width, int height) const {
    return _x < x + width && _x + _width > x
        && _y < y + height && _y + _height > y;
}

void Entity::setSprite(Sprite* s) {
    _sprite = s;
    getSpriteSize(s, _width, _height);
}
