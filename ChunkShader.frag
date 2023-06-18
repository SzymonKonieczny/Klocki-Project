#version 330 core
out vec4 FragColor;


in vec3 color;
in vec2 texCoord;
in vec4 gl_FragCoord ;
uniform sampler2D tex0;


float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; 
    return (2.0 * near * far) / (far + near - z * (far - near)) / far;	
}
float FogExp2(float depth, float density)
{
	
	return 1.0f;
}
float FogLinear(float depth,float density)
{
	if(depth > 0.8) return 0.8f;
	return (depth)/(1/density);
}
vec4 applyFog(vec4 pixel)
{

	return mix(pixel, vec4(164/255.0f, 196 / 255.0f, 252 / 255.0f, 1.0f), vec4(FogLinear(LinearizeDepth(gl_FragCoord.z), 0.9) ));
}
void main()
{
	vec4 pixel = texture(tex0 , texCoord);
	if(pixel.w < 0.1) discard;
	FragColor = vec4( vec4(color, 1.0f)*pixel );
	FragColor = applyFog(FragColor);

	//FragColor = vec4((color, 1.0f)*  pixel);




	

}