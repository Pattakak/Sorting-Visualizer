//This shader takes four coordinates of a block and draws it to the screen

layout (location = 0) aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0f);
}