#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture0;  
uniform sampler2D texture1;  

uniform int Actor;

void main() {
    if (Actor == 0) {
        //FragColor = texture(texture0, vec2(TexCoord.x, TexCoord.y));
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    } else if (Actor == 1) {
        //FragColor = texture(texture0, vec2(TexCoord.x, TexCoord.y));
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}