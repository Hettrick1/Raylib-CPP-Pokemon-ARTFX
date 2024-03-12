#include "Initializer.h"
#include "raylib.h"
#include "Abilities.h"
#include "Pokemon.h"
#include "PokemonData.h"

#include <vector>
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

Image bulbasaur;
Image charmander;
Image squirtle;

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

std::string Initializer::ChooseName(std::vector<std::string>& Allnames) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 11);
    return Allnames[dist(gen)];
}

int Initializer::ChooseInt(int min, int max) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

Pokemon Initializer::NewPokemon(std::vector<std::string>& AllNames) {
    std::string name = ChooseName(AllNames);
    std::string description = GetPokemonDescription(name);
    PokeType type = GetPokemonType(name);
    int level = ChooseInt(1, 21);

    return Pokemon(name, type, level, description, 100);
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
    bulbasaur = LoadImage("Images/bulbasaur.png");
    charmander = LoadImage("Images/charmander.png");
    squirtle = LoadImage("Images/squirtle.png");

    ImageResize(&bulbasaur, 100, 100);
    ImageResize(&charmander, 100, 100);
    ImageResize(&squirtle, 100, 100);

    bulbasaurTexture = LoadTextureFromImage(bulbasaur);
    charmenderTexture = LoadTextureFromImage(charmander);
    squirtleTexture = LoadTextureFromImage(squirtle);

    UnloadImage(bulbasaur);
    UnloadImage(charmander);
    UnloadImage(squirtle);

    std::vector<std::string> names = GetAllPokemonNames();

    Trainers dresseur("Ash", "alfn", "afkj", 100, 100, 10);

    for (int i = 0; i < 2; i++)
    {
        Pokemon newPokemon = NewPokemon(names);
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
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
    else if (!isChoosingName && !hasFirstPokemon){
        DrawText("Welcome ", 240, 40, 40, GRAY);
        DrawText(playerFirstName.c_str(), 240 + MeasureText("Welcome ", 40), 40, 40, RED);
        DrawTexture(bulbasaurTexture, 400 - 50 - 200, 200, WHITE);
        DrawText("Bulbasaur", 150, 320, 20, BLACK);
        DrawRectangleLines(150, 200, 100, 100, DARKGRAY);
        DrawTexture(charmenderTexture,400 - 50 + 200, 200, WHITE);
        DrawText("Charmander", 550, 320, 20, BLACK);
        DrawRectangleLines(550, 200, 100, 100, DARKGRAY);
        DrawTexture(squirtleTexture,400 - 50, 200, WHITE);
        DrawText("Squirtle", 350, 320, 20, BLACK);
        DrawRectangleLines(350, 200,100, 100, DARKGRAY);
    }
    else if (hasFirstPokemon && hasLoaded){
        WaitTime(0.2);
        std::string pokemonName = player.GetTeam()[0].GetName();
        DrawText(TextFormat("You choose: %s", pokemonName.c_str()), 240, 40, 40, GRAY);
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        initialisationFinished = true;
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
                firstPokemon = Pokemon("Bulbizarre", PokeType::GRASS, 1, "Il a une etrange graine plantee sur son dos. Elle grandit avec lui depuis sa naissance.", 100);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), charmanderBox)) 
        { 
            mouseOnCharmender = true; 
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstPokemon = Pokemon("Carapuce", PokeType::WATER, 1, "La flamme sur sa queue represente l energie vitale de Salameche. Quand il est vigoureux, elle brule plus fort.", 100);
                hasFirstPokemon = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), squirtleBox)) 
        { 
            mouseOnSquirtle = true; 
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstPokemon = Pokemon("Salamèche", PokeType::FIRE, 1, "Il se refugie dans sa carapace et replique en eclaboussant l ennemi a la premiere occasion.", 100);
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
    if (hasFirstPokemon) {
        Trainers defaultPlayer(playerFirstName);
        player = defaultPlayer;
        player.AddPokemon(firstPokemon);
        hasLoaded = true;
    }
}
bool Initializer::GetInitFinish() {
    return initialisationFinished;
}

