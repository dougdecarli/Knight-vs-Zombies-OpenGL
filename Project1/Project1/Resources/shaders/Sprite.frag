#version 330 core

out vec4 FragColor;

in vec2 v_TexCoords;
uniform float u_OffsetX;
uniform float u_OffsetY;
uniform sampler2D u_Texture;

void main(){
	vec2 v_Texture = vec2(v_TexCoords.x + u_OffsetX, v_TexCoords.y + u_OffsetY);
	vec4 v_TextureMix = texture(u_Texture, v_Texture);

	if(v_TextureMix.a < 0.5)
		discard;

	FragColor = v_TextureMix;
}