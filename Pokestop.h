#pragma once

#include "Trainers.h"
#include "raylib.h"
#include "Pokemon.h"

#include <vector>

class Pokestop
{
public:
	Pokestop();
	~Pokestop();
	void Update(Trainers& player);
	void Draw(Trainers& player);
	void EnterPokestop(Trainers& player);
	void QuitPokestop();
	bool GetQuitPokestop();
};

