#version 120

varying vec2 texCoord;

void main(void)
{
	gl_Position = ftransform();
	texCoord = gl_Position.xy; // / 2.0 + vec2(0.5);
}
