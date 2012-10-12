#version 150

in vec2 exTexCoord;
in vec3 exNormal;
in vec3 viewDir;
in vec4 vertexPosition;

out vec4 outColor;

uniform sampler2D texUnit;
uniform mat4 lightSourcesColors;
uniform mat4 lightSourcesDirections;
uniform vec4 lightSourcesOn;
//uniform int shading;

const float ka = 0.05;
const float kd = 0.9;
const float ks = 0.6;

void main(void)
{

	//Ambient
	//------------------------------------
	vec3 Iamb = vec3(1.0, 1.0, 1.0);

	//Diffuse and specular init
	//----------------------------------------------------
	vec3 Idiff = vec3(0.0, 0.0, 0.0);
	vec3 Ispec = vec3(0.0, 0.0, 0.0);
	float shade = 0.0;

    for (int i = 0; i < 4; i++)
    {
        vec4 color = vec4(lightSourcesColors[i]);
        vec4 dirPos = vec4(lightSourcesDirections[i]);
        float n = color[3]; 		//Specular term

        vec3 colorVec3 = vec3(color[0], color[1], color[2]);
        vec3 dirPosVec3;

        if (lightSourcesOn[i] == 0.0)
            dirPosVec3 = vec3(0.0, 0.0, 0.0);
        else if (dirPos[3] <= 0.5)                                       //Directional light
            dirPosVec3 = normalize(vec3(dirPos[0], dirPos[1], dirPos[2]));
        else                                                        //Positional light
            dirPosVec3 = normalize(vec3(dirPos[0] - vertexPosition[0], dirPos[1] - vertexPosition[1], dirPos[2] - vertexPosition[2]));

        //Diffuse
        shade = max(dot(dirPosVec3, normalize(-exNormal)), 0);
        Idiff += shade * colorVec3;
        Idiff = clamp(Idiff, 0, 1);

        //Specular
        vec3 r = 2.0 * normalize(exNormal) * dot(dirPosVec3, normalize(exNormal)) - dirPosVec3;
        float cosFi = dot(normalize(r), normalize(viewDir));
        Ispec += colorVec3 * pow(max(cosFi, 0), n);
        Ispec = clamp(Ispec, 0, 1);
    }

	//Total output light    //Clicking s toggles between modes
	//--------------------------------------------------------
    //outColor = clamp(ka*Iamb + kd*Idiff + ks*Ispec, 0, 1);// + exNormal;// vec3(1.0, exTexCoord);// * texture(texUnit, exTexCoord,  1.0)
    outColor = vec4(clamp(ka*Iamb + kd*Idiff + ks*Ispec, 0, 1), 1.0) * texture2D(texUnit, exTexCoord);

    //vec4 color = texture2D(texUnit, exTexCoord);
    //if (color == vec4(1.0,0.0,0.0,1.0))
    //    discard;

    //outColor = vec4(1.0);

}
