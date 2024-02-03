#include "Core.hpp"

/* OT:2: PixelPhobicGames 2023 */

int main() {
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(1280, 720, "NOSTOMANIA DEMO - OT2");
    SetTargetFPS(60);

    InitAudioDevice();

    if (!IsAudioDeviceReady()) {
        CloseAudioDevice();
    }

    PlayLogo();

    OmegaTechInit();
    PlayHomeScreen();

    LoadWorld();

    HideCursor();
    DisableCursor();

    while (!WindowShouldClose()) {

        if (!UseLumina) {
            if (!ConsoleToggle) {

                if (UsingCineFlow) {
                    UpdateCamera(&CineFlowData.CFCamera, CAMERA_FREE);
                    UpdateCineFlow();
                } else {
                    OmegaPlayer.OldX = OmegaTechData.MainCamera.position.x;
                    OmegaPlayer.OldY = OmegaTechData.MainCamera.position.y;
                    OmegaPlayer.OldZ = OmegaTechData.MainCamera.position.z;

                    OmegaTechData.CameraSpeed = 1;

                    if (IsKeyDown(KEY_SPACE))OmegaTechData.CameraSpeed = 2;

                    if (!OmegaInputController.InteractDown) {
                        for (int i = 0; i <= OmegaTechData.CameraSpeed; i++) {
                            UpdateCamera(&OmegaTechData.MainCamera, CAMERA_FIRST_PERSON);
                        }
                    }

                    OmegaInputController.UpdateInputs();
                }
            }

            UpdateLightSources();
        }

        UpdateFade();
        if (!CustomData.PlayEnding) {
            if (!UseLumina) {
                DrawWorld();
            } else {
                LuminaDrawWorld();
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (!CustomData.PlayEnding) {

            if (!UseLumina) {
                BeginShaderMode(OmegaTechData.Bloom);
                DrawTexturePro(Target.texture,
                               (Rectangle){0, 0, Target.texture.width, -Target.texture.height},
                               (Rectangle){0, 0, float(GetScreenWidth()), float(GetScreenHeight())},
                               (Vector2){0, 0},
                               0.f,
                               FadeColor);

            }

            else {
                DrawTexturePro(LuminaTarget.texture,
                               (Rectangle){0, 0, LuminaTarget.texture.width, -LuminaTarget.texture.height},
                               (Rectangle){0, 0, float(GetScreenWidth()), float(GetScreenHeight())},
                               (Vector2){0, 0},
                               0.f,
                               FadeColor);
            }

            if (ScriptCollisionMessage) {
                DisplayInteractText();
            }

            if (OmegaTechData.Ticker == 33 || OmegaInputController.InteractPressed || OmegaInputController.TextButton) {
                ScriptCollisionMessage = false;
            }

            EndShaderMode();

            if (!UsingCineFlow && !UseLumina) {
                if (UIToggle)UpdateUI();
                UpdateCustomUI(OmegaTechData.LevelIndex);
            }

            if (IsKeyPressed(KEY_TAB)){
                if (UIToggle){
                    UIToggle = false;
                }
                else {
                    UIToggle = true;
                }
            }

            if (FPSEnabled) {
                DrawFPS(0, 0);
            }

            if (!UsingCineFlow)
                OmegaTechTextSystem.Update();

            if (ConsoleToggle) {
                DrawConsole();
            }
        }

        else { // Endings
            switch (OmegaTechData.LevelIndex) {
            case 1:
                // Ending 1
                ray_video_update(&CustomData.Ending1, GetFrameTime());
                DrawTexturePro(CustomData.Ending1.texture,
                               (Rectangle){0, 0, CustomData.Ending1.width, CustomData.Ending1.height},
                               (Rectangle){0, 0, float(GetScreenWidth()), float(GetScreenHeight())},
                               (Vector2){0, 0},
                               0.f,
                               FadeColor);
                if (CustomData.Ending1.video_state == RAY_VIDEO_STATE_DONE) {
                    ray_video_destroy(&CustomData.Ending1);
                    exit(0);
                }
                break;
            }
        }

        EndDrawing();

        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        if (IsWindowResized()){
            SetWindowSize(1280 , 720);
        }

        if (IsKeyPressed(KEY_F3)) {
            if (ConsoleToggle) {
                ConsoleToggle = false;
                HideCursor();
                DisableCursor();
            } else {
                ConsoleToggle = true;
                ShowCursor();
                EnableCursor();
            }
        }

        if (ExitLuminaFlag) {
            UseLumina = false;
            OmegaTechData.LevelIndex++;
            LoadWorld();
            ExitLuminaFlag = false;
        }

        SceneIDMirror = OmegaTechData.LevelIndex;
    }
    CloseWindow();
}