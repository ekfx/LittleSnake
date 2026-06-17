#include "LittleSnake.h"

void LittleSnake::InitEnvironment() 
{
    s.Start(MyObjects.ObjectArray, 40, GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);
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
        s.SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::FORWARD);
    }

    if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
        s.SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::FORWARD);
    }

    if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
        s.SetDirectionAxis(ENGINE::AXIS::Y_AXIS, ENGINE::DIRECTION::BACKWARD);
    }

    if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
        s.SetDirectionAxis(ENGINE::AXIS::X_AXIS, ENGINE::DIRECTION::BACKWARD);
    }
}

void LittleSnake::ProcessPhysics(f32 Delta) 
{
    if (MyTimer.UpdateTick(MyClock, SnakeTick)) {   // atualiza a cada 70ms
        s.Walk(MyObjects.ObjectArray);
    }

    // left top right bottom
    s.SetSpace(GetWindowWidth(), GetWindowHeight(), SnakeDistanceParts);

    if (MyObjects.ObjectArray.at(0).position.x <= Fruits.ObjectArray.at(0).position.x + 1.1f &&
        MyObjects.ObjectArray.at(0).position.x >= Fruits.ObjectArray.at(0).position.x - 1.1f &&
        MyObjects.ObjectArray.at(0).position.y <= Fruits.ObjectArray.at(0).position.y + 1.1f &&
        MyObjects.ObjectArray.at(0).position.y >= Fruits.ObjectArray.at(0).position.y - 1.1f) {

        float AspectRatio = GetWindowWidth()/GetWindowHeight();
        float HeightSpace_ = 35.0f;

        float WidthSpace_ = HeightSpace_ * AspectRatio;

        // corrigir: nao eh viavel criar instancia a cada quadro
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<i32> FruitX(-(WidthSpace_/2), +(WidthSpace_/2));
        std::uniform_int_distribution<i32> FruitY(-(HeightSpace_/2), +(HeightSpace_/2));

        Fruits.ObjectArray.at(0).position.x = FruitX(mt);
        Fruits.ObjectArray.at(0).position.y = FruitY(mt);

        s.Add(MyObjects.ObjectArray);
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

    std::cerr << "X: " << Fruits.ObjectArray.at(0).position.x << " | Y: " << Fruits.ObjectArray.at(0).position.y << "\n";
    //std::cerr << "X: " << MyObjects.ObjectArray.at(0).position.x << " | Y: " << MyObjects.ObjectArray.at(0).position.y << "\n";

    for (int i = 0; i < MyObjects.ObjectArray.size(); i++) {
        MyModel = glm::mat4(1.0f);
        MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
        MyModel = glm::translate(MyModel, MyObjects.ObjectArray.at(i).position);

        if (i % 2 == 0) {
            GlobalShader.SetInt("Actor", 0);
        } else {
            GlobalShader.SetInt("Actor", 1);
        }

        GlobalShader.SetMat4("model", MyModel);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0); // aprwnder drwa instanced
    }

    MyModel = glm::mat4(1.0f);
    MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
    MyModel = glm::translate(MyModel, Fruits.ObjectArray.at(0).position);
    GlobalShader.SetInt("Actor", 3);
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