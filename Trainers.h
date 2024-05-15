#pragma once

#include "Abilities.h"
#include "Pokemon.h"

#include <vector>
#include <iostream>
#include <string>

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
	int mCurrentPokemonIndex;

public:
	Trainers();
	Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, int dMoney, int dLifePoints, int dPokeballs);
	Trainers(std::string dName);
	~Trainers();
	std::string GetName();
	std::vector<Pokemon>& GetTeam();
	void AddPokemon(Pokemon& pokemon);
	void ShowTeam();
	void Introduce();
	void EarnMoney(int amount);
	void EarnPokeballs(int count);
	void ChangeCurrentPokemon();
	int GetCurrentPokemonIndex();
	int& GetMoney();
	int& GetPokeballs();
	void SetCurrentPokemon(int pokemonIndex);
	bool GetIfTeamIsIncapacited();
};

