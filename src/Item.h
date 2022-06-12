#pragma once

#include "Point.h"
#include "IObject.h"
#include <string>

class Item : public IObject
{
public:
    float dropTime = 0;

    std::string type = "none";

    Item(std::string t, float eTime);
    ~Item();

    Point position;
    Point getRandPosition();

    void Update(float eTime);
    void Render();
};