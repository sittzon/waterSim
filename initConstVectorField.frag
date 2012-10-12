#version 150

uniform float xSpeed;
uniform float ySpeed;
uniform float zSpeed;
uniform float pressure;

out vec4 outColor;

void main(void)
{

    //Vector field
    outColor = vec4(xSpeed, ySpeed, zSpeed, pressure);
}
