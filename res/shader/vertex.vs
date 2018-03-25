attribute vec2 position;
attribute vec2 texCoord;

varying vec2 vTexCoord;

uniform mat4 projection;
uniform mat4 mvp;
uniform mat4 view;

void main() 
{
    vTexCoord = texCoord;

	gl_Position = projection * (view * (mvp * vec4(position, 0.0, 1.0)));
}
