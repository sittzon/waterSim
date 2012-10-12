#version 150

in vec2 exTexCoord;
//in vec3 exNormal;

out vec4 outColor;

uniform sampler2D upperTex;
uniform sampler2D middleTex;
uniform sampler2D lowerTex;

const float ka = 0.05;
const float kd = 0.9;
const float ks = 0.6;

void main(void)
{

    //Vector field operations on texture

    //outColor = textureOffset(texUnit, exTexCoord, ivec2(1,1));

    //float r =  texture2D(texUnit, exTexCoord).r;

    outColor = texture2D(middleTex, exTexCoord) -  vec4(0.1);
    outColor = vec4(1.0);
}
