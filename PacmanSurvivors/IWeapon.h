#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include "IEnemy.h"

class IWeapon {
public:
    virtual ~IWeapon() {}
    virtual void update(float dt,
        sf::Vector2f playerPos,
        std::vector<Projectile>& Projectile,
        const std::vector<std::unique_ptr<IEnemy>>& enemies) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};