#include "GGE/MathHelper.hpp"

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f) {
    return (a * (1.f - f)) + (b * f);
}

float lerp(float a, float b, float f){
    return (a * (1.f - f)) + (b * f);
}

sf::Vector2f clamp(sf::Vector2f value, float min, float max){
    return {std::max(min, std::min(max, value.x)), std::max(min, std::min(max, value.y))};
}