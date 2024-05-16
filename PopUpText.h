#pragma once

#include "raylib.h"
#include <string>

struct PopUp {
    Vector2 position;
    float speedX;
    float speedY;
    std::string text;
    float time;
    float alpha;
};