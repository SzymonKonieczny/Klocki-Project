#version 330 core

layout (location = 0) in uint Data1;
//layout (location = 1) in uint Data2; // has to be used. Otherwise the compiler discards it

out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//uint* tst = (uint*)&ddt1;
	//uint Data1 = *tst;

	float x = float(Data1 & 0x1Fu);
	float y = float((Data1 & 0x7FE0u)>>5);
	float z = float((Data1 & 0xF8000u)>>15);
	uint corner = uint((Data1 & 0x300000u)>>20);
	uint col = uint((Data1 & 0xC00000u)>>22);
	int TextureNr = int((Data1 & 0xFF000000u)>>24);

	//vec3 aPos = vec3(x,y,z);
	float texx = float((TextureNr % 5) * 0.2);
	float texy = float((float(TextureNr)/5) * 0.2);
	switch(corner)
	{
	case 0u:
	break;
	case 1u:
	texx+=0.2;
	break;
	case 2u:
	texy+=0.2;

	break;
	case 3u:
	texy+=0.2;
	texx+=0.2;

	break;
	}
	

	 switch(col)
	{
	case 0u:
	color = vec3(1.0, 1.0, 1.0); // UP
	break;
	case 1u:
	color = vec3(0.8, 0.8, 0.8); // SIDE
	break;
	case 2u:
	color = vec3(0.5, 0.5, 0.5); // BOTTOM
	break;
	case 3u:
	color = vec3(0.0, 0.0, 0.0); // ERROR
	break;
	}



	gl_Position = projection * view * model * vec4(x,y,z,1.0) ;
    texCoord = vec2(texx,texy);

	//color = aColor;

	//texCoord = aTex;


}