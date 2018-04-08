static const char* VertexSource[] =
{
"#version 330 core\n"
"layout (location = 0) in vec3 Apos;"
"layout (location = 1) in vec2 ATexCoord;"

"uniform mat4 MVP;"

"out vec3 Color;"
"out vec2 TexCoord;"

"void main(void)"
"{"
"gl_Position = MVP * vec4(Apos, 1.0);"
"TexCoord = vec2(ATexCoord);"
"}"
};
