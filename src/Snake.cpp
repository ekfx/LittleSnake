#include "Snake.h"

void Snake::Start(std::vector<ObjectManager::Object>& Body, int quantity, float left, float top, float right, float bottom, float velocity) {
    /*
        Pode parecer estranho à primeira vista por conta do seu grid 40x40 mas o que acontece é que 
        as coordenadas da cobra são INDEPENDENTES do OpenGL, por isso é necessário diminuir
        a sua escala no loop for de render
    */

    Left = left;
    Right = right;
    Top = top;
    Bottom = bottom;
    Velocity = velocity;

    ObjectManager::Object TempObj;

    for (int i = 0; i < quantity; i++) {
        TempObj.position.x = 0;
        TempObj.position.y = 0;
        TempObj.position.z = 0;

        Body.push_back(TempObj);
    }
}

void Snake::Walk(std::vector<ObjectManager::Object>& Body) {
    for (int i = Body.size() - 1; i > 0; i--) {
        int j = i - 1;
        Body.at(i).position = Body.at(j).position;
    }


    // antecipar o movimento
    if (TargetAxis == ENGINE::AXIS::X_AXIS) {
        if (Body.at(0).position.x + (Velocity*Direction) > Left && 
            Body.at(0).position.x + (Velocity*Direction) < Right) {

            Body.at(0).position.x += (Velocity*Direction);
        } else {
            Body.at(0).position.x = -Body.at(0).position.x;
        }
    }

    if (TargetAxis == ENGINE::AXIS::Y_AXIS) {
        if (Body.at(0).position.y + (Velocity*Direction) > Bottom && 
            Body.at(0).position.y + (Velocity*Direction) < Top) {
                
            Body.at(0).position.y += (Velocity*Direction);
        } else {
            Body.at(0).position.y = -Body.at(0).position.y + (Velocity*Direction);
        }
    }

    std::cout << Body.at(0).position.x << " - " << Body.at(0).position.y << std::endl;

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

void Snake::SetSpace(float l, float t, float r, float b, float v) {
    Left         = l;
    Right        = r;
    Top          = t;
    Bottom       = b;
    Velocity     = v;
}