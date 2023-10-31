#include "raylib.h"
#include "Settings.hpp"
#include "Player.hpp"
#include "Editor.hpp"
#include "Video.hpp"
#include "ParticleDemon/ParticleDemon.hpp"
#include "Parasite/ParasiteScript.hpp"
#include "Encoder/Encoder.hpp"
#include "Entities.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>

using namespace std;

#define MaxCachedModels 200
#define MaxMapSize 2000

static float AmbientLightValues[4] = {0.1f, 0.1f, 0.1f, 0.1f};

static float TerrainHeightMap[MaxMapSize][MaxMapSize];

void GenHeights(Image heightmap, Vector3 size)
{
    #define GRAY_VALUE(c) ((float)(c.r + c.g + c.b) / 3.0f)

    int mapX = size.x;
    int mapZ = size.z;
    
    for (int z = 0; z < mapX - 1; z++){
        for (int x = 0; x < mapZ - 1; x++){
            TerrainHeightMap[z][x] = 0.0f;
        }
    }

    Color *pixels = LoadImageColors(heightmap);

    float Scale = heightmap.width / size.x;
    
    for (int z = 0; z < (mapZ)- 1; z++)
    {
        for (int x = 0; x < (mapX) - 1; x++)
        {
            float Index = ((x * Scale) + (z * Scale) * heightmap.width);
            TerrainHeightMap[z][x] = GRAY_VALUE(pixels[int(Index)]) / (255 / size.y);
        }
    }
}

static wstring WorldData;
static wstring OtherWDLData;


static int R = 0;
static int G = 0;
static int B = 0;

int Direction = 1;

bool FadeDone = false;
Color FadeColor = (Color){R, G, B, 255};

void PlayFade()
{
    Direction = 1;
    R = 0;
    G = 0;
    B = 0;
    FadeDone = false;
}   



class GameModels
{
    public:
        Texture2D Skybox;
        
        Vector3 HeightMapPosition;

        int HeightMapW = 0;
        int HeightMapH = 0;

        Model HeightMap;
        Texture2D HeightMapTexture;

        Model Model1;
        Texture2D Model1Texture;

        Model Model2;
        Texture2D Model2Texture;

        Model Model3;
        Texture2D Model3Texture;

        Model Model4;
        Texture2D Model4Texture;

        Model Model5;
        Texture2D Model5Texture;

        Model Model6;
        Texture2D Model6Texture;

        Model Model7;
        Texture2D Model7Texture;

        Model Model8;
        Texture2D Model8Texture;

        Model Model9;
        Texture2D Model9Texture;

        Model Model10;
        Texture2D Model10Texture;

        Model Model11;
        Texture2D Model11Texture;

        Model Model12;
        Texture2D Model12Texture;

        Model Model13;
        Texture2D Model13Texture;

        Model Model14;
        Texture2D Model14Texture;

        Model Model15;
        Texture2D Model15Texture;

        Model Model16;
        Texture2D Model16Texture;

        Model Model17;
        Texture2D Model17Texture;

        Model Model18;
        Texture2D Model18Texture;

        Model Model19;
        Texture2D Model19Texture;

        Model Model20;
        Texture2D Model20Texture;

        // GLTS Models

        // For Faster Rendering.

        Model FastModel1;
        Texture2D FastModel1Texture;
        Model FastModel2;
        Texture2D FastModel2Texture;
        Model FastModel3;
        Texture2D FastModel3Texture;
        Model FastModel4;
        Texture2D FastModel4Texture;
        Model FastModel5;
        Texture2D FastModel5Texture;
};

static GameModels WDLModels;

class GameData{
    public:
        float X;
        float Y;
        float Z;
        float R;
        float S;
        int ModelId;
        bool Collision;

        void Init(){
            X = 0;
            Y = 0;
            Z = 0;
            R = 0;
            S = 0;
            ModelId = 0;
            Collision = false;
        }

};

static int CachedModelCounter = 0;
static GameData CachedModels[MaxCachedModels];

class CollisionData{
    public:
        float X;
        float Y;
        float Z;
        float W;
        float H;
        float L;

        void Init(){
            X = 0;
            Y = 0;
            Z = 0;
            W = 0;
            H = 0;
            L = 0;
        }

};

static int CachedCollisionCounter = 0;
static CollisionData CachedCollision[MaxCachedModels];

class GameSounds
{
    public:
        Sound CollisionSound;
        Sound WalkingSound;
        Sound UIClick;
        Sound ChasingSound;
        Sound Death;
        Music NESound1;
        Music NESound2;
        Music NESound3;

        Music BackgroundMusic;


        bool MusicFound = false;
};

static GameSounds OmegaTechSoundData;


void DrawTerrainMap(){
    for (int z = 0; z < MaxMapSize; z++){
        for (int x = 0; x < MaxMapSize; x++){
            DrawCube({x , TerrainHeightMap[z][x] , z }, 0.5 , 0.5 , 0.5, RED);
        }
    }
}


bool TextBox001EditMode = false;
char TextBox001Text[128] = "";
bool TextBox002EditMode = false;
char TextBox002Text[1024] = "OmegaConsole\n";

void PrintConsole(const char* Message){
    strcat(TextBox002Text, Message);
}

void ConsoleParseCommand(const char* Command){
    bool Found = false;

    string CommandValue(Command);

    if (CommandValue == "ExportTerrain"){
        PrintConsole("Exporting Terrain As Mesh\n");
        if (ExportMesh(WDLModels.HeightMap.meshes[0], "Terrain.obj")){
            PrintConsole("Done.. Stored in Terrain.obj\n");
        }

        Found = true;
    }

    if (!Found){
        PrintConsole("Command Not Found: ");
        PrintConsole(Command);
        PrintConsole("<--\n");
    }
}

void DrawConsole(){
    GuiPanel((Rectangle){ 0, 40, 616, 288 }, NULL);

    if (GuiTextBox((Rectangle){ 8, 296, 600, 24 }, TextBox001Text, 128, TextBox001EditMode)) TextBox001EditMode = !TextBox001EditMode;

    if (GuiTextBox((Rectangle){ 8, 48, 600, 240 }, TextBox002Text, 1024, TextBox002EditMode)){

    }

    if (IsKeyPressed(KEY_ENTER)){
        ConsoleParseCommand(TextBox001Text);
        TextBox001Text[0] = '\0';
    }
}