#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Abilities.h"
#include "Pokemon.h"

class Trainers
{
private:
	std::string mName;
	std::string mLastName;
	std::string mCatchPhrase;
	int mMoney;
	int mLifePoints;
	int mPokeballs;
	std::vector<Pokemon> mTeam;
	Pokemon* mCurrentPokemon;

public:
	Trainers();
	Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, int dMoney, int dLifePoints, int dPokeballs);
	Trainers(std::string dName, Pokemon& dFirstPokemon);
	~Trainers();
	std::string GetName();
	std::vector<Pokemon>& GetTeam();
	void AddPokemon(Pokemon& pokemon);
	void ShowTeam();
	void Introduce();
	void EarnMoney(int amount);
	void EarnPokeballs(int count);
	void ChangeCurrentPokemon();
	Pokemon* GetCurrentPokemon();
	int GetMoney();
	void SetCurrentPokemon(Pokemon& pokemon);
	void SetCurrentPokemon(int pokemon);
};

