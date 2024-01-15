#include "External/raygui/Style.h"

#include <cstddef>

static bool ShowSettings = false;
static bool Debug = false;
static bool HeadBob = true;
static bool PixelShader = true;
static bool ParticlesEnabled = true;
static bool FPSEnabled = false;
static bool ConsoleToggle = false;
static float ResolutionScale = 1.0f;

static RenderTexture2D Target;

void ToggleSettings() {
    if (ShowSettings) {
        ShowSettings = false;
        HideCursor();
        DisableCursor();
    } else {
        ShowSettings = true;
        ShowCursor();
        EnableCursor();
    }
}

void UpdateSettings() {
}

bool MenuSettings = false;

bool VSYNCToggle = false;
bool MXAAToggle = false;
bool FScreenToggle = false;

bool MuteToggle = false;
float AudioSlider = 100.0f;

void ShowMenuSetiings() {

    if (GuiWindowBox((Rectangle){192, 264, 384, 384}, "OmegaTech2 Settings")) {
        MenuSettings = false;
    }
    GuiPanel((Rectangle){200, 336, 368, 344}, NULL);
    AudioSlider = GuiSlider((Rectangle){216, 336, 120, 16}, NULL, NULL, AudioSlider, 0, 100);

    GuiLabel((Rectangle){232, 312, 120, 24}, "Master Volume");
    GuiLine((Rectangle){200, 360, 368, 12}, NULL);
    GuiLabel((Rectangle){504, 344, 120, 24}, "Audio");

    MXAAToggle = GuiToggle((Rectangle){216, 384, 88, 24}, "MSAA 4x", MXAAToggle);
    VSYNCToggle = GuiToggle((Rectangle){216, 424, 88, 24}, "VSYNC", VSYNCToggle);
    FScreenToggle = GuiToggle((Rectangle){216, 464, 88, 24}, "FullScreen", FScreenToggle);
    GuiPanel((Rectangle){208, 376, 104, 120}, NULL);
    GuiLabel((Rectangle){512, 616, 120, 24}, "Video");

    if (VSYNCToggle) {
        SetConfigFlags(FLAG_VSYNC_HINT);
    } else {
        ClearWindowState(FLAG_VSYNC_HINT);
    }

    if (MXAAToggle) {
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    } else {
        ClearWindowState(FLAG_MSAA_4X_HINT);
    }

    SetMasterVolume(AudioSlider);
    if (MuteToggle) {
        SetMasterVolume(0);
    }
}