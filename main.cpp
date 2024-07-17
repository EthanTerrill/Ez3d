#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>




#include <cassert>
#include <vector>

#include <fstream>
#include <string>
#include <unistd.h>
#include <math.h>

#include <sstream>


#include "bitmap.hpp"
#include "texture2d.cpp"
#include "objFile.cpp"
#include "model.cpp"
#include "shader.cpp"
#include "shaderProgram.cpp"
#include "camera.cpp"




void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//////////////////////////////////////////////////////////////
//	Screen Info
//////////////////////////////////////////////////////////
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

//////////////////////////////////////////////////////////////
//	Shaders
//////////////////////////////////////////////////////////
camera myCam = camera(glm::vec3(0, 0.3, -2.0));

int main() {

  myCam.lockKey();

  /////////////er_size_callback(GLFWwindow *window, int width, int height);
  void processInput(GLFWwindow *window);
  /////////////////////////////////////////////////
  //	Initialize GLFW and set version to 3.3
  //////////////////////////////////////////////////////////
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//////////////////////////////////////////////////////////////
//	Add optomizations for apple devices
//////////////////////////////////////////////////////////
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  //////////////////////////////////////////////////////////////
  //	Create window using GLFW
  //////////////////////////////////////////////////////////
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "P.D.E. window", NULL, NULL);

  if (window == NULL) {
    std::cerr << "an error occoured while trying to setup the GLFW Window\n exiting with code -1\n";
    glfwTerminate();
    return -1;
  }

  //////////////////////////////////////////////////////////////
  //	Make sure that GLFW is pointing towards our
  //	Window
  //////////////////////////////////////////////////////////
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  //////////////////////////////////////////////////////////////
  //	Setup glad
  //////////////////////////////////////////////////////////
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  //////////////////////////////////////////////////////////////
  //	setup and compile shader
  //////////////////////////////////////////////////////////
  shaderProgram myShader = shaderProgram
  (
    "shaders/vertexDefault.glsl", 
    "shaders/fragmentDefault.glsl"
  );

  shaderProgram myShader2 = shaderProgram
  (
    "shaders/vertexDefault.glsl", 
    "shaders/fragmentDefault.glsl"
  );

  //////////////////////////////////////////////////////////////
  //	Vertices for polygon faces
  //////////////////////////////////////////////////////////
  float vertices[] = {


   -0.5f, 0.0f,-0.5f,   //1.0f, 0.1f, 0.1f,     0.0f, 0.0f,   // lb
    0.5f, 0.0f,-0.5f,   //0.1f, 1.0f, 0.1f,    1.0f, 0.0f,   // rb
   -0.5f, 0.0f, 0.5f,   //0.1f, 0.1f, 1.0f,    0.0f, 0.0f,   // lt
    0.5f, 0.0f, 0.5f,   //0.9f, 0.9f, 0.1f,    1.0f, 0.0f,  // rt
    0.0f, 0.95f, 0.0,   // 0.1f, 0.9f, 0.9f,    0.5f, 1.0f,  // t
   -0.5f, 0.0f, 0.5f,   //0.1f, 0.1f, 1.0f,    1.0f, 0.0f,   // lt2
    0.5f, 0.0f, 0.5f   //0.9f, 0.9f, 0.1f,    0.0f, 0.0f  // rt2
    


    };

  //////////////////////////////////////////////////////////////
  //	Polygon face (based on indeces of vertices)
  //////////////////////////////////////////////////////////
  GLuint indexBuffer[] = {

    0, 1, 4, 
    0, 5, 4, 
    1, 6, 4,
    2, 3, 4

  };

  //////////////////////////////////////////////////////////////
  //	setup polygons from vertices
  //////////////////////////////////////////////////////////
  //model m = model(vertices, indexBuffer, sizeof(vertices), 4);

  float r, g, b = 0;
  float t = 0;
  float dt = 0.1;
  srand(time(NULL));
  


  //model ship = model("mech/Mech-bot.obj");
  const int n = 5;
  model ship[n];

  std::string l[4] = {"Shambler.obj", "ship.obj", "tank.obj", "mech/Mech-bot.obj"};
  float m[4] = {0.03,              0.3,        3,          0.2};
  for(int i =0; i < n; i ++)
    ship[i] = model(l[i%4]);
  
  

  bitmap mybmp("Input/dococ.bmp");
  texture2d myTexture = texture2d(mybmp);


  GLuint tex0uni = glGetUniformLocation(myShader.getShader(), "tex0");

  GLuint glTime = glGetUniformLocation(myShader.getShader(), "t");
  GLuint glScale = glGetUniformLocation(myShader.getShader(), "scale");
  GLuint pos     = glGetUniformLocation(myShader.getShader(), "pos");


  glUniform1f(tex0uni, 2.0f);

  float rot = 0.0f;
  
  /////////////////////////////////////////////////////////////////
  //  main game loop
  //////////////////////////////////////////////////////////////

  glEnable(GL_DEPTH_TEST);

  //system("open funky.mp3");


  glfwSetCursorPos(window, 0, 0);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  while (!glfwWindowShouldClose(window)) {

    //myCam.move(glm::vec3(0.0f, 0.0f, -1.0), 0.1);
    myCam.processKeys(window);
    glUniform1f(glTime, t);
    glUniform1f(glScale, 3);
    

    /////////////////////////////////////////////////////////////////
    // increment time
    //////////////////////////////////////////////////////////////

    t+= dt;
    

    /////////////////////////////////////////////////////////////////
    //  handle user input
    //////////////////////////////////////////////////////////////

    processInput(window);
    

    /////////////////////////////////////////////////////////////////
    //  background clear
    //////////////////////////////////////////////////////////////

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /////////////////////////////////////////////////////////////////
    // 
    //////////////////////////////////////////////////////////////

    glUseProgram(myShader.getShader());


    /////////////////////////////////////////////////////////////////
    // Linear Algebra stuff
    //////////////////////////////////////////////////////////////

    


    myCam.linkCamera(SCR_WIDTH, SCR_HEIGHT, myShader);
  
    //myTexture.bind();

    for(int i = 0; i < n; i++){
      //glTranslatef(i, i, 0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(10 * t), glm::vec3(0.0f,1.0f,0.0f));

    if(i % 4 == 2)
    model = glm::rotate(model, glm::radians(-90.0f),  glm::vec3(1.0f,0.0f,0.0f));
    
    int modelLoc = glGetUniformLocation(myShader.getShader(), "model");
    

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glUniform1f(glScale, m[i%4]);

    glUniform3f(pos, (i % 2) * 3, 0.2,  3* (i/2));
    ship[i].bindArrays();
    glDrawElements(GL_TRIANGLES, ship[i].getPolyNum() * 3, GL_UNSIGNED_INT, 0);
    }
    //ship.draw();


    //myTexture.bind();
    //m.bindArrays();
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

    usleep(100);
    glfwPollEvents();
  }

  for(int i = 0; i < n; i++)
  ship[i].Delete();
  //m.Delete();
  myShader.Delete();
  myTexture.Delete();

  // glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
