#pragma once

#include "raylib.h"
#include "Pokemon.h"
#include "Trainers.h"
#include "Battle.h"
#include "PokemonData.h"
#include "Pokestop.h"

#include <random>

class Event
{
private:
public:
	Event();
	~Event();
	void Load();
	void Start();
	void Update(Trainers& player);
	void Draw(Trainers& player);
	void Unload();
	int ChooseInt(int min, int max);
	void Pokestop(Trainers& player);
	void HighGrass(Trainers& player);
	void LakeShores(Trainers& player);
};

