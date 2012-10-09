#version 150

in vec2 inTexCoord;
in vec3 inPosition;
in vec3 inNormal;

out vec2 exTexCoord;
out vec3 exNormal;

uniform mat4 projection;
uniform mat4 worldToView;
uniform mat4 modelToWorld;

void main(void)
{
    gl_Position = vec4(inPosition, 1.0);

    //Normal vectors
	mat3 normalMatrix = mat3(modelToWorld);
	exNormal = normalMatrix * inNormal;
	//exNormal = inNormal;

    //Texture coordinates
	exTexCoord = inTexCoord;
}
