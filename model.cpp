



class model{

  private:

  GLuint vertexBufferPointer = 0;
  GLuint vertexArrayPointer  = 0;
  GLuint indexBufferPointer  = 0;
  
  GLenum drawType = GL_STATIC_DRAW;

  objFile obj;
    

    
  void bind(GLuint pointer, GLenum bufferType, size_t size, void* buffer){

    
    //////////////////////////////////////////////////////////////
    //  Bind the pointer to the GPU memory and specify its type	
    //////////////////////////////////////////////////////////

    glBindBuffer(bufferType, pointer);

    //////////////////////////////////////////////////////////////
    //  Bind the buffer to the pointer specifying type, size,
    //  and render mode
    //////////////////////////////////////////////////////////
    glBufferData(bufferType , size, buffer, drawType);

    


  } 
  void draw(){

  }

  void linkAttrib(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
  {
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
  }
  
  void unbind(){


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  }

  void generate(){
    
    //////////////////////////////////////////////////////////////
    //	generate the buffers and vertex arrays
    //////////////////////////////////////////////////////////

    glGenVertexArrays(1, &vertexArrayPointer);
    glGenBuffers(1, &vertexBufferPointer);
    glGenBuffers(1, &indexBufferPointer);

  }

  
 
  public:

  void bobmethod(float* vertices, GLuint* indeBuffer, int verticeNum, int indexNum){

      //////////////////////////////////////////////////////////////
      //	check that vertices and indexBuffer are good
      //////////////////////////////////////////////////////////

      assert(vertices != NULL);
      assert(indeBuffer != NULL);

      assert(verticeNum > 0);
      assert(indexNum > 0);


      //////////////////////////////////////////////////////////////
      //	assign variables
      //////////////////////////////////////////////////////////

      
      generate();


      // Make the VAO the current Vertex Array Object by binding it
      glBindVertexArray(vertexArrayPointer);


      //std::cout << "VertixNUm = " << verticeNum<<"\n";
      bind(vertexBufferPointer, GL_ARRAY_BUFFER,          sizeof(float)  * verticeNum, vertices);
      bind(indexBufferPointer,  GL_ELEMENT_ARRAY_BUFFER,  sizeof(GLuint) * 3 * indexNum,   indeBuffer);


      //linkAttrib(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
      //linkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
      //linkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
      linkAttrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    
      unbind();
  }

  void Scale(){
    //for(int i = 0; i < obj.getVerticeNum() * 3; i++){

      //vertexBuffer[i] = vertexBuffer[i] * scale;
      
    //}

  }

  model(float vertices[], GLuint indexBuffer[], int verticeNum, int indexNum)
  {

    bobmethod(vertices, indexBuffer, verticeNum, indexNum);
      
  }

  model(std::string filename)
  {
    obj = objFile(filename);

    bobmethod(obj.getVertices(), obj.getIndices(), obj.getVertexNum() * 3, obj.getPolyNum());


    obj.empty();
    
      
  }

  model(){}


  void bindArrays(){

    glBindVertexArray(vertexArrayPointer);

  }

  void bindArrays(GLuint n){

    glBindVertexArray(n);

  }

  


  void Delete(){


    glDeleteVertexArrays(1, &vertexArrayPointer);
    glDeleteBuffers(1, &vertexBufferPointer);
    glDeleteBuffers(1, &indexBufferPointer);


  }

  int getPolyNum(){

    return obj.getPolyNum();
  }




};
