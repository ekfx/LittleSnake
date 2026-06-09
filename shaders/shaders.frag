#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform int Actor;
uniform sampler2D texture0; // player
uniform sampler2D texture1; // stars
uniform sampler2D texture2; // background
// não é um ID qualquer, é um sampler2D

void main() {
    if (Actor == 0) {   // player
        //FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        FragColor = texture(texture0, vec2(TexCoord.x, TexCoord.y));
        
    } else if (Actor == 1) {        // estrelas
        //FragColor = vec4(1.0, 1.0, 0.0, 1.0);
        FragColor = texture(texture1, vec2(TexCoord.x, TexCoord.y));

    } else if (Actor == 2) {
        FragColor = texture(texture2, vec2(TexCoord.x, TexCoord.y));
    }

}