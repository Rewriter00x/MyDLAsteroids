#include "Entity.h"
#include <cmath>

const float Entity::speedStep = 0.05f;
const float Entity::maxSpeed = 5.0f;
ShootingDirectionManager& Entity::shootingManager = ShootingDirectionManager::Instance();

Entity::Entity(Sprite* s) : _sprite(s), _constSpeedX(0.0f), _constSpeedY(0.0f) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::Entity(Sprite* s, float constSpeedX, float constSpeedY)
    : _sprite(s), _constSpeedX(constSpeedX), _constSpeedY(constSpeedY) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::~Entity() {
    destroySprite(_sprite);
}

void Entity::draw() {
    drawSprite(_sprite, _x, _y);
}

void Entity::drawCentered() {
    drawSprite(_sprite, _x - _width / 2, _y - _height / 2);
}

void Entity::move() {
    _x += _speedX + _constSpeedX;
    _y += _speedY + _constSpeedY;
    updateSpeed();
}

void Entity::updateSpeed() {
    if (Entity::shootingManager[FRKey::LEFT]) {
        if (abs(_speedX) < maxSpeed + _constSpeedX)
            _speedX += -speedStep;
    }
    else {
        if (_speedX < _constSpeedX) {
            _speedX -= -speedStep;
            if (_speedX > _constSpeedX)
                _speedX = _constSpeedX;
        }
    }
    if (Entity::shootingManager[FRKey::RIGHT]) {
        if (abs(_speedX) < maxSpeed + _constSpeedX)
            _speedX += speedStep;
    }
    else {
        if (_speedX > _constSpeedX) {
            _speedX -= speedStep;
            if (_speedX < _constSpeedX)
                _speedX = _constSpeedX;
        }
    }
    if (Entity::shootingManager[FRKey::UP]) {
        if (abs(_speedY) < maxSpeed + _constSpeedY)
            _speedY += -speedStep;
    }
    else {
        if (_speedY < _constSpeedY) {
            _speedY -= -speedStep;
            if (_speedY > _constSpeedY)
                _speedY = _constSpeedY;
        }
    }
    if (Entity::shootingManager[FRKey::DOWN]) {
        if (abs(_speedY) < maxSpeed + _constSpeedY)
            _speedY += speedStep;
    }
    else {
        if (_speedY > _constSpeedY) {
            _speedY -= speedStep;
            if (_speedY < _constSpeedY)
                _speedY = _constSpeedY;
        }
    }
}
