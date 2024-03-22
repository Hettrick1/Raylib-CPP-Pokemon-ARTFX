#include "Abilities.h"

Abilities::Abilities()
{
	mName = "name";
	mDamages = 0;
	mType = PokeType::NORMAL;
	mPrice = 0;
	mMaxUses = 5;
	mCurrentUses = 0;
}

Abilities::Abilities(std::string name, float damages, int price, PokeType type) {
	mName = name;
	mDamages = damages;
	mType = type;
	mPrice = price;
	mMaxUses = 5;
	mCurrentUses = 0;
}

Abilities::~Abilities() {}

float Abilities::GetDamages() {
	return mDamages;
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