#version 330 core
out vec4 FragColor;


in vec3 color;
in vec2 texCoord;
uniform sampler2D tex0;



void main()
{
	vec4 pixel = texture(tex0 , texCoord);
//	if(pixel.w < 0.1) discard;
	FragColor = vec4( vec4(color, 0.5f)*pixel );
//	FragColor = vec4( 0.5f,0.5f,0.5f,0.5f );
	





	

}