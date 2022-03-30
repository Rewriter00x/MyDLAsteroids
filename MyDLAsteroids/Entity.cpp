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

Entity::Entity(Sprite* s, float constSpeedX, float constSpeedY, float x, float y)
    : _sprite(s), _constSpeedX(constSpeedX), _constSpeedY(constSpeedY), _x(x), _y(y) {
    if (s)
        getSpriteSize(s, _width, _height);
}

Entity::~Entity() {}

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

float Entity::distance(const Entity& e) const {
    return distance(e.x(), e.y(), e.width(), e.height());
}

float Entity::distance(float x, float y, int width, int height) const {
    float x1 = _x + _width / 2;
    float y1 = _y + _height / 2;
    float x2 = x + width / 2;
    float y2 = y + height / 2;
    return pow(x1 - x2, 2.0f) + pow(y1 - y2, 2.0f);
}

bool Entity::collides(const Entity& e) const {
    return collides(e.x(), e.y(), e.width(), e.height());
}

bool Entity::collides(float x, float y, int width, int height) const {
    // Rect collision, replaced with circle
    // It is better to overlap a bit then die colliding air
//    return _x < x + width && _x + _width > x
//        && _y < y + height && _y + _height > y;
    return distance(x, y, width, height) <= pow((_height + height) / 2, 2);
}

void Entity::setSprite(Sprite* s) {
    _sprite = s;
    getSpriteSize(s, _width, _height);
}
