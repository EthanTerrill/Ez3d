class objFile{

private:


  int polygonCount;
  int vertexCount;
  int normalCount;
  int textureCount;
  int commentCount;


  float* vertexBuffer;
  GLuint* indexBuffer;
  int* indexBuffer2;




  float scale = 0.015;


  void parseVertLine(std::ifstream& file, uint& vertIndex){


    char whiteSpace;

    for(int i = 0; i < 3; i++) {

        if(vertIndex < vertexCount * 3)
        {
          file >> vertexBuffer[vertIndex];
        }
        else
        {
          std::cerr<<"wompwomp out of range" << vertIndex << "\n";
        }
        vertIndex++;

    }





  }

  int numberOfSlashes(std::string s){

    for(int i = 0; i < s.size() - 1; i++){

      if(s[i] = '/') {
        if(s[i] = '/') {
          return 2;

        }
        else{
          return 1;
        }
      }
      
    }
    return -1;

  }

  void parsePolyIndex(std::string str, uint& index){

    std::stringstream s(str); 
    char whiteSpace;
    int n = numberOfSlashes(str);
    int a;
    if(n == 2) 
    {
      
      int a;
      s >> a;
      
      indexBuffer[index] = a; 
      indexBuffer2[index] = a; 
      index++;
      s >> whiteSpace;
      s >> whiteSpace;
      s >> a;

    }
    else if(n == -1)
    {
      int a;
      s >> a;
      
      indexBuffer[index] = a; 
      indexBuffer2[index] = a; 
      index++;

    }
    



  }

  void parsePolyIndex2(std::string str, uint& index){}

  void parsePolyLine(std::ifstream& file, uint& polyIndex)
  {

    
    int tempft[3] = { 0 };
    int tempfn[3] = { 0 };

    char whiteSpace;

    for(int i = 0; i < 3; i++) {
      std::string str;

      file >> str;

      parsePolyIndex(str, polyIndex);

    }

    float a = indexBuffer[polyIndex - 3];

    char c;
    if(!file.eof()){
      file.get(c);
      
      if(c != '\n' && !file.eof()){
      c = file.peek();
      
      while(c != '\n' && !file.eof()){
        
        float b = indexBuffer[polyIndex - 1];
        
        indexBuffer[polyIndex] = a; indexBuffer2[polyIndex] = a; polyIndex++;
        indexBuffer[polyIndex] = b; indexBuffer2[polyIndex] = a; polyIndex++;
        std::string str;
        file >> str;
        parsePolyIndex(str, polyIndex);
        file.get(c);
      
      }
      
      }
    }
  }


  void parseObjFile(std::ifstream& file){


    if(vertexCount <= 0 || polygonCount <= 0){ 
      throw("Error Invalid objFile");
    }

    vertexBuffer = new float[vertexCount * 3] { 0 };
    indexBuffer  = new GLuint[polygonCount * 3 ]{ 0 };
    indexBuffer2 = new  int[polygonCount * 3 ]{ 0 };




    std::string firstLine;


    uint vertIndex = 0;
    uint polyIndex = 0;

    while(!file.eof())    
    {

        std::string firstLine;
        file >> firstLine;

        /**/ if(firstLine == "#")       { goToEndOfLine(file);/*do nothing*/ }
        else if(firstLine == "v")       { parseVertLine(file, vertIndex); goToEndOfLine(file);}
        else if(firstLine == "vt")      { goToEndOfLine(file);}
        else if(firstLine == "vn")      { goToEndOfLine(file);}
        else if(firstLine == "usemtl")  { goToEndOfLine(file);}
        else if(firstLine == "o")       { goToEndOfLine(file);}
        else if(firstLine == "g")       { goToEndOfLine(file);}
        else if(firstLine == "f")       { parsePolyLine(file, polyIndex);}

        
    }
    file.close();


    //printVertices();
    //printIndices();




    };

  void goToEndOfLine(std::ifstream& file)
    {
      char c;

      while(c != '\n' && !file.eof()){


        file.get(c);
        //std::cout << c;

      }

  }

  void preParsePolyLine(std::ifstream& file, int& polygonCount){

    std::string str;
    for(int i = 0; i < 3; i++) {
      file >> str;
    }
    polygonCount++;
    

    char c;
    if(!file.eof()){
      file.get(c);
      while(c != '\n' && !file.eof()){
        polygonCount++;
        file >> str;
        file.get(c);

        

      }
    }




  }
  
  void getVerticeNum(std::ifstream& file) {

    
    

    commentCount  = 0;
    vertexCount   = 0;
    textureCount  = 0;
    normalCount   = 0;
    polygonCount  = 0;

    while(!file.eof())    
    {
      std::string firstLine;
      
      file >> firstLine;
      
      /**/ if(firstLine == "#")       { commentCount++; goToEndOfLine(file);}
      else if(firstLine == "v")       { vertexCount++;  goToEndOfLine(file);}
      else if(firstLine == "vt")      { textureCount++; goToEndOfLine(file);}
      else if(firstLine == "vn")      { normalCount++;  goToEndOfLine(file);}
      else if(firstLine == "usemtl")  { /*do nothing*/  goToEndOfLine(file);}
      else if(firstLine == "o")       { /*do nothing*/  goToEndOfLine(file);}
      else if(firstLine == "g")       { /*do nothing*/  goToEndOfLine(file);}
      else if(firstLine == "f")       { preParsePolyLine(file, polygonCount); }

    }
    file.close();

  }


public:

  void printFileData(){

  std::cout <<  "\n vertex num:\t"<< vertexCount <<"\n"
              <<   " polygon num:\t"<< polygonCount <<"\n"
              <<   " normal  num:\t"<< normalCount <<" \n";

  }

  void printVertices(){

  int i = 0;
  while (i < vertexCount * 3){
      std::cout<< "v";
      for(int j = 0; j < 3; j++){

      std::cout<< " " << vertexBuffer[i] <<" ";
      i++;
      }
      std::cout<< "\n";
  }
  }

  void printIndices(){

  int i = 0;
  while (i < polygonCount * 3){

      std::cout<< "f";

      for(int j = 0; j < 3; j++){

      std::cout<< " " << indexBuffer2[i] <<" ";
      i++;
      }
      std::cout<< "\n";
  }
  }

  objFile(std::string filename){
    
    std::ifstream file(filename, std::ios::binary);

    if(!file.is_open()){
      assert(false);
    }

    getVerticeNum(file);

    file = std::ifstream(filename);
    if(!file.is_open()){
      assert(false);
    }



    printFileData();
    parseObjFile(file);


    for(int i = 0; i < 3 * polygonCount; i++){
      indexBuffer[i] = indexBuffer[i] - 1;
    }

    

    //////////////////////////////////////////////////////////////
    //	check that vertices and indexBuffer are good
    //////////////////////////////////////////////////////////

    //Scale();

    //bobmethod(vertexBuffer, indexBuffer, vertexCount * 3, polygonCount);

    
  }


  objFile(){};


  int getPolyNum(){

    return polygonCount;
  }

  void empty(){
    delete vertexBuffer;
    delete indexBuffer;
  }

  
  float* getVertices(){

    return vertexBuffer;
  }
  GLuint* getIndices(){
    
    return indexBuffer;
  }

  int getVertexNum(){
    return vertexCount;
  }




};


