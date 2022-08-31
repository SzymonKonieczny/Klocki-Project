#version 330 core
out vec4 FragColor;


in vec3 color;
in vec2 texCoord;
uniform sampler2D tex0;



void main()
{
	vec4 pixel = texture(tex0 , texCoord);
	if(pixel.w < 0.1) discard;
	FragColor = vec4(pixel * vec4(color, 1.0f));
	

	//FragColor = vec4((color, 1.0f)*  pixel);




	

}