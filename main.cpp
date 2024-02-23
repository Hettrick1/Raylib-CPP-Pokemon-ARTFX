#include "raylib.h"
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 500;
float deltaTime;

void Load();
void Start();
void Update();
void Draw();
void Unload();
void center_window(float window_width, float window_height);

int main() {
    Load();
    Start();
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    Unload();
    return 0;
}

void Load()
{
    InitWindow(WIDTH, HEIGHT, "Pokemon");
    SetTargetFPS(60);
}

void Start()
{
    center_window(WIDTH, HEIGHT);
}

void Update()
{
    deltaTime = GetFrameTime();
}

void Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}

void Unload()
{
    CloseWindow();
}

void center_window(float window_width, float window_height)
{
    int monitor = GetCurrentMonitor();
    int monitor_width = GetMonitorWidth(monitor);
    int monitor_height = GetMonitorHeight(monitor);
    SetWindowPosition((int)(monitor_width / 2) - (int)(window_width / 2), (int)(monitor_height / 2) - (int)(window_height / 2));
}
