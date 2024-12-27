#version 410 core

layout(location = 0) in vec3 aPos;  // Vertex position
out vec2 fragCoord;  // Output to fragment shader

void main()
{
    fragCoord = (aPos.xy + 1.0) * 0.5 * vec2(640.0, 480.0);  // Scale and shift to pixel coordinates
    gl_Position = vec4(aPos, 1.0);
}
