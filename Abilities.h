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
	PokeType mType;

public:
	Abilities();
	Abilities(std::string name, float damages, PokeType type);
	~Abilities();
	float GetDamages();
	PokeType GetAbilityType();
	std::string GetAbilityName();
	bool CanUse();
	void ResetUses();
	void SetCurrentUses();
};

