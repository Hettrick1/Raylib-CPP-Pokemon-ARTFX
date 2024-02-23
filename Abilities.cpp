#include "Abilities.h"

Abilities::Abilities(std::string name, float damages, PokeType type) {
	mName = name;
	mDamages = damages;
	mType = type;
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

bool Abilities::CanUse() {
	return mCurrentUses < mMaxUses;
}
void Abilities::ResetUses() {
	mCurrentUses = 0;
}
void Abilities::SetCurrentUses() {
	mCurrentUses++;
}