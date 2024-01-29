#include "Data.hpp"
#include "External/GBEngine/GBEngine.hpp"

class Custom {
  public:
    Texture2D HeartBeatIcon;
    int HeartRate;
    Font CustomFont;
    bool HRWarning;

    ray_video_t Ending1;
    Sound Ending1Music;

    bool PlayEnding = false;
};

static Custom CustomData;


void LoadCustom(int ID) {
    switch (ID) {
    case 1:
        CustomData.HeartBeatIcon = LoadTexture("GameData/Global/Custom/Heart.png");
        CustomData.CustomFont = LoadFont("GameData/Global/Custom/Custom.ttf");
        CustomData.HeartRate = 60;
        CustomData.HRWarning = false;
        CustomData.Ending1 = ray_video_open("GameData/Global/Movies/Ending1.mpg");
        CustomData.Ending1Music = LoadSound("GameData/Global/Movies/Ending1.mp3");

        break;

    case 3:
        InitGB("GameData/Global/Rom/Game.gb");
        RunGB();

        ray_video_t FMVVideo;
        FMVVideo = ray_video_open("GameData/Global/Movies/Credits.mpg");
        Sound VideoSound = LoadSound("GameData/Global/Movies/Credits.mp3");

        PlaySound(VideoSound);

        while (true && !WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);

            ray_video_update(&FMVVideo, GetFrameTime());

            DrawTexturePro(FMVVideo.texture,
                           (Rectangle){0, 0, FMVVideo.width, FMVVideo.height},
                           (Rectangle){0, 0, float(GetScreenWidth()), float(GetScreenHeight())},
                           (Vector2){0, 0},
                           0.f,
                           WHITE);

            EndDrawing();

            if (FMVVideo.video_state == RAY_VIDEO_STATE_DONE || (IsKeyPressed(KEY_SPACE))) {
                UnloadSound(VideoSound);
                UnloadRenderTexture(Target);
                Target = LoadRenderTexture(GetScreenWidth() / 4, GetScreenHeight() / 4);
                ray_video_destroy(&FMVVideo);
                break;
            }
        }

        exit(0);
        break;
    }
}

#define MaxGrass 1000

int RenderedGrass = 80;
Vector3 GrassPositions[MaxGrass];
bool GrassScan = true;
int GrassTicker = 0;

void UpdateCustom(int ID) {
    switch (ID) {
    case 1:
        if (!CheckCollisionBoxSphere(OmegaPlayer.PlayerBounds, {400, 100, 400}, 393)) {
            OmegaTechData.MainCamera.position.x = 105;
            OmegaTechData.MainCamera.position.y = 15;
            OmegaTechData.MainCamera.position.z = 365;
        }

        break;

    default:
        break;
    }

    if (GrassEnabled) {

        if (GrassTicker != 60 * 3) {
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) != 0 || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) != 0)
                GrassTicker++;
        } else {
            GrassTicker = 0;
            GrassScan = true;
        }
        if (GrassScan) {
            int Range = 75;

            for (int i = 0; i <= RenderedGrass - 1; i++) {
                int GrassX = GetRandomValue(int(OmegaTechData.MainCamera.position.x - Range),
                                            int(OmegaTechData.MainCamera.position.x + Range));
                int GrassZ = GetRandomValue(int(OmegaTechData.MainCamera.position.z - Range),
                                            int(OmegaTechData.MainCamera.position.z + Range));
                int GrassHeight = TerrainHeightMap[GrassZ][GrassX];

                GrassPositions[i] = {GrassX, GrassHeight, GrassZ};
            }

            GrassScan = false;
        }

        for (int i = 0; i <= RenderedGrass - 1; i++) {
            DrawModelEx(WDLModels.FastModel1, GrassPositions[i], {0, 0, 0}, 0, {1, 1, 1}, WHITE);
        }
    }
}

float lerp(float value, float start_range, float end_range, float start_value, float end_value) {
    return start_value + (end_value - start_value) * ((value - start_range) / (end_range - start_range));
}

float CalculateHeartRate(float elevation) {
    float startElevation = 0.0f;
    float endElevation = 32.0f;
    float startHeartRate = 65.0f;
    float endHeartRate = 0.0f;

    return lerp(elevation, startElevation, endElevation, startHeartRate, endHeartRate);
}

auto UpdateCustomUI(int ID) {
    switch (ID) {
    case 1:
        if (OmegaTechData.Ticker == 60) {
            CustomData.HeartRate = int(CalculateHeartRate(OmegaTechData.MainCamera.position.y - 9));

            if (ToggleFlags[1].Value == 1) {
                CustomData.HeartRate += 20;
            }
        }

        if (!CustomData.HRWarning && CustomData.HeartRate < 20) {
            OmegaTechTextSystem.Write("Its So Cold Up here..| I can feel my skin freezing| I have to warm up.|/");
            CustomData.HRWarning = true;
        }

        if (CustomData.HeartRate < 10) {
            PlayFadeIn();
            CustomData.PlayEnding = true;

            PlaySound(CustomData.Ending1Music);
        }

        DrawTextEx(CustomData.CustomFont, TextFormat("Heart Rate: %i", CustomData.HeartRate), {10, 680}, 35, 1, WHITE);

        break;

    default:
        break;
    }
}