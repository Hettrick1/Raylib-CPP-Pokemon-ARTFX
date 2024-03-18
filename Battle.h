#pragma once
#include "Trainers.h"
#include "Pokemon.h"


class Battle
{
private :
	bool stopBattle;
	bool enemyDefeated;
public:
	Battle();
	~Battle();
	void Update();
	void Draw();
	void FightWildPokemon(Trainers& player, Pokemon& wildPokemon);
	void FightTrainer(Trainers& player, Trainers& opponent);
	void QuitBattle();
	bool GetQuitBattle();
	bool GetDefeated();
};

