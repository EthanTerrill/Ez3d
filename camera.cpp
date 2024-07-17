float playerSpeed;
float playerSensitvity = 0.05;
float Θmax = 360;
 

bool lock = false;
class camera {

    private:


    glm::vec3 position    = glm::vec3(0.0f, 0.52f, 0.0f);
    glm::vec3 dPosition   = glm::vec3(0.0f, 0.52f, 0.0f);
    glm::vec3 orientation = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 forwards    = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 side        = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up          = glm::vec3(0.0f, 0.0f, 1.0f);


    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 proj  = glm::mat4(1.0f);

    glm::mat3 pitch = glm::mat3(1.0f);
    glm::mat3 roll= glm::mat3(1.0f);


    float near  = 0.1f;
    float far   = 100.0f;

    float Θ = 0.0f;
    float φ = 0.0f;

    float dΘ = 0.0f;
    float dφ = 0.0f;

    float speed = 0.1;
    

    int width;
    int height;

    void updateDir(){


        orientation =   pitch * roll * glm::vec3(1.0f, 0.0f, 0.0f); 
        side        =   pitch        * glm::vec3(0.0f, 0.0f, 1.0f);
        forwards    =   pitch        * glm::vec3(1.0f, 0.0f, 0.0f);
        up          =   pitch * roll * glm::vec3(0.0f, 1.0f, 0.0f);



    }






    void updatePitch(){



        float sinΘ = sin(Θ);
        float cosΘ = cos(Θ);
        /*

        Pitch
        ╔══              ══╗
        ║  cosΘ,  0,  sinΘ ║
        ║     0,  1,  0    ║
        ║ -sinΘ,  0,  cosΘ ║
        ╚══              ══╝
        
        */
        
        pitch[1][1] = 1;

        pitch[0][0] =  cosΘ;
        pitch[2][2] =  cosΘ;
        pitch[2][0] = -sinΘ;
        pitch[0][2] =  sinΘ;

    }
    void updateRoll(){



        float sinφ = sin(φ);
        float cosφ = cos(φ);
        /*

        Pitch
        ╔══              ══╗
        ║  cosΘ,  0,  sinΘ ║
        ║     0,  1,  0    ║
        ║ -sinΘ,  0,  cosΘ ║
        ╚══              ══╝
        
        */
        
        roll[0][0] =  cosφ;
        roll[1][1] =  cosφ;
        roll[1][0] = -sinφ;
        roll[0][1] =  sinφ;


    }



    /////////////////////////////////////
    //  Please replace with PID
    //      controls thx
    //////////////////////////////////

    float t = 0.2;
    void updateΘ(){

        Θ += (dΘ - Θ) * t;
        updatePitch();
        
    }
    void updateφ(){

        φ += (dφ - φ) * t;
        updateRoll();
        
    }
    void updatePos(){

        position += (dPosition - position);

    }




    public:

    camera(){



    }

    

    camera(glm::vec3 start){
        
        dPosition = start;
        position  = start;
        





    }


    void linkCamera(int width, int height, shaderProgram camShader){

        view  = glm::mat4(1.0f);
        proj  = glm::mat4(1.0f);


        view = glm::lookAt(position, position + orientation, up);


        //view = glm::translate(view, position);
        proj = glm::perspective(glm::radians(45.0f), ((float)width/(float)height), near, far);

        int viewLoc  = glGetUniformLocation(camShader.getShader(), "view");
        int projLoc  = glGetUniformLocation(camShader.getShader(), "proj");

        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));

    }


    void move(glm::vec3 dir, float speed){

        dPosition += dir * speed;


    }

    void processKeys(GLFWwindow* win){


        if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        {

            move(forwards, speed);
        }
        if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        {

            move(forwards, -speed);
        }
        if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        {

            move(side, -speed);
        }
        if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        {

            move(side, speed);
        }
        if(glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS){

            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            lock = true;
        }
        if(glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS){

            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            lock = false;
            
        }

        if(lock){
            double xpos, ypos;
            glfwGetCursorPos(win, &xpos, &ypos);
            if(xpos !=0 || ypos != 0 ){
                
                float offset = 90.0f;
                if(xpos > offset){
                    xpos += (xpos - offset) * (xpos - offset) * 0.001;
                }
                else if(xpos < -offset){
                    xpos -= (xpos + offset) * (xpos + offset) * 0.001;
                }
                
                dΘ += (xpos * 2 * 3.14 / 180) * playerSensitvity;
                 

                dφ -= (ypos * 2 * 3.14 / 180) * playerSensitvity;
                if(dφ > 3.14/2) {
                    dφ = 3.14/2;

                }
                else if(dφ < -3.14/2) {
                    dφ = -3.14/2;

                }
            
                glfwSetCursorPos(win, 0, 0);
                glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                updatePitch();
                updateRoll();
                updateDir();
            }
            updateΘ();
            updateφ();
            updatePos();
            updateDir();

            
        }

        

    }

    void lockKey()
    {
        lock = true;
    }






};