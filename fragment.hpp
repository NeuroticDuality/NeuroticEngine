const char* FragmentSource [] = {
"#version 330 core\n"
"out vec4 FragColor;"

"in vec3 Color;"
"in vec2 TexCoord;"

"uniform sampler2D Tex0;"

"void main(void)"
"{"
    "FragColor = texture(Tex0, TexCoord);"
"}"
};
