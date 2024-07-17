#version 330 core



//////////////////////////////////////////////////////////////
//	layout (location) specifies where our vec3 is 
//    location 0 means that it is in the 0th index
//////////////////////////////////////////////////////////

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aCol;
//layout (location = 2) in vec2 tex;


flat out vec3 color;
out vec2 texCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 pos;

uniform float scale;





float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void main()
{

  //////////////////////////////////////////////////////////////
  //  gl_position specifies the position of the vertex
  //////////////////////////////////////////////////////////

  gl_Position = proj * view * (model * vec4((aPos) * scale, 1.0) + vec4((pos), 1.0));

  //////////////////////////////////////////////////////////////
  // assign the output to the color we had defined before 
  //  in order to pass over to frag shader
  //////////////////////////////////////////////////////////
  float ambient = 0.15;
  float rate = 0.3;
  float light = rate * aPos.x + ambient;
  
  /*
  color = 
  vec3( 
    random(vec2(aPos.x, 255)), 
    random(vec2(aPos.y, 255)), 
    random(vec2(aPos.z, 255))
                
  );
  */

  color = vec3
  (
    aPos.x * rate + ambient, 
    aPos.y * rate + ambient,
    aPos.z * rate + ambient
  );


  

  texCoordinates = vec2(0,0);


}
