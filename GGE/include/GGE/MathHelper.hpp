#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

// Interpolate between a and b with f
sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f);
float lerp(float a, float b, float f);

// Clamp a value within a range
sf::Vector2f clamp(sf::Vector2f value, float min, float max);