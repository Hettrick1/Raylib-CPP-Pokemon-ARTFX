#include "Pokemon.h"
#include "Trainers.h"
#include "Abilities.h"
#include "PokemonData.h"

Pokemon::Pokemon()
{
}

Pokemon::Pokemon(std::string name, PokeType type, int level, std::string description, float health, Texture2D frontSpriteTexture, Texture2D backSpriteTexture) {
	mName = name;
	mType = type;
	mLevel = level;
	mDescription = description;
	mHealth = health;
	mMaxHealth = health;
	mIncapacited = false;
	mFrontSpriteTexture = frontSpriteTexture;
	mBackSpriteTexture = backSpriteTexture;
}
Pokemon::~Pokemon() {}

std::string Pokemon::GetName() { return mName; }
int Pokemon::GetLevel() { return mLevel; }
std::string Pokemon::GetDescription() { return mDescription; }
float Pokemon::GetHealth() { return mHealth; }
PokeType Pokemon::GetType() { return mType; }
bool Pokemon::GetIncapacited() { return mIncapacited; }

Texture2D Pokemon::GetFrontSprite()
{
	return mFrontSpriteTexture;
}

Texture2D Pokemon::GetBackSprite()
{
	return mBackSpriteTexture;
}


float Pokemon::CalculateDamage(Abilities& ability, Pokemon& defender) {

	if (ability.CanUse()) {
		ability.SetCurrentUses();
		PokeType attackType = ability.GetAbilityType();

		PokeType defenderType = defender.GetType();

		float resistance = GetResistance(static_cast<int>(attackType), static_cast<int>(defenderType));

		float damage = ability.GetDamages() * resistance;

		return damage;
	}
	else {
		std::cout << "la capacité " << ability.GetAbilityName() << " ne peut plus être utilisée. \n";
		return 0;
	}
}

void Pokemon::TakeDamages(float damages) {
	if (mHealth > damages) {
		mHealth -= damages;
	}
	else {
		mIncapacited = true;
		mHealth = 0;
	}
}

void Pokemon::LearnAbilities(Abilities& ability) {
	mAbilities.push_back(ability);
}
void Pokemon::GoOutOfPokeball() {
	std::cout << mName << " est sorti de sa pokeball.\n";
}
void Pokemon::GoInAPokeball() {
	std::cout << mName << " est entre dans sa pokeball.\n";
}

void Pokemon::Rest() {
	mHealth = mMaxHealth;
	for (Abilities& ability : mAbilities) {
		ability.ResetUses();
	}
}

std::vector<Abilities>& Pokemon::GetAbilities() {
	return mAbilities;
}


void Pokemon::ChoseAbilities(std::vector<Abilities>& abilities, Pokemon& defender) {
	int answer;
	for (int i = 0; i < abilities.size(); i++) {
		std::cout << i + 1 << ". " << abilities[i].GetAbilityName() << ".\n";
	}
	do {
		std::cin >> answer;
	} while (answer <= 0 || answer > abilities.size());
	int damages = CalculateDamage(abilities[answer - 1], defender);
	if (damages > 0) {
		defender.TakeDamages(damages);
		std::cout << "L'abilite " << abilities[answer - 1].GetAbilityName() << " a ete utilisee. Les degats infliges s'elevent a : " << damages << ". \n";
	}
}