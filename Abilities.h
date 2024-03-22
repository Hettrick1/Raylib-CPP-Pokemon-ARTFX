#pragma once

#include "Poketype.h"

#include <iostream>
#include <string>

class Abilities
{
private:
	std::string mName;
	float mDamages;
	int mMaxUses;
	int mCurrentUses;
	int mPrice;
	PokeType mType;

public:
	Abilities();
	Abilities(std::string name, float damages, int price, PokeType type);
	~Abilities();
	float GetDamages();
	PokeType GetAbilityType();
	std::string GetAbilityName();
	int& GetPrice();
	bool CanUse();
	void ResetUses();
	void SetCurrentUses();
};

