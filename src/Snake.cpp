#include "Snake.h"

void Snake::Start(ObjectManager& Body, int quantity, float window_width, float window_height, float velocity) {
    /*
        Pode parecer estranho à primeira vista por conta do seu grid 40x40 mas o que acontece é que 
        as coordenadas da cobra são INDEPENDENTES do OpenGL, por isso é necessário diminuir
        a sua escala no loop for de render
    */

    float AspectRatio = window_width/window_height;
    float HeightSpace_ = 28.0f;

    float WidthSpace_ = HeightSpace_ * AspectRatio;

    Left         = -(WidthSpace_/2);
    Right        = +(WidthSpace_/2);
    Top          = +(HeightSpace_/2);
    Bottom       = -(HeightSpace_/2);
    Velocity     = velocity;

    for (int i = 0; i < quantity; i++) {
        Body.ObjectArray.push_back({});
    }
}

void Snake::Walk(ObjectManager& Body) {
    for (int i = Body.ObjectArray.size() - 1; i > 0; i--) {
        int j = i - 1;
        Body.ObjectArray.at(i).position = Body.ObjectArray.at(j).position;
    }


    // antecipar o movimento
    if (TargetAxis == ENGINE::AXIS::X_AXIS) {
        if (Body.ObjectArray.at(0).position.x + (Velocity*Direction) > Left && 
            Body.ObjectArray.at(0).position.x + (Velocity*Direction) < Right) {

            Body.ObjectArray.at(0).position.x += (Velocity*Direction);
        } else {
            Body.ObjectArray.at(0).position.x = -Body.ObjectArray.at(0).position.x;
        }
    }

    if (TargetAxis == ENGINE::AXIS::Y_AXIS) {
        if (Body.ObjectArray.at(0).position.y + (Velocity*Direction) > Bottom && 
            Body.ObjectArray.at(0).position.y + (Velocity*Direction) < Top) {
                
            Body.ObjectArray.at(0).position.y += (Velocity*Direction);
        } else {
            Body.ObjectArray.at(0).position.y = -Body.ObjectArray.at(0).position.y + (Velocity*Direction);
        }
    }

    /*
        Funcionamento comum da cobrinha:
            puxa para a posição atual a posicao posterior
            e no fim atualiza a cabeca
    */
}

void Snake::SetDirectionAxis(int axis, int direction) {
    TargetAxis   = axis;
    Direction    = direction;
}

void Snake::SetSpace(float window_width, float window_height, float v) {
    float AspectRatio = window_width/window_height;
    float HeightSpace_ = 35.0f;

    float WidthSpace_ = HeightSpace_ * AspectRatio;
    /*
        vai fazer um espaco x proporcional a altura.
        
        1920x1080
        35.0 * 1.88 = 65.8

        800x600
        35.0 * 1.33 = 46.5
    */

    Left         = -(WidthSpace_/2);
    Right        = +(WidthSpace_/2);
    Top          = +(HeightSpace_/2);
    Bottom       = -(HeightSpace_/2);
    Velocity     = v;
}

void Snake::Add(ObjectManager& Body) {
    Body.ObjectArray.push_back(Body.ObjectArray.at(0));
}

bool Snake::CheckCollision(ObjectManager& Body, ObjectManager& Fruit) {
    if (Body.ObjectArray.at(0).position.x <= Fruit.ObjectArray.at(0).position.x + 1.1f &&
        Body.ObjectArray.at(0).position.x >= Fruit.ObjectArray.at(0).position.x - 1.1f &&
        Body.ObjectArray.at(0).position.y <= Fruit.ObjectArray.at(0).position.y + 1.1f &&
        Body.ObjectArray.at(0).position.y >= Fruit.ObjectArray.at(0).position.y - 1.1f) {
            return true;
    }
    return false;
}

void Snake::Chase(ObjectManager& Body, ObjectManager& Fruit) {
    if (Fruit.ObjectArray.at(0).position.x > Body.ObjectArray.at(0).position.x) {
        SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::FORWARD);
    } else if (Fruit.ObjectArray.at(0).position.x < Body.ObjectArray.at(0).position.x) {
        SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::BACKWARD);
    } 
    if (Fruit.ObjectArray.at(0).position.y > Body.ObjectArray.at(0).position.y) {
        SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::FORWARD);
    } else if (Fruit.ObjectArray.at(0).position.y < Body.ObjectArray.at(0).position.y) {
        SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::BACKWARD);
    } 
}

float Snake::GetLeft() {
    return Left;
}

float Snake::GetRight() {
    return Right;
}

float Snake::GetTop() {
    return Top;
}

float Snake::GetBottom() {
    return Bottom;
}
