#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float fade;

void main(){
    vec3 color1 = texture(texture1, TexCoord).rgb;
    vec4 color2 = texture(texture2, TexCoord);

    vec3 color = mix(color1, color2.rgb, color2.a * fade);

    FragColor = vec4(color, 1.0);
}