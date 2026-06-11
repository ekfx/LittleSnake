#include "LittleSnake.h"

void LittleSnake::InitEnvironment() 
{
    s.Start(MyObjects.ObjectArray, 20, -(WidthSpace/2), (WidthSpace/2), (HeightSpace/2), -(HeightSpace/2), 1.0f);

    SetVSync(false);


    MyHUD.Start(GetWindowHandle());
    MyHUD.SetCustomRenderFunction([&]() {
        ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize);
            ImGui::InputFloat("Zoom", &CameraZoom, 0.1f, 0.1f, "%.3f", 0);
            ImGui::InputFloat("Width", &WidthSpace, 1.0f, 1.0f, "%.3f", 0);
            ImGui::InputFloat("Height", &HeightSpace, 1.0f, 1.0f, "%.3f", 0);
        ImGui::End();
    });
}

void LittleSnake::Initialize() 
{
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
    if (MyTimer.Update(MyClock, 60.0f)) {   // atualiza a cada 60ms
        s.Walk(MyObjects.ObjectArray);
    }

    // left top right bottom
    s.SetSpace(-(WidthSpace/2), (HeightSpace/2), (WidthSpace/2), -(HeightSpace/2));

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

    for (int i = 0; i < MyObjects.ObjectArray.size(); i++) {
        MyModel = glm::mat4(1.0f);
        MyModel = glm::scale(MyModel, glm::vec3(0.06125f));
        MyModel = glm::translate(MyModel, MyObjects.ObjectArray.at(i).position);

        if (i == 0) {
            GlobalShader.SetInt("Actor", 0);
        } else {
            GlobalShader.SetInt("Actor", 1);
        }

        GlobalShader.SetMat4("model", MyModel);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    }

    MyHUD.Run(GetWindowWidth(), GetWindowHeight(), 0);
}

void LittleSnake::Release() 
{
    MyMesh.ReleaseBuffers();
    MyTexture.ReleaseTexture();
    GlobalShader.ReleaseShaderProgram();
    MyHUD.Release();
}