#version 330
#ifdef GL_ES
precision mediump float;
#endif

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colorDiffuse;
uniform float u_time;

out vec4 final_color;

vec2 u_resolution = vec2(640.0, 480.0);

void main()
{
    vec4 texture_color = texture(texture0, fragTexCoord) * fragColor;

    float r = 0.85;
    float g = 0.75;
    float b = 0.75;
    float a = 1.0;
    vec4 base = vec4(r, g, b, a);

    final_color = base * texture_color;
    // final_color = texture_color;
}