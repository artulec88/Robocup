#version 330 core

in vec3 fragmentColor; // Interpolated values from the vertex shaders
out vec3 color;

void main() {
	//color = vec3(1, 0, 0); // the whole figure will be red
	color = fragmentColor;
}