#version 330 core
out vec4 FragColor;
in vec3 oPos;    
void main()
{
   FragColor = vec4(oPos.x, oPos.y, oPos.z, 1.0f);
}