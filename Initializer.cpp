#include "Initializer.h"

#define MAX_INPUT_CHARS     9

Rectangle textBox = {425, 300, 230, 50};
Rectangle bulbasaurBox = {290, 300, 100, 100};
Rectangle squirtleBox = {490, 300, 100, 100};
Rectangle charmanderBox = {690, 300, 100, 100};
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
        DrawText("Hello trainer ! What is your name ?", 540 - MeasureText("Hello trainer ! What is your name ?", 30)/2, 250, 30, BLACK);
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, DARKGRAY);
        DrawText(name, textBox.x + 5, textBox.y + 8, 40, MAROON);

        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 540 - MeasureText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 20)/2, 365, 20, DARKGRAY);
        if (letterCount < MAX_INPUT_CHARS)
        {
            if (((framesCounter / 60) % 2) == 0) DrawText("_", textBox.x + 8 + MeasureText(name, 40), textBox.y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", 540 - MeasureText("Press BACKSPACE to delete chars...", 20)/2, 400, 20, GRAY);
    }
    else if (!isChoosingName && !hasFirstPokemon)
    {
        DrawText(TextFormat("Welcome %s !", playerFirstName.c_str()), 540 - MeasureText(TextFormat("Welcome %s !", playerFirstName.c_str()), 40) / 2, 140, 40, BLACK);
        DrawText("Choose your first Pokemon !", 540 - MeasureText("Choose your first Pokemon !", 30) / 2, 220, 30, GRAY);

        DrawTextureEx(bulbasaurTexture, Vector2{ bulbasaurBox.x-15, 265}, 0.0f, 2, WHITE);
        DrawText("Bulbasaur", bulbasaurBox.x + (bulbasaurBox.width -MeasureText("Bulbasaur", 20))/2, bulbasaurBox.y + 110, 20, BLACK);
        DrawRectangleLines(bulbasaurBox.x, bulbasaurBox.y, bulbasaurBox.width, bulbasaurBox.height, DARKGRAY);

        DrawTextureEx(squirtleTexture, Vector2{ squirtleBox.x-15, 265 }, 0.0f, 2, WHITE);
        DrawText("Squirtle", squirtleBox.x + (squirtleBox.width - MeasureText("Squirtle", 20)) / 2, squirtleBox.y + 110, 20, BLACK);
        DrawRectangleLines(squirtleBox.x, squirtleBox.y, squirtleBox.width, squirtleBox.height, DARKGRAY);

        DrawTextureEx(charmenderTexture, Vector2{ charmanderBox.x-15, 265}, 0.0f, 2, WHITE);
        DrawText("Charmander", charmanderBox.x + (charmanderBox.width - MeasureText("Charmander", 20)) / 2, charmanderBox.y + 110, 20, BLACK);
        DrawRectangleLines(charmanderBox.x, charmanderBox.y, charmanderBox.width, charmanderBox.height, DARKGRAY);     
    }
    else if (hasFirstPokemon && hasLoaded && !isChoosingName && !initialisationFinished)
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        DrawText(TextFormat("You choose: %s", pokemonName.c_str()), 540 - MeasureText(TextFormat("You choose: %s", pokemonName.c_str()), 40) / 2, 150, 40, BLACK);
        DrawTextureEx(player.GetTeam()[0].GetFrontSprite(), Vector2{static_cast<float>(650) - player.GetTeam()[0].GetFrontSprite().width,static_cast<float>(190) - player.GetTeam()[0].GetFrontSprite().height}, 0.0f, 5, WHITE);
        DrawTextBoxed(GetFontDefault(), player.GetTeam()[0].GetDescription().c_str(), Rectangle{250, 260, 360, 300}, 30, 1.5f, true, BLACK);
        DrawText("Press ENTER to continue", 540 - MeasureText("Press ENTER to continue", 30) / 2, 510, 30, LIGHTGRAY);
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
        framesCounter++;
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
                firstPokemon = GetPokemon(2);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), squirtleBox))
        {
            mouseOnSquirtle = true;
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                firstPokemon = GetPokemon(1);
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
