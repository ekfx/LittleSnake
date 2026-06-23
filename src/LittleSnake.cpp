#include "LittleSnake.h"

void LittleSnake::InitEnvironment() 
{
    snake.Start(MySnake, 40, GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);
    if (AI) enemy.Start(MyEnemy, 10, GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);
    SetVSync(false);

    MyHUD.Start(GetWindowHandle());
    MyHUD.SetCustomRenderFunction([&]() {
        ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize);
            ImGui::InputFloat("Zoom", &CameraZoom, 0.1f, 0.1f, "%.3f", 0);
            ImGui::InputFloat("SnakeTick", &SnakeTick, 1.0f, 1.0f, "%.3f", 0);
            ImGui::InputFloat("SnakeDistanceParts", &SnakeDistanceParts, 0.1f, 0.1f, "%.3f", 0);
        ImGui::End();
    });
}

void LittleSnake::Initialize() 
{
    Fruits.CreateOneObject(glm::vec3(0.2f, 0.2f, 0.2f), 10.0f,
                           glm::vec3(1.0f), glm::vec4(1.0f));

    GlobalShader.CreateBasicShaders();
    MyMesh.CreateMesh(MyVertex, sizeof(MyVertex), MyEBO, sizeof(MyEBO), 1, 1, 0, 1);
    MyTexture.BasicTexture(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR, "../assets/snake_part.png", 1, 0);
    GlobalShader.Use();
    GlobalShader.SetInt("texture0", 0);
}

void LittleSnake::Input(GLFWwindow* window, f32 Delta) 
{
    if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
        snake.SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::FORWARD);
    } else if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
        snake.SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::FORWARD);
    } else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
        snake.SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::BACKWARD);
    } else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
        snake.SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::BACKWARD);
    }
}

void LittleSnake::ProcessPhysics(f32 Delta) 
{
    
    // Artificial Intelligence
    if (AI) enemy.Chase(MyEnemy, Fruits);
    
    if (MyTimer.UpdateTick(MyClock, SnakeTick)) {   // atualiza a cada 70ms
        snake.Walk(MySnake);
        if (AI) enemy.Walk(MyEnemy);
    }
    
    // left top right bottom
    snake.SetSpace(GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);
    if (AI) enemy.SetSpace(GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);

    if (snake.CheckCollision(MySnake, Fruits)) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<i32> FruitX(snake.GetLeft(), snake.GetRight());
        std::uniform_int_distribution<i32> FruitY(snake.GetBottom(), snake.GetTop());
        Fruits.ObjectArray.at(0).position.x = FruitX(mt);
        Fruits.ObjectArray.at(0).position.y = FruitY(mt);
    }

    if (AI) {
        if (enemy.CheckCollision(MyEnemy, Fruits)) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<i32> FruitX(enemy.GetLeft(), enemy.GetRight());
            std::uniform_int_distribution<i32> FruitY(enemy.GetBottom(), enemy.GetTop());
            Fruits.ObjectArray.at(0).position.x = FruitX(mt);
            Fruits.ObjectArray.at(0).position.y = FruitY(mt);

            enemy.Add(MyEnemy);
        }
    }
}

void LittleSnake::Processing() 
{
    // Camera
    MyCamera.Start();
    MyCamera.SetProjection(ENGINE::CAMERA::ORTHOGRAPHIC, GetWindowWidth(), GetWindowHeight());
    MyCamera.Translate(0.0f, 0.0f, -1.0f);
    MyCamera.Zoom(CameraZoom);

    // essential
    GlobalShader.SetMat4("view", MyCamera.GetCameraMat4());
    GlobalShader.SetMat4("projection", MyCamera.GetProjectionMat4());
}

void LittleSnake::Render() 
{
    GlobalShader.Use();
    GlobalShader.SetInt("Actor", 1);
    glBindTexture(GL_TEXTURE0, MyTexture.GetTextureID());
    glBindVertexArray(MyMesh.GetVAO());

    for (int i = 0; i < MySnake.ObjectArray.size(); i++) {
        MyModel = glm::mat4(1.0f);
        MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
        MyModel = glm::translate(MyModel, MySnake.ObjectArray.at(i).position);

        if (i % 2 == 0) {
            GlobalShader.SetInt("Actor", 0);
        } else {
            GlobalShader.SetInt("Actor", 1);
        }

        if (i == 0) {
            GlobalShader.SetInt("Actor", 5);
        }

        GlobalShader.SetMat4("model", MyModel);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0); // aprwnder drwa instanced
    }

    if (AI) {
        for (int i = 0; i < MyEnemy.ObjectArray.size(); i++) {
            MyModel = glm::mat4(1.0f);
            MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
            MyModel = glm::translate(MyModel, MyEnemy.ObjectArray.at(i).position);

            if (i % 2 == 0) {
                GlobalShader.SetInt("Actor", 2);
            } else {
                GlobalShader.SetInt("Actor", 3);
            }

            if (i == 0) {
                GlobalShader.SetInt("Actor", 5);
            }

            GlobalShader.SetMat4("model", MyModel);
            // needs draw instanced
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0); // aprwnder drwa instanced
        }
    }

    MyModel = glm::mat4(1.0f);
    MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
    MyModel = glm::translate(MyModel, Fruits.ObjectArray.at(0).position);
    GlobalShader.SetInt("Actor", 4);
    GlobalShader.SetMat4("model", MyModel);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    MyHUD.Run(GetWindowWidth(), GetWindowHeight(), 0);
}

void LittleSnake::Release() 
{
    MyMesh.ReleaseBuffers();
    MyTexture.ReleaseTexture();
    GlobalShader.ReleaseShaderProgram();
    MyHUD.Release();
}