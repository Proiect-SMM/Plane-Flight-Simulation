#define SHADOW_WIDTH  3072
#define SHADOW_HEIGHT 3072


#include <Windows.h>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Skybox.h"
#include "Terrain.h"
#include "PointLight.h"
#include "Model.h"
#include "Airplane.h"
int nScreenWidth = 1920;
int nScreenHeight = 1080;
#define SCR_HEIGHT nScreenHeight 
#define SCR_WIDTH nScreenWidth
//Model* Airplane = nullptr;
Airplane* airplane = nullptr;

Model* Tower = nullptr;
Model* Airport = nullptr;


Shader* ShadowMappingDepthShader = nullptr;
Shader* ShadowMappingShader = nullptr;

Terrain* terrain = nullptr;

unsigned int depthMapFBO = 0;
unsigned int depthMap = 0;

double deltaTime = 0.0;
double lastFrame = 0.0;

void InitDepthFBO()
{
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE); 
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void InitShaders()
{
    ShadowMappingDepthShader = new Shader("ShadowMappingDepth.vs", "ShadowMappingDepth.fs");
    ShadowMappingShader = new Shader("ShadowMapping.vs", "ShadowMapping.fs");

    ShadowMappingShader->SetValue("diffuseTexture", 0);
    ShadowMappingShader->SetValue("shadowMap", 1);
}

void InitTerrain()
{
    terrain = new Terrain("terrain/map.jpg");
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* handler = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (handler)
        handler->MouseControl((float)xpos, (float)ypos);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
     Camera* handler = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
  
}

void ProcessInput(GLFWwindow* window, Camera* camera, Airplane* airplane)
{
    airplane->ProcessInput(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera->SetMode(1);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        camera->SetMode(0);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera::ECameraMovementType::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera::ECameraMovementType::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera::ECameraMovementType::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera::ECameraMovementType::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        airplane->ModifyThrottle(deltaTime, 1);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        airplane->ModifyThrottle(deltaTime, -1);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            airplane->ModifyRoll(deltaTime, 1);
        }
        else
            airplane->ModifyYaw(deltaTime, 1);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            airplane->ModifyRoll(deltaTime, -1);
        }
        else
            airplane->ModifyYaw(deltaTime, -1);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        airplane->ModifyPitch(deltaTime, 1);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        airplane->ModifyPitch(deltaTime, -1);

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        airplane->Break(deltaTime);

}

/// Initializeaza fereastra si face un contex OpenGL in aceasta fereastra
void InitWindow(GLFWwindow* (&window), const std::string& title)
{
    if (!glfwInit())
    {
        std::cerr << "GLFW failed to initialize!" << std::endl;
        exit(-1);
    }

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), NULL, NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW failed to initialize!" << std::endl;
        exit(-1);
    }

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, keyboard_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void RenderScene(const Shader* shader)
{
    glEnable(GL_DEPTH_TEST);
    glm::mat4 model;
   
    model = glm::mat4(0.7f);
    shader->Bind();
    shader->SetMat4("model", model);
    terrain->Render();
    
  /*  model = glm::scale(glm::mat4(1), glm::vec3(0.01f));
    model = glm::rotate(model, -90.f, {1.0f, 1.0f, 1.0f });
    model = glm::translate(model,{0.0f, 0.0f, 150.0f });
    shader->SetMat4("model", model);*/
   
    airplane->Draw(shader);

     model = glm::mat4(0.7f);
    model = glm::scale(model, { 0.2f,0.2f,0.2f });
    model = glm::rotate(model, -90.f, { 1.0f, 1.0f, 1.0f });
    model = glm::translate(model, { 850.0f, 200.0f, 70.0f });
    shader->SetMat4("model", model);
    Tower->Draw(shader);

    model = glm::mat4(0.7f);
    model = glm::scale(model, { 0.7f,0.7f,0.7f });
    model = glm::rotate(model, -90.f, { 1.0f, 1.0f, 1.0f });
    model = glm::translate(model, { 50.0f, 100.0f, 1.0f });
    shader->SetMat4("model", model);
    Airport->Draw(shader);

    glDisable(GL_DEPTH_TEST);
}

/// functia care deseneaza
void RenderFunction(GLFWwindow* window)
{
    Skybox skybox;
    Pointlight light({ 50.0f, 200.0f, 0.0f });

    Camera* camera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(-4, 6, -3));
    camera->BindAirplane(airplane);
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(camera));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        // render scene from light's point of view
        ShadowMappingDepthShader->Bind();
        ShadowMappingDepthShader->SetMat4("lightSpaceMatrix", light.LightSpaceMatrix());
        ShadowMappingDepthShader->SetMat4("lightViewMatrix", light.ViewMatrix());

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

        glClear(GL_DEPTH_BUFFER_BIT);

        //glActiveTexture(GL_TEXTURE0);

        //glBindTexture(GL_TEXTURE_2D, floorTexture);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);


        RenderScene(ShadowMappingDepthShader);

        glCullFace(GL_BACK);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. render scene as normal using the generated depth/shadow map 
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShadowMappingShader->Bind();

        glm::mat4 projection = camera->GetProjectionMatrix();
        glm::mat4 view = camera->GetViewMatrix();
        ShadowMappingShader->SetMat4("projection", projection);
        ShadowMappingShader->SetMat4("view", view);
        // set light uniforms

        ShadowMappingShader->SetVec3("viewPos", camera->GetPosition()) ;
        ShadowMappingShader->SetVec3("lightPos", light.GetPosition());
        ShadowMappingShader->SetMat4("lightSpaceMatrix", light.LightSpaceMatrix());
        ShadowMappingDepthShader->SetMat4("lightViewMatrix", light.ViewMatrix());


        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, floorTexture);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        ShadowMappingShader->SetValue("shadowMap", 5);
        glDisable(GL_CULL_FACE);

        glDepthMask(GL_FALSE);
        skybox.Draw(camera);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        RenderScene(ShadowMappingShader);


        glEnable(GL_DEPTH_TEST);



        glfwSwapBuffers(window);
        glfwPollEvents();
        airplane->Update(deltaTime);
        ProcessInput(window, camera, airplane);
    }
}

int main()
{
    GLFWwindow* window;
    InitWindow(window, "FlightSim");
    InitShaders();
    InitDepthFBO();
    InitTerrain();
    Tower = new Model("tower/scene.gltf");

    airplane = new Airplane({ 0,0,0 });
    airplane->SetScale({ 0.01f,0.01f,0.01f});

    Airport = new Model("airport/scene.gltf");


    RenderFunction(window);
}