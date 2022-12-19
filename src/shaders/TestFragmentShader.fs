#version 330 core

out vec4 fragColor;

in vec2 TextureCord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // fragColor = texture(texture1, TextureCord);
    fragColor = mix(texture(texture1, TextureCord), texture(texture2, TextureCord), 0.5);
}