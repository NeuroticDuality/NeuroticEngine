#include "render.hpp"
#include "verticedata.hpp"
#include "leveldata.hpp"

Render::Render(){
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

void Render::LoadTexture(Shader* shader, char* FileLocation, int ID){
TexSurf = IMG_Load(FileLocation);
glGenTextures(1, &TexID[ID]);
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

void Render::AssignTextures(Shader* shader){
//Enable Alpha transparency in textures.
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
//Enable Depth testing
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
//Load Texture resources here.
LoadTexture(shader, (char*)"Resources/Textures/FroggerLogo.png", 0);
LoadTexture(shader, (char*)"Resources/Textures/Heart.png", 1);
LoadTexture(shader, (char*)"Resources/Textures/HeartDespair.png", 2);
LoadTexture(shader, (char*)"Resources/Textures/HeartDespairTearing.png", 3);
LoadTexture(shader, (char*)"Resources/Textures/LiquidWater.png", 4);
LoadTexture(shader, (char*)"Resources/Textures/BackroundDay.png", 5);
LoadTexture(shader, (char*)"Resources/Textures/PesterDespair.png", 6);
LoadTexture(shader, (char*)"Resources/Textures/FrogBro.png", 7);
LoadTexture(shader, (char*)"Resources/Textures/Fate.png", 8);
LoadTexture(shader, (char*)"Resources/Textures/SoilSideFog.png", 9);
LoadTexture(shader, (char*)"Resources/Textures/SoilTopFog.png", 10);
LoadTexture(shader, (char*)"Resources/Textures/SoilFog.png", 11);
LoadTexture(shader, (char*)"Resources/Textures/Curt.png", 12);
//SetDefaultTexture to use.
glUseProgram(shader->ShaderProgram);

glBindTexture(GL_TEXTURE_2D, TexID[0]);

//glActiveTexture(GL_TEXTURE2);
//glBindTexture(GL_TEXTURE_2D, TexID[2]);
}

void Render::DrawQuad(Shader* shader, Physics* physics, int ID){
//Multiply MVP and send data to shader uniform.
glm::mat4 MVP = physics->Proj * physics->View * physics->Model;
//SetShader MVP
glUseProgram(shader->ShaderProgram);
GLint UniformMVP = glGetUniformLocation(shader->ShaderProgram, "MVP");
glUniformMatrix4fv(UniformMVP, 1 , GL_FALSE, glm::value_ptr(MVP));
//Set Texture.

if(ID != shader->CurrentTexture)
{
shader->CurrentTexture = ID;
glBindTexture(GL_TEXTURE_2D, TexID[ID]);
NumTexBind++;
//fprintf(stderr, "BindNewQuadTexture\n");
}
//Bind VAO and draw.
glBindVertexArray(QuadVAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
NumDraw++;
NumVerts += 6;
glBindVertexArray(0);
}

void Render::DrawCube(Shader* shader, Physics* physics, int BottID, int SideID, int TopID){
//Multiply MVP and send data to shader uniform.
glm::mat4 MVP = physics->Proj * physics->View * physics->Model;
//SetShader MVP
glUseProgram(shader->ShaderProgram);
GLint UniformMVP = glGetUniformLocation(shader->ShaderProgram, "MVP");
glUniformMatrix4fv(UniformMVP, 1 , GL_FALSE, glm::value_ptr(MVP));

//Set Texture.
if(SideID != shader->CurrentTexture)
{
shader->CurrentTexture = SideID;
glBindTexture(GL_TEXTURE_2D, TexID[SideID]);
NumTexBind++;
//fprintf(stderr, "BindingNewCubeSideTexture\n");
}
//Bind VAO and draw.
glBindVertexArray(CubeVAO);
glDrawArrays(GL_TRIANGLES, 0, 24);
NumDraw++;
NumVerts += 24;
//Set Texture.
if(BottID != shader->CurrentTexture)
{
shader->CurrentTexture = TopID;
glBindTexture(GL_TEXTURE_2D, TexID[BottID]);
NumTexBind++;
//fprintf(stderr, "BindingNewCubeTopTexture\n");
}
glBindTexture(GL_TEXTURE_2D, TexID[BottID]);
glDrawArrays(GL_TRIANGLES, 24, 6);
NumDraw++;
NumVerts += 6;
//Set Texture.
if(TopID != shader->CurrentTexture)
{
shader->CurrentTexture = TopID;
glBindTexture(GL_TEXTURE_2D, TexID[TopID]);
NumTexBind++;
//fprintf(stderr, "BindingNewCubeTopTexture\n");
}
glBindTexture(GL_TEXTURE_2D, TexID[TopID]);
glDrawArrays(GL_TRIANGLES, 30, 6);
NumDraw++;
NumVerts += 6;
//Unbind for safety
glBindVertexArray(0);
}

void Render::DrawObjects(Shader* shader, Physics* physics, ChunkManager* chunkmanager){
NumVerts = 0;
NumDraw = 0;
NumTexBind = 0;

//DrawBlocks(shader, physics);
DrawFrog(shader, physics);
DrawChunk(shader, physics, chunkmanager, 0, 0);
DrawChunk(shader, physics, chunkmanager, 0, 1);

//Print Statistics
fprintf(stderr, "DrawObjects;\n");
fprintf(stderr, "VertexCount     :%i\n", NumVerts);
fprintf(stderr, "DrawCalls       :%i\n", NumDraw);
fprintf(stderr, "BindTextureCalls:%i\n\n", NumTexBind);
}

void Render::DrawIntro(Shader* shader, Physics* physics){
glDisable(GL_DEPTH_TEST);
//Set Model and default position.
//Backround
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, 0.0f, -0.4f));
physics->Model = glm::scale(physics->Model, glm::vec3(20.0f, 6.0f, 1.0f));
DrawQuad(shader, physics, 5);
//Soil
glEnable(GL_DEPTH_TEST);
for(int x = 0; x < 9; x++){
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(-4.0f + x, -2.25f, 0.0f));
DrawCube(shader, physics, 11, 9, 10);
}
glDisable(GL_DEPTH_TEST);
//Logo
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, cos(physics->RotTimer*8) /8 + 0.5f, cos(physics->RotTimer*2)));
physics->Model = glm::rotate(physics->Model, cos(physics->RotTimer) /4, glm::vec3(0.0f, 0.0f, 1.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(2.0f, 2.0f, 1.0f));
DrawQuad(shader, physics, 0);
//Heart
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(-2.5f, 0.0f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(-exp(cos(physics->RotTimer*15))/20 +1.0f, -exp(cos(physics->RotTimer*15))/32 +1.0f, 1.0f));
DrawQuad(shader, physics, 1);
//Heart Despair
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, 1.5f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(-exp(cos(physics->RotTimer*10))/20 +1.0f, -exp(cos(physics->RotTimer*10))/32 +1.0f, 1.0f));
DrawQuad(shader, physics, 2);
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, -1.5f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(-exp(cos(physics->RotTimer*10))/20 +1.0f, -exp(cos(physics->RotTimer*10))/32 +1.0f, 1.0f));
DrawQuad(shader, physics, 2);
//HeartDespairTearing
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(2.5f, 0.0f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(-exp(cos(physics->RotTimer*5))/20 +1.0f, -exp(cos(physics->RotTimer*5))/32 +1.0f, 1.0f));
DrawQuad(shader, physics, 3);
//FrogBro
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(-2.0f, -1.25f, 0.0f));
DrawQuad(shader, physics, 7);
//Fate
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(2.0f, -1.25f, 0.0f));
DrawQuad(shader, physics, 8);
//Curt
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(3.0f, -1.4f, 0.0f));
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, cos(physics->RotTimer*8) /8 + 0.5f, 0.0f));
DrawQuad(shader, physics, 12);
//LiquidWater
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, -3.5f, 0.0f));
physics->Model = glm::rotate(physics->Model, cos(physics->RotTimer) /128, glm::vec3(0.0f, 0.0f, 1.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(10.0f, -exp(cos(physics->RotTimer*1))/4 +2.5f, 0.5f));
DrawQuad(shader, physics, 4);
glEnable(GL_DEPTH_TEST);
}

void Render::DrawChunk(Shader* shader, Physics* physics, ChunkManager* chunkmanager, int ChunkX, int ChunkZ){

unsigned char X = 0;
unsigned char Y = 0;
unsigned char Z = 0;

for(Y = 0;Y < 16;Y++){

for(Z = 0;Z < 16;Z++){
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(ChunkX * 16 + X, Y, ChunkZ * 16 + Z));
for(X = 0;X < 16;X++){
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(ChunkX * 16 + X, Y, ChunkZ * 16 + Z));
DrawCube(shader, physics, chunkmanager->Data[ChunkX][ChunkZ][X][Y][Z],chunkmanager->Data[ChunkX][ChunkZ][X][Y][Z],chunkmanager->Data[ChunkZ][ChunkZ][X][Y][Z]);
fprintf(stderr, "X: %i\n", X);
}
fprintf(stderr, "Z: %i\n", Z);

}
}
}


void Render::DrawFrog(Shader* shader, Physics* physics){
//Set Model.
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, physics->FrogPos);
physics->Model = glm::scale(physics->Model, glm::vec3(1.0f, 1.0f, 1.0f));
//Multiply MVP and send data to shader uniform.
DrawQuad(shader, physics, 12);
}

void Render::DrawBlocks(Shader* shader, Physics* physics){

for(int z = 0; z < 9; z++)
{
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(-4.0f, -2.5f, z));
DrawCube(shader, physics, 11, 9, 10);
for(int x = 0; x < 9; x++)
{
physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(-4.0f + x, -2.5f, z));
DrawCube(shader, physics, 11, 9, 10);
}
}

physics->Model = glm::mat4();
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, -2.35f, 0.0f));
physics->Model = glm::translate(physics->Model, glm::vec3(0.0f, -exp(cos(physics->RotTimer*1))/4 + 0.25f, 0.0f));
physics->Model = glm::rotate(physics->Model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
physics->Model = glm::scale(physics->Model, glm::vec3(100.0f, 100.0f, 1.0f));
DrawQuad(shader, physics, 4);
}


