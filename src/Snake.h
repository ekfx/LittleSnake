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
    void Start(ObjectManager& Body, int quantity, float width, float height, float velocity);

    void Walk(ObjectManager& Body);

    void SetDirectionAxis(int axis, int direction);
    void SetSpace(float width, float height, float v);
    void Add(ObjectManager& Body);
    bool CheckCollision(ObjectManager& Body, ObjectManager& Fruit);
    void Chase(ObjectManager& Body, ObjectManager& Fruit);

    float GetLeft();
    float GetRight();
    float GetTop();
    float GetBottom();
};

#endif // SNAKE_H