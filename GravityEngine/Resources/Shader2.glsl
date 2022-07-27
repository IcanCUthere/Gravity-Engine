#shader vertex
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec4 pos;
layout(location = 0) out vec3 fragColor;

vec3 colors[4] = vec3[](
    vec3(1.0, 1.0, 1.0),
    vec3(1.0, 1.0, 1.0),
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 0.0, 0.0)
);

void main() 
{
    gl_Position = pos;
    fragColor = colors[gl_VertexIndex];
}

#shader fragment
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() 
{
    outColor = vec4(fragColor, 1.0);
}