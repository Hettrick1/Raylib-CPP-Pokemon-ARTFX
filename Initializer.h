#pragma once
#include <vector>

#include "Abilities.h"
#include "Trainers.h"
#include "Pokemon.h"

class Initializer
{
private:
	std::vector<Trainers> AllDresseurs;
	Trainers player;
	std::vector<Abilities> abilitiesAvailable;
public:
	Initializer();
	~Initializer();
	std::string ChooseName(std::vector<std::string>& Allnames);
	int ChooseInt(int min, int max);
	Pokemon NewPokemon();
	Trainers& GetTrainer(int trainerIndex);
	std::vector<Abilities>& GetAbilitiesAvailable();
	void CreatePlayer();
	Trainers& GetPlayer();
	bool GetInitFinish();
	void Start();
	void Update();
	void Draw();
	void Unload();
};

