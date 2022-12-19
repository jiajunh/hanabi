#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aTexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 TextureCord;

void main(){
    gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
    TextureCord = vec2(aTexCoord.x, aTexCoord.y);
}