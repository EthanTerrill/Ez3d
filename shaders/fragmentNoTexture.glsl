#version 330 core
//extension GL_ARB_separate_shader_objects : require


varying vec3 aPos;


//////////////////////////////////////////////////////////////
//  out vec4 specifies that a vec4 (FragColor) will break 
//    the output of this code
//////////////////////////////////////////////////////////
    
out vec4 FragColor;
in  vec3 color;

uniform float t;


void main()
{
	FragColor = vec4( color.x, 0, gl_FragCoord.z + color.z, t);
	
	//FragColor = vec4(gl_FragCoord.x/500.0, 0, gl_FragCoord.y/500.0, 0.0f);
}