#include "Snake.h"

void Snake::Start(std::vector<ObjectManager::Object>& Body, int quantity, float window_width, float window_height, float velocity) {
    /*
        Pode parecer estranho à primeira vista por conta do seu grid 40x40 mas o que acontece é que 
        as coordenadas da cobra são INDEPENDENTES do OpenGL, por isso é necessário diminuir
        a sua escala no loop for de render
    */

    float AspectRatio = window_width/window_height;
    float HeightSpace_ = 35.0f;

    float WidthSpace_ = HeightSpace_ * AspectRatio;

    Left         = -(WidthSpace_/2);
    Right        = +(WidthSpace_/2);
    Top          = +(HeightSpace_/2);
    Bottom       = -(HeightSpace_/2);
    Velocity     = velocity;

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