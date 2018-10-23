//This shader takes four coordinates of a block and draws it to the screen
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0f);
}