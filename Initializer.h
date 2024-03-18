#pragma once

#include "Abilities.h"
#include "Trainers.h"
#include "Pokemon.h"
#include "PokemonData.h"
#include "raylib.h"

#include <random>

class Initializer
{
private:
    Trainers player;

public:
    Initializer();
    ~Initializer();
    int ChooseInt(int min, int max);
    /*Pokemon NewPokemon();*/
    void CreatePlayer();
    Trainers& GetPlayer();
    bool GetInitFinish();
    void Start();
    void Update();
    void Draw();
    void Unload();
};
