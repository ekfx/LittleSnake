#ifndef SNAKE_H
#define SNAKE_H

#include "Object.h"
#include "Core.h"

/*
    Remembering:
        its just a class that controls snake's position manipulating a object from Object.h,
        the interpretation is to the main program archive (LittleSnake.cpp)
*/

class Snake {
private:
    int TargetAxis = 0;
    int Direction = 0;
    float Left, Top, Right, Bottom;
    float Velocity;

public:
    void Start(std::vector<ObjectManager::Object>& Body, int quantity, float width, float height, float velocity);

    void Walk(std::vector<ObjectManager::Object>& Body);

    void SetDirectionAxis(int axis, int direction);
    void SetSpace(float width, float height, float v);
};

#endif // SNAKE_H