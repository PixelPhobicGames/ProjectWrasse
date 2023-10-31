#include "Core.hpp"


int main(){
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(1280 , 720 , "OT2");
    SetTargetFPS(60);

    InitAudioDevice();

    if (!IsAudioDeviceReady()){
        CloseAudioDevice();
    }

    OmegaTechInit();
    PlayHomeScreen();
    
    LoadWorld();

    HideCursor(); 
    DisableCursor();  
    
    while (!WindowShouldClose())
    {
        if (!ConsoleToggle){
            OmegaPlayer.OldX = OmegaTechData.MainCamera.position.x;
            OmegaPlayer.OldY = OmegaTechData.MainCamera.position.y;
            OmegaPlayer.OldZ = OmegaTechData.MainCamera.position.z;

            if (!OmegaInputController.InteractDown && !ShowSettings){
                for (int i = 0 ; i <= OmegaTechData.CameraSpeed; i ++){
                    UpdateCamera(&OmegaTechData.MainCamera, CAMERA_FIRST_PERSON);
                }
            }

            OmegaInputController.UpdateInputs();
        }

        UpdateLightSources();

        if (Direction == 1)
        {
            R += 1;
            G += 1;
            B += 1;

            if (R == 254)
            {
                FadeDone = true;
                Direction = 3;
            }
        }

        FadeColor = (Color){R, G, B, 255};
    

        DrawWorld();
        
        BeginDrawing();  
        
        ClearBackground(BLACK);

        BeginShaderMode(OmegaTechData.FinalShader);
        DrawTexturePro(Target.texture, (Rectangle){ 0, 0, Target.texture.width, -Target.texture.height }, (Rectangle){ 0, 0, float(GetScreenWidth()), float(GetScreenHeight())}, (Vector2){ 0, 0 } , 0.f , WHITE);
        UpdateObjectBar();
        EndShaderMode();

        if (ParticlesEnabled){
            OmegaTechData.RainParticles.Update(0,0);
            OmegaTechData.RainParticles.TriggerEffect({0,0} , RainEffect);
        }

        if (FPSEnabled){
            DrawFPS(0,0);
        }

        UpdateSettings();
        OmegaTechTextSystem.Update();

        if (ConsoleToggle){
            DrawConsole();
        }

        EndDrawing();

        if (IsKeyPressed(KEY_F11))ToggleFullscreen();

        if (IsKeyPressed(KEY_F3)){
            if (ConsoleToggle){
                ConsoleToggle = false;
                HideCursor(); 
                DisableCursor();  
            }
            else {
                ConsoleToggle = true;
                ShowCursor();
                EnableCursor();
            }
        }

    }
    
    CloseWindow();
}