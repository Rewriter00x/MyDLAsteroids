#include <cmath>
#include "Entity.h"

const float Entity::speedStep = 0.05f;
const float Entity::maxSpeed = 5.0f;
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
        if (_speedX > -maxSpeed)
            _speedX += -speedStep;
    }
    else {
        if (_speedX < 0.0f) {
            _speedX -= -speedStep;
            _speedX = _speedX > 0.0f ? 0.0f : _speedX;
        }
    }
    if (shootingManager[FRKey::RIGHT]) {
        if (_speedX < maxSpeed)
            _speedX += speedStep;
    }
    else {
        if (_speedX > 0.0f) {
            _speedX -= speedStep;
            _speedX = _speedX < 0.0f ? 0.0f : _speedX;
        }
    }
    if (shootingManager[FRKey::UP]) {
        if (_speedY > -maxSpeed)
            _speedY += -speedStep;
    }
    else {
        if (_speedY < 0.0f) {
            _speedY -= -speedStep;
            _speedY = _speedY > 0.0f ? 0.0f : _speedY;
        }
    }
    if (shootingManager[FRKey::DOWN]) {
        if (_speedY < maxSpeed)
            _speedY += speedStep;
    }
    else {
        if (_speedY > 0.0f) {
            _speedY -= speedStep;
            _speedY = _speedY < 0.0f ? 0.0f : _speedY;
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
    _x += _speedX + _constSpeedX;
    _y += _speedY + _constSpeedY;
    updateSpeed();
}

void Entity::moveReverse() {
    _x -= _speedX + _constSpeedX;
    _y -= _speedY + _constSpeedY;
    updateSpeed();
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
