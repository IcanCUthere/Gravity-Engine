#shader vertex
#version 450
#extension GL_ARB_separate_shader_objects : enable 
#extension GL_ARB_shading_language_420pack : enable 

layout (std140, binding = 0) uniform matrices {
    mat4 Matrix;
} Matrices;

layout (location = 0) in vec3 positions;

void main() {
    gl_Position = Matrices.Matrix * vec4(positions, 1.0);
}

#shader fragment
#version 450 
#extension GL_ARB_separate_shader_objects : enable 
#extension GL_ARB_shading_language_420pack : enable 

layout (location = 0) out vec4 color; 

void main() { 
    color = vec4(1.0, 1.0, 1.0, 1.0); 
}  