#ifndef LITTLESNAKE_H
#define LITTLESNAKE_H

#include "Program.h"
#include "Snake.h"

class LittleSnake : public Program {
private:
    

    /////////////////////    
    // Properties
    f32 CameraZoom = 1.0f;
    f32 SnakeTick = 35.0f;
    f32 SnakeDistanceParts = 1.0f;
    bool AI = 1;

    /////////////////////

    Shader GlobalShader;
    HUD MyHUD;

    Mesh MyMesh;
    Texture MyTexture;
    glm::mat4 MyModel;
    
    ObjectManager Fruits;
    
    ObjectManager MySnake;
    Snake snake;

    ObjectManager MyEnemy;
    Snake enemy;

    // Vertex
    u32 MyEBO[6] {
        0, 1, 2,
        2, 3, 0,
    };

    // Default Vertex
    Mesh::vertex MyVertex[4] {         // Padrão
        // X      Y       Z  |  R      G     B  |    U     V
        {-0.50f, -0.50f,  0.0f, 1.0f,  1.0f,  0.0f,  0.00f, 0.00f}, // bottom left
        { 0.50f, -0.50f,  0.0f, 0.0f,  0.85f, 0.0f,  1.00f, 0.00f}, // bottom right
        { 0.50f,  0.50f,  0.0f, 0.85f, 0.0f,  0.0f,  1.00f, 1.00f},  // top right
        {-0.50f,  0.50f,  0.0f, 0.0f,  0.0f,  0.85f, 0.00f, 1.00f}, // top left 
    };

public:

    void InitEnvironment();                         // Inicia o ambiente com COnfiguracoes personalziadas
    void Initialize();                              // inicializa RECURSOS
    void Input(GLFWwindow* window, f32 Delta);    // Entrada do jogador
    void ProcessPhysics(f32 Delta);               // processa fisica
    void Processing();                              // processamento
    void Render();                                  // render
    void Release();                                 // Deletes
};

#endif // LITTLESNAKE_H