const char* FragmentSource [] =
{
"#version 330 core\n"
"out vec4 FragColor;"

"in vec3 Color;"
"in vec2 TexCoord;"

"uniform int TexID;"

"uniform sampler2D Tex0;"
"uniform sampler2D Tex1;"
"uniform sampler2D Tex2;"

"void main(void)"
"{"
"switch(TexID)"
    "{"
    "case 0:"
    "FragColor = texture(Tex0, TexCoord);"
    "break;"
    "case 1:"
    "FragColor = texture(Tex1, TexCoord);"
    "break;"
    "case 1:"
    "FragColor = texture(Tex2, TexCoord);"
    "break;"
    "}"
"}"
};
