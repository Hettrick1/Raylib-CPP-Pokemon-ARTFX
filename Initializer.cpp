#include "Initializer.h"

#define MAX_INPUT_CHARS     9

Rectangle textBox = {300, 180, 225, 50};
Rectangle bulbasaurBox = {150, 200, 100, 100};
Rectangle charmanderBox = {350, 200, 100, 100};
Rectangle squirtleBox = {550, 200, 100, 100};
char name[MAX_INPUT_CHARS + 1] = "\0";
int letterCount = 0;
int framesCounter = 0;
bool isChoosingName = true;
bool hasFirstPokemon = false;
bool hasLoaded = false;
std::string playerFirstName;
std::string pokemonName;

Texture2D bulbasaurTexture;
Texture2D charmenderTexture;
Texture2D squirtleTexture;

bool mouseOnBulbasaur = false;
bool mouseOnCharmender = false;
bool mouseOnSquirtle = false;

bool initialisationFinished = false;

int index;

Initializer::Initializer()
{
}

Initializer::~Initializer()
{
}

int Initializer::ChooseInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

Trainers& Initializer::GetPlayer()
{
    return player;
}

void Initializer::Start()
{
    LoadPokemonDatas();
    bulbasaurTexture = LoadTexture("Images/bulbasaur.png");
    charmenderTexture = LoadTexture("Images/charmander.png");
    squirtleTexture = LoadTexture("Images/squirtle.png");
    for (int j = 0; j < 6; j++)
    {
        Trainers trainer = GetTrainer(j);
        for (int i = 0; i < 2; i++)
        {
            index = ChooseInt(0, 10);
            Pokemon newPokemon = GetPokemon(index);
            trainer.AddPokemon(newPokemon);
        }
    }
}

void Initializer::Update()
{
    CreatePlayer();
}

void Initializer::Draw()
{
    if (isChoosingName)
    {
        DrawText("Hello trainer ! What is your name ?", 240, 140, 20, GRAY);
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width),
                           static_cast<int>(textBox.height), DARKGRAY);
        DrawText(name, static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);

        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
        if (letterCount < MAX_INPUT_CHARS)
        {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name, 40),
                                                          static_cast<int>(textBox.y) + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
    else if (!isChoosingName && !hasFirstPokemon)
    {
        DrawText(TextFormat("Welcome %s", playerFirstName.c_str()),
                 400 - MeasureText(TextFormat("Welcome %s", playerFirstName.c_str()), 40) / 2, 40, 40, GRAY);
        DrawTextureEx(bulbasaurTexture, Vector2{140, 195}, 0.0f, 2, WHITE);
        DrawText("Bulbasaur", 150, 320, 20, BLACK);
        DrawRectangleLines(150, 200, 100, 100, DARKGRAY);
        DrawTextureEx(charmenderTexture, Vector2{540, 190}, 0.0f, 2, WHITE);
        DrawText("Charmander", 550, 320, 20, BLACK);
        DrawRectangleLines(550, 200, 100, 100, DARKGRAY);
        DrawTextureEx(squirtleTexture, Vector2{330, 190}, 0.0f, 2, WHITE);
        DrawText("Squirtle", 350, 320, 20, BLACK);
        DrawRectangleLines(350, 200, 100, 100, DARKGRAY);
    }
    else if (hasFirstPokemon && hasLoaded && !isChoosingName && !initialisationFinished)
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        DrawText(TextFormat("You choose: %s", pokemonName.c_str()),
                 400 - MeasureText(TextFormat("You choose: %s", pokemonName.c_str()), 40) / 2, 50, 40, BLACK);
        DrawTextureEx(player.GetTeam()[0].GetFrontSprite(), Vector2{
                          static_cast<float>(520) - player.GetTeam()[0].GetFrontSprite().width,
                          static_cast<float>(160) - player.GetTeam()[0].GetFrontSprite().height
                      }, 0.0f, 5, WHITE);
        DrawTextBoxed(GetFontDefault(), player.GetTeam()[0].GetDescription().c_str(), Rectangle{100, 180, 400, 300}, 30,
                      1.5f, true, BLACK);
        DrawText("Press ENTER to continue", 400 - MeasureText("Press ENTER to continue", 30) / 2, 410, 30, LIGHTGRAY);
    }
}

void Initializer::Unload()
{
    UnloadTexture(bulbasaurTexture);
    UnloadTexture(charmenderTexture);
    UnloadTexture(squirtleTexture);
    UnloadPokemonDatas();
}

void Initializer::CreatePlayer()
{
    Pokemon firstPokemon;

    if (isChoosingName)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = static_cast<char>(key);
                name[letterCount + 1] = '\0';
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            playerFirstName = std::string(name);
            isChoosingName = false;
        }
    }
    else if (!isChoosingName && !hasFirstPokemon)
    {
        if (CheckCollisionPointRec(GetMousePosition(), bulbasaurBox))
        {
            mouseOnBulbasaur = true;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                firstPokemon = GetPokemon(0);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), charmanderBox))
        {
            mouseOnCharmender = true;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                firstPokemon = GetPokemon(1);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), squirtleBox))
        {
            mouseOnSquirtle = true;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                firstPokemon = GetPokemon(2);
                hasFirstPokemon = true;
            }
        }
        if (!mouseOnBulbasaur && !mouseOnCharmender && !mouseOnSquirtle)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        else
        {
            mouseOnBulbasaur = false;
            mouseOnCharmender = false;
            mouseOnSquirtle = false;
        }
    }
    if (hasFirstPokemon && !hasLoaded)
    {
        Trainers defaultPlayer(playerFirstName);
        player = defaultPlayer;
        player.AddPokemon(firstPokemon);
        pokemonName = player.GetTeam()[0].GetName();
        hasLoaded = true;
    }
    if (hasLoaded && !initialisationFinished)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            initialisationFinished = true;
        }
    }
}

bool Initializer::GetInitFinish()
{
    return initialisationFinished;
}
