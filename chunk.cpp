#include "chunk.hpp"

ChunkManager::ChunkManager(){
FillChunk(0,0,1);
FillChunk(0,1,2);

FillChunk(1,1,3);
FillChunk(1,2,4);

FillChunk(2,1,5);
FillChunk(2,2,6);
}

void ChunkManager::LoadChunk(){

}

void ChunkManager::FillChunk(int x, int z, unsigned char ID){

unsigned char X = 0;
unsigned char Y = 0;
unsigned char Z = 0;

for(Y = 0;Y < 16;Y++){
for(Z = 0;Z < 16;Z++){
for(X = 0;X < 16;X++){
Data[x][z][X][Y][Z] = ID;
}
}
}

}

void ChunkManager::ClearChunk(){

}

void ChunkManager::GenChunk(){

}

void ChunkManager::AddID(){

}

void ChunkManager::DelID(){

}
