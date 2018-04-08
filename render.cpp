#include "render.hpp"
#include "verticedata.hpp"

Render::Render()
{
//init Vertex resources here.
//Quad
glGenVertexArrays(1, &QuadVAO);
glGenBuffers(1, &QuadVBO);
glGenBuffers(1, &QuadEBO);
//Bind Vao and then VBO with vertice and attrib info for vao.
glBindVertexArray(QuadVAO);
//Bind VBO and EBO Vertice and Indices Data.
glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QuadIndices), QuadIndices, GL_STATIC_DRAW);
//Vertex Attribs

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// texture coord attribute
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindVertexArray(0);
//Cube
glGenVertexArrays(1, &CubeVAO);
glGenBuffers(1, &CubeVBO);
glBindVertexArray(CubeVAO);
glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
//Vertice Data Attrib
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// texture coord attribute
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindVertexArray(0);

//Unbind objects for safety
glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Render::LoadTexture(Shader* shader, char* FileLocation, int ID)
{
TexSurf = IMG_Load(FileLocation);
glGenTextures(1, &TexID[ID]);
glActiveTexture(GL_TEXTURE0 + ID);
glBindTexture(GL_TEXTURE_2D, TexID[ID]);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load image, create texture and generate mipmaps
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexSurf->w, TexSurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TexSurf->pixels);
}

void Render::AssignTextures(Shader* shader)
{
//Enable Alpha transparency in textures.
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
//Enable Depth testing
glEnable(GL_DEPTH_TEST);
//Load Texture resources here.
//LoadTexture(shader, "Resources/Textures/FrogBro.png", 0);
TexSurf = IMG_Load("Resources/Textures/FrogBro.png");
glGenTextures(1, &TexID[0]);
glActiveTexture(GL_TEXTURE0 + 0);
glBindTexture(GL_TEXTURE_2D, TexID[0]);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load image, create texture and generate mipmaps
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexSurf->w, TexSurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TexSurf->pixels);

TexSurf = IMG_Load("Resources/Textures/SoilSide.png");
glGenTextures(1, &TexID[1]);
glActiveTexture(GL_TEXTURE0 + 1);
glBindTexture(GL_TEXTURE_2D, TexID[1]);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load image, create texture and generate mipmaps
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexSurf->w, TexSurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TexSurf->pixels);
//SetDefaultTexture to use.
glUseProgram(shader->ShaderProgram);
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "TexID"),0);
//Tells gl where the shader uniform is, its name and which texture unit is asigned to the sampler2d.
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "Tex0"),0);
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "Tex1"),1);
//glUniform1i(glGetUniformLocation(shader->ShaderProgram, "Tex2"),2);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, TexID[0]);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, TexID[1]);

//glActiveTexture(GL_TEXTURE2);
//glBindTexture(GL_TEXTURE_2D, TexID[2]);
}

void Render::DrawObjects(Shader* shader, Physics* physics)
{
DrawFrog(shader, physics);
DrawBlocks(shader, physics);
}

void Render::DrawIntro(Shader* shader, Physics* physics)
{

}

void Render::DrawFrog(Shader* shader, Physics* physics)
{
//Set Model.
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, physics->FrogPos);
physics->Model = glm::scale(physics->Model, glm::vec3(1.0f, 1.0f, 1.0f));
//Multiply MVP and send data to shader uniform.
glm::mat4 MVP = physics->Proj * physics->View * physics->Model;
//SetShaderTexture
glUseProgram(shader->ShaderProgram);
GLint UniformMVP = glGetUniformLocation(shader->ShaderProgram, "MVP");
glUniformMatrix4fv(UniformMVP, 1 , GL_FALSE, glm::value_ptr(MVP));
//Set Texture.
glUseProgram(shader->ShaderProgram);
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "TexID"),0);
//Bind VAO and draw.
glBindVertexArray(QuadVAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
}

void Render::DrawBlocks(Shader* shader, Physics* physics)
{
//Set Model.
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.125f, -1.0f, 0.0f));
//physics->Model = glm::rotate(physics->Model, glm::radians(physics->RotTimer) * 45, glm::vec3(0.0f, 1.0f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(1.0f, 1.0f, 1.0f));
//Multiply MVP and send data to shader uniform.
glm::mat4 MVP = physics->Proj * physics->View * physics->Model;
//SetShaderTexture
glUseProgram(shader->ShaderProgram);
GLint UniformMVP = glGetUniformLocation(shader->ShaderProgram, "MVP");
glUniformMatrix4fv(UniformMVP, 1 , GL_FALSE, glm::value_ptr(MVP));

//Set Texture.
glUseProgram(shader->ShaderProgram);
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "TexID"),1);
//Bind VAO and draw.
glBindVertexArray(CubeVAO);
glDrawArrays(GL_TRIANGLES, 0, 24);

//Set Texture.
glUseProgram(shader->ShaderProgram);
glUniform1i(glGetUniformLocation(shader->ShaderProgram, "TexID"),0);
glActiveTexture(GL_TEXTURE0 + 1);
glDrawArrays(GL_TRIANGLES, 24, 12);
//Unbind for safety
glBindVertexArray(0);
}


