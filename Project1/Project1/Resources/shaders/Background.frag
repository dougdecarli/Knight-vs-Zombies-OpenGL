#version 330 core

out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

uniform float u_OffsetX;

void main(){
	vec2 v_TextureScroll = vec2(v_TexCoords.x + u_OffsetX, v_TexCoords.y);
	FragColor = texture(u_Texture, v_TextureScroll);
}