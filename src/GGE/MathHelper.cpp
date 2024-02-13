#include "GGE/MathHelper.hpp"

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f) {
    return (a * (1.f - f)) + (b * f);
}