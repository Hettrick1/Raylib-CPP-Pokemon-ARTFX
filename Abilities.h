#pragma once

#include "Poketype.h"

#include <iostream>
#include <string>

class Abilities
{
private:
	std::string mName;
	float mDamagesMin;
	float mDamagesMax;
	int mMaxUses;
	int mCurrentUses;
	int mPrice;
	PokeType mType;

public:
	Abilities();
	Abilities(std::string name, float damagesMin, float damagesMax, int price, PokeType type);
	~Abilities();
	float GetDamagesMin();
	float GetDamagesMax();
	PokeType GetAbilityType();
	std::string GetAbilityName();
	int& GetPrice();
	bool CanUse();
	void ResetUses();
	void SetCurrentUses();
	int GetUseRemaning();
};

