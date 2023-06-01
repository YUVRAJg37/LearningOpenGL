#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture_1;
uniform sampler2D ourTexture_2;
uniform float alpha;

void main()
{
   FragColor = mix(texture(ourTexture_1, texCoord), texture(ourTexture_2, texCoord), alpha);
}  