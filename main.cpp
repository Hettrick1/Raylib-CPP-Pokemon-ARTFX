#include "raylib.h"
#include "Initializer.h"
#include "Event.h"
#include "Pokemon.h"
#include "Trainers.h"
#include "Abilities.h"
#include "Battle.h"
#include <iostream>

constexpr int WIDTH = 1080;
constexpr int HEIGHT = 720;
float deltaTime;

Texture2D cadreTexture;

void Load();
void Start();
void Update();
void Draw();
void Unload();
void center_window(float window_width, float window_height);

Initializer init = Initializer();
Event event = Event();

int main()
{
    Load();
    Start();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
    Unload();
    return 0;
}

void Load()
{
    InitWindow(WIDTH, HEIGHT, "PokemonLikeGame");
    cadreTexture = LoadTexture("Images/cadre.png");
    event.Load();
    SetTargetFPS(60);
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
    if (init.GetInitFinish())
    {
        event.Update(init.GetPlayer());
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground(Color({245, 245, 245, 255}));
    DrawTextureEx(cadreTexture, Vector2({ 0,0 }), 0, 1, WHITE);
    init.Draw();
    if (init.GetInitFinish())
    {
        event.Draw(init.GetPlayer());
    }
    EndDrawing();
}

void Unload()
{
    UnloadTexture(cadreTexture);
    init.Unload();
    event.Unload();
    CloseWindow();
}

void center_window(float window_width, float window_height)
{
    int monitor = GetCurrentMonitor();
    int monitor_width = GetMonitorWidth(monitor);
    int monitor_height = GetMonitorHeight(monitor);
    SetWindowPosition(monitor_width / 2 - static_cast<int>(window_width / 2),
                      monitor_height / 2 - static_cast<int>(window_height / 2));
}
