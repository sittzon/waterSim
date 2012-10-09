#version 150

in vec2 exTexCoord;
in vec3 exNormal;
in vec3 viewDir;
in vec4 vertexPosition;

out vec4 outColor;

uniform sampler2D texUnit;

const float ka = 0.05;
const float kd = 0.9;
const float ks = 0.6;

void main(void)
{

    //Vector field operations on texture




    outColor = texture2D(texUnit, exTexCoord);
}
