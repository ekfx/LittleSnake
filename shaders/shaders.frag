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
        FragColor = vec4(0.4431, 0.0, 0.6196, 1.0);
    } else if (Actor == 1) {
        //FragColor = texture(texture0, vec2(TexCoord.x, TexCoord.y));
        FragColor = vec4(0.6039, 0.0549, 0.9216, 1.0);
    } else if (Actor == 2) {
        FragColor = vec4(0.0078, 0.2863, 0.0, 1.0);
    } else if (Actor == 3) {
        FragColor = vec4(0.0157, 0.4549, 0.0, 1.0);
    } else if (Actor == 4) {
        FragColor = vec4(0.7412, 0.0, 0.0, 1.0);
    } else if (Actor == 5) {
        FragColor = vec4(0.0, 0.8, 1.0, 1.0);
    }

    // needs to add better color change
    // not viable uniforms in every frame
}