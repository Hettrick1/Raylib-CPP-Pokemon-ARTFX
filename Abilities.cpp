#include "Abilities.h"

Abilities::Abilities()
{
	mName = "name";
	mDamagesMin = 0;
	mDamagesMax = 0;
	mType = PokeType::NORMAL;
	mPrice = 0;
	mMaxUses = 5;
	mCurrentUses = 0;
}

Abilities::Abilities(std::string name, float damagesMin, float damagesMax, int price, PokeType type) {
	mName = name;
	mDamagesMin = damagesMin;
	mDamagesMax = damagesMax;
	mType = type;
	mPrice = price;
	mMaxUses = 5;
	mCurrentUses = 0;
}

Abilities::~Abilities() {}

float Abilities::GetDamagesMin() {
	return mDamagesMin;
}

float Abilities::GetDamagesMax()
{
	return mDamagesMax;
}

PokeType Abilities::GetAbilityType() {
	return mType;
}

std::string Abilities::GetAbilityName() {
	return mName;
}

int& Abilities::GetPrice()
{
	return mPrice;
}

bool Abilities::CanUse() {
	return mCurrentUses < mMaxUses;
}
void Abilities::ResetUses() {
	mCurrentUses = 0;
}
void Abilities::SetCurrentUses() {
	mCurrentUses++;
}

int Abilities::GetUseRemaning()
{
	return mMaxUses - mCurrentUses;
}
