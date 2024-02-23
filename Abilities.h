#pragma once

#include <iostream>
#include <string>

#include "Poketype.h"

class Abilities
{
private:
	std::string mName;
	float mDamages;
	int mMaxUses;
	int mCurrentUses;
	PokeType mType;

public:
	Abilities(std::string name, float damages, PokeType type);
	~Abilities();
	float GetDamages();
	PokeType GetAbilityType();
	std::string GetAbilityName();
	bool CanUse();
	void ResetUses();
	void SetCurrentUses();
};

