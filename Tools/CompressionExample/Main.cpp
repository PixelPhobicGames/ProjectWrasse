#include "raylib.h"
#include "minizip/unzip.h"
#include <iostream>


using namespace std;

unzFile openZip(const char* zipFilePath, const char* fileName) {
    unzFile zipFile = unzOpen(zipFilePath);
    if (!zipFile) {
        std::cerr << "Failed to open zip file: " << zipFilePath << std::endl;
        return nullptr;
    }

    int err = unzLocateFile(zipFile, fileName, 1);
    if (err != UNZ_OK) {
        std::cerr << "File not found in zip: " << fileName << std::endl;
        unzClose(zipFile);
        return nullptr;
    }

    err = unzOpenCurrentFile(zipFile);
    if (err != UNZ_OK) {
        std::cerr << "Failed to open file in zip: " << fileName << std::endl;
        unzClose(zipFile);
        return nullptr;
    }

    return zipFile;
}

// Function to stream a compressed asset from a zip file
bool streamAssetFromZip(unzFile zipFile, char* buffer, int bufferSize) {
    int readBytes = unzReadCurrentFile(zipFile, buffer, bufferSize);

    if (readBytes < 0) {
        std::cerr << "Error reading from zip file." << std::endl;
        unzCloseCurrentFile(zipFile);
        unzClose(zipFile);
        return false;
    }

    // Additional processing or decompression can be done here if needed

    return readBytes > 0;
}

Image LoadImageFrom(const char* ZipPath, const char* FilePath) {
    const int bufferSize = 1024 * 10;
    unzFile zipFile = openZip(ZipPath, FilePath);

    if (!zipFile) {
        Image dummyImage = GenImageColor(1, 1, BLANK);
        return dummyImage;  // Return a dummy image on failure
    }

    char buffer[bufferSize];

    // Example: Stream the asset in chunks
    int bytesRead = streamAssetFromZip(zipFile, buffer, bufferSize);

    unzCloseCurrentFile(zipFile);
    unzClose(zipFile);

    if (bytesRead <= 0) {
        Image dummyImage = GenImageColor(1, 1, BLANK);
        return dummyImage;  // Return a dummy image on failure
    }

    Image img = LoadImageFromMemory(FilePath, reinterpret_cast<const unsigned char*>(buffer), bytesRead);

    return img;
}

Texture2D LoadTextureFrom(const char* ZipPath, const char* FilePath) {
    Image img = LoadImageFrom(ZipPath, FilePath);

    Texture2D tex = LoadTextureFromImage(img);

    UnloadImage(img); // Unload the image data, as it is no longer needed

    return tex;
}

int main(){
    InitWindow(500 , 500 , "Test");
    SetTargetFPS(60);
    
    Texture2D Test = LoadTextureFrom("Game.zip" , "Test.png");


    while (!WindowShouldClose())
    {
        /* code */

        BeginDrawing();

        DrawTexture(Test , 0 , 0 , RED);
        
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}