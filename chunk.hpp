#ifndef CHUNK_H_
#define CHUNK_H_

#define CX 16
#define CY 16
#define CZ 16

#include "stdio.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ChunkManager{
public:
unsigned char Data[4][4][CX][CY][CZ];
ChunkManager();
void LoadChunk();
void FillChunk(int x, int z, unsigned char ID);
void ClearChunk();
void GenChunk();
void AddID();
void DelID();
};

enum BlockID{
Air,
Bedrock,
Stone,
Sand,
SandStone,
Gravel,
Soil,
Grass,
PlantGrass,
PlantGrassTall,
PlantFernTall,
PlantBush,
PlantCactus,
MushroomBrown,
MushroomWhite,
MushroomRed,
OakWood,
OakLeaves,
OakWoodPlank,
OakSapling,
OakChest,
OakTorch,
Water,
Snow,
SnowLayer,
Ice,
Lava,
Coal,
CoalOre,
Iron,
IronShovel,
IronAxe,
IronPickaxe,
IronSword,
IronOre,
Gold,
GoldOre,
Diamond,
DiamondOre,
WoolBlack,
WoolWhite,
WoolGrey,
WoolRed,
WoolGreen,
WoolBlue,
WoolPurple,
WoolOrange,
WoolPink,
WoolBrown,
WoolBed,
Glass,
GlassHeart,
GlassPane,
TNT,
Rabbit,
RabbitMeat,
Pig,
PigMeat,
Frog,
FrogGrappleTongue,
CurtFace,
CurtBody,
CurtPocketWatch,
DespairFleshSoil,
DespairHead,
DespairBody,
DespairEyes,
DespairRageHead,
DespairRageBody,
DespairHeart,
DespairHeartTearing,
};

#endif
