#pragma once

#include "Poketype.h"
#include "Abilities.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Pokemon
{
private:
	std::string mName;
	PokeType mType;
	int mLevel;
	std::string mDescription;
	float mMaxHealth;
	float mHealth;
	std::vector<Abilities> mAbilities;
	bool mIncapacited;
public:
	Pokemon();
	Pokemon(std::string name, PokeType type, int level, std::string description, float health);
	~Pokemon();
	std::string GetName() const;
	PokeType GetType();
	int GetLevel() const;
	std::string GetDescription() const;
	float GetHealth() const;
	bool GetIncapacited();
	float CalculateDamage(Abilities& ability, Pokemon& defender);
	void TakeDamages(float damage);
	void LearnAbilities(std::vector<Abilities>& abilitiesAvailable);
	void GoOutOfPokeball();
	void GoInAPokeball();
	void Rest();
	std::vector<Abilities>& GetAbilities();
	void ChoseAbilities(std::vector<Abilities>& abilities, Pokemon& defender);
};

