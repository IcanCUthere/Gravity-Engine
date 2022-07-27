#shader vertex
#version 450
#extension GL_ARB_separate_shader_objects : enable 
#extension GL_ARB_shading_language_420pack : enable 

layout (std140, binding = 0) uniform matrices {
    mat4 Matrix;
} Matrices;

layout (location = 0) in vec3 inPositions;
layout (location = 1) in vec2 inTexCoords;
layout (location = 0) out vec2 outTexCoords;

void main() {
    gl_Position = Matrices.Matrix * vec4(inPositions, 1.0);
    outTexCoords = inTexCoords;
}

#shader fragment
#version 450 
#extension GL_ARB_separate_shader_objects : enable 
#extension GL_ARB_shading_language_420pack : enable 

layout (binding = 1) uniform sampler2D texSampler;

layout (location = 0) in vec2 inTexCoords;
layout (location = 0) out vec4 outColor; 

void main() { 
    outColor = texture(texSampler, inTexCoords);
}  