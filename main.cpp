#include "raylib.h"
#include "PokemonData.h"
#include "Initializer.h"
#include "Event.h"
#include "Pokemon.h"
#include "Trainers.h"
#include "Abilities.h"
#include "Battle.h"
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

Initializer init = Initializer();
Event event = Event();

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
    WaitTime(0.01f);
    LoadPokemonDatas();
}

void Start()
{
    center_window(WIDTH, HEIGHT);
    init.Start();
    event.Start();
}

void Update()
{
    deltaTime = GetFrameTime();
    init.CreatePlayer();
    if (init.GetInitFinish()) {
        event.Update();
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    init.Draw();
    if (init.GetInitFinish()) {
        event.Draw();
    }
    EndDrawing();
}

void Unload()
{
    init.Unload();
    event.Unload();
    UnloadPokemonDatas();
    CloseWindow();
}

void center_window(float window_width, float window_height)
{
    int monitor = GetCurrentMonitor();
    int monitor_width = GetMonitorWidth(monitor);
    int monitor_height = GetMonitorHeight(monitor);
    SetWindowPosition((int)(monitor_width / 2) - (int)(window_width / 2), (int)(monitor_height / 2) - (int)(window_height / 2));
}
