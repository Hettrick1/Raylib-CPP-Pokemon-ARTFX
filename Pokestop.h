#pragma once

#include "Trainers.h"
#include "raylib.h"
#include "Pokemon.h"
#include "Abilities.h"
#include "PokemonData.h"

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
	bool ResetPokemonMouseCursor();
	bool ResetAbilityMouseCursor();
	void OnButtonClickPokemon(int buttonIndex, Trainers& player);
	void OnButtonClickAbility(int buttonIndex, Trainers& player);
	void OnButtonClickAccept(Trainers& player);
	void OnButtonClickRefuse(Trainers& player);
};

