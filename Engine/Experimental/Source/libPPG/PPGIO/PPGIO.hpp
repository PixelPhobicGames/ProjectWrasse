
#ifndef PPGIO_H
#define PPGIO_H

#pragma once

#include <chrono>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <utility>

#include "raylib.h"

using namespace std;

static int SVPlaceCounter = 0;
static int SVStart = 0;
static int SVEnd = 0;

string WstringToString(wstring wideStr);
wstring CharArrayToWString(const char *charArray);
wstring LoadFile(const char *Path);
float ToFloat(wstring Data);
int GetWDLSize(wstring WData, wstring Extra);
wstring WReadValue(wstring Data, int Start, int End);
wstring WSplitValue(wstring Data, int Place);
int PullConfigValue(const char *Path, int ValueIndex);
bool GetCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2);
int StringToInt(const std::string &Data);
float StringToFloat(string Data);
string SplitValue(string Data, int Place);
string ReadValue(string Data, int Start, int End);

class Input {
  public:
    bool InteractPressed;
    bool InteractDown;
    bool TextButton;

    bool ControllerUsed = false;

    void UpdateInputs() {

        if (IsGamepadAvailable(0)) {
            ControllerUsed = true;
        }

        if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0) {
            ControllerUsed = false;
        }

        if (ControllerUsed) {
            if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
                InteractDown = true;
            } else {
                InteractDown = false;
            }
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
                InteractPressed = true;
            } else {
                InteractPressed = false;
            }
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
                TextButton = true;
            } else {
                TextButton = false;
            }
        } else {
            if (IsMouseButtonDown(0)) {
                InteractDown = true;
            } else {
                InteractDown = false;
            }

            if (IsMouseButtonPressed(0)) {
                InteractPressed = true;
            } else {
                InteractPressed = false;
            }

            if (IsKeyPressed(KEY_SPACE)) {
                TextButton = true;
            } else {
                TextButton = false;
            }
        }
    }
};

static Input OmegaInputController;

#endif