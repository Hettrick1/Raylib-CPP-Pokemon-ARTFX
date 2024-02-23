#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Abilities.h"
#include "Pokemon.h"

class Trainers
{
private:
	std::string name;
	std::string lastName;
	std::string catchPhrase;
	int money;
	int lifePoints;
	int pokeballs;
	std::vector<Pokemon> team;
	Pokemon* currentPokemon;

public:
	Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, int dMoney, int dLifePoints, int dPokeballs);
	Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, Pokemon& dFirstPokemon);
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

