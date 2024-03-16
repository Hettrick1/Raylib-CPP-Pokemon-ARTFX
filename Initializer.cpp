#include "Initializer.h"
#include "raylib.h"
#include "Abilities.h"
#include "Pokemon.h"
#include "PokemonData.h"

#include <iostream>
#include <random>

#define MAX_INPUT_CHARS     9

Rectangle textBox = { 300, 180, 225, 50 };
Rectangle bulbasaurBox = { 150, 200, 100, 100 };
Rectangle charmanderBox = { 350, 200, 100, 100 };
Rectangle squirtleBox = { 550, 200,100, 100 };
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

Initializer::Initializer() {
}
Initializer::~Initializer() {}

// std::string Initializer::ChooseName(std::vector<std::string>& Allnames) {
//
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<int> dist(0, 11);
//     return Allnames[dist(gen)];
// }

int Initializer::ChooseInt(int min, int max) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

Pokemon Initializer::NewPokemon() {
    return GetPokemon(ChooseInt(0,12));
}

Trainers& Initializer::GetTrainer(int dresseurIndex) {
    return AllDresseurs[dresseurIndex];
}

std::vector<Abilities>& Initializer::GetAbilitiesAvailable() {
    return abilitiesAvailable;
}

Trainers& Initializer::GetPlayer() {
    return player;
}

void Initializer::Start()
{
    bulbasaurTexture = LoadTexture("Images/bulbasaur.png");
    charmenderTexture = LoadTexture("Images/charmander.png");
    squirtleTexture = LoadTexture("Images/squirtle.png");

    Trainers dresseur("Ash", "alfn", "afkj", 100, 100, 10);

    for (int i = 0; i < 2; i++)
    {
        Pokemon newPokemon = NewPokemon();
        dresseur.AddPokemon(newPokemon);
    }
    AllDresseurs.push_back(dresseur);

    Abilities newAbility("hello", 10, PokeType::ELECTRIC);
    abilitiesAvailable.push_back(newAbility);

}

void Initializer::Update()
{
    CreatePlayer();
}

void Initializer::Draw()
{
    if (isChoosingName) {
        DrawText("Hello trainer ! What is your name ?", 240, 140, 20, GRAY);
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
        DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
        if (letterCount < MAX_INPUT_CHARS)
        {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
    else if (!isChoosingName && !hasFirstPokemon){
        DrawText(TextFormat("Welcome %s", playerFirstName.c_str()), 400 - MeasureText(TextFormat("Welcome %s", playerFirstName.c_str()), 40)/2, 40, 40, GRAY);
        DrawTextureEx(bulbasaurTexture, Vector2{ 140, 195 }, 0.0f, 2, WHITE);
        DrawText("Bulbasaur", 150, 320, 20, BLACK);
        DrawRectangleLines(150, 200, 100, 100, DARKGRAY);
        DrawTextureEx(charmenderTexture, Vector2{ 540, 190 }, 0.0f, 2, WHITE);
        DrawText("Charmander", 550, 320, 20, BLACK);
        DrawRectangleLines(550, 200, 100, 100, DARKGRAY);
        DrawTextureEx(squirtleTexture, Vector2{ 330, 190 }, 0.0f, 2, WHITE);
        DrawText("Squirtle", 350, 320, 20, BLACK);
        DrawRectangleLines(350, 200,100, 100, DARKGRAY);
    }
    else if (hasFirstPokemon && hasLoaded && !isChoosingName && !initialisationFinished){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        DrawText(TextFormat("You choose: %s", pokemonName.c_str()),400 - MeasureText(TextFormat("You choose: %s", pokemonName.c_str()), 40)/2, 80, 40, BLACK);
        DrawTextureEx(player.GetTeam()[0].GetFrontSprite(), Vector2{(float)520 - player.GetTeam()[0].GetFrontSprite().width, (float)180 - player.GetTeam()[0].GetFrontSprite().height }, 0.0f, 5, WHITE);
        DrawTextBoxed(GetFontDefault(), player.GetTeam()[0].GetDescription().c_str(), Rectangle {100, 200, 400, 300}, 30, 1.5f, true, BLACK);
        DrawText("Press ENTER to continue", 400 - MeasureText("Press ENTER to continue", 30)/2, 430 ,30, LIGHTGRAY);
    }
}

void Initializer::Unload()
{
    UnloadTexture(bulbasaurTexture);
    UnloadTexture(charmenderTexture);
    UnloadTexture(squirtleTexture);
}

void Initializer::CreatePlayer() {
    Pokemon firstPokemon;

    if (isChoosingName) {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = (char)key;
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
        if (IsKeyPressed(KEY_ENTER)) {
            playerFirstName = std::string(name);
            isChoosingName = false;
        }
    }
    else if (!isChoosingName && !hasFirstPokemon){
        if (CheckCollisionPointRec(GetMousePosition(), bulbasaurBox)) 
        { 
            mouseOnBulbasaur = true; 
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstPokemon = GetPokemon(0);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), charmanderBox)) 
        { 
            mouseOnCharmender = true; 
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstPokemon = GetPokemon(1);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), squirtleBox)) 
        { 
            mouseOnSquirtle = true; 
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstPokemon = GetPokemon(2);
                hasFirstPokemon = true;
            }
        }
        if (!mouseOnBulbasaur && !mouseOnCharmender && !mouseOnSquirtle) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        else{
            mouseOnBulbasaur = false;
            mouseOnCharmender = false;
            mouseOnSquirtle = false;
        }
        
    }
    if (hasFirstPokemon && !hasLoaded) {
        Trainers defaultPlayer(playerFirstName);
        player = defaultPlayer;
        player.AddPokemon(firstPokemon);
        pokemonName = player.GetTeam()[0].GetName();
        hasLoaded = true;
    }
    if (hasLoaded && !initialisationFinished) {
        if (IsKeyPressed(KEY_ENTER))
        {
            initialisationFinished = true;
        }
    }
}
bool Initializer::GetInitFinish() {
    return initialisationFinished;
}

