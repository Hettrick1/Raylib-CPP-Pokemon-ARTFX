#pragma once
#include "Trainers.h"
#include "Pokemon.h"
#include "PokemonData.h"

#include <random>
#include <vector>


class Battle
{
private :
	bool stopBattle;
	bool enemyDefeated;
public:
	Battle();
	~Battle();
	void Update(Trainers& player, bool isInHighGrass);
	void Draw(Trainers& player, bool isInHighGrass, Texture2D& battleBackGround, Texture2D& pokeball, Texture2D& gold, Texture2D& enemyPokemonInfos, Texture2D& playerPokemonInfos);
	int ChooseInt(int min, int max);
	void AgainstPokemon(Trainers& player, Pokemon& pokemon);
	void AgainstTrainer(Trainers& player, Trainers& opponent);
	void EnterBattle();
	void QuitBattle();
	bool GetQuitBattle();
	bool GetDefeated();
};

