#version 330 core

layout(location = 0) in vec2 vao_Position;
layout(location = 1) in vec2 vao_TexCoords;

out vec2 v_TexCoords;

uniform float u_Depth;

void main(){
	gl_Position = vec4(vao_Position, u_Depth, 1.0);
	v_TexCoords = vao_TexCoords;
}
