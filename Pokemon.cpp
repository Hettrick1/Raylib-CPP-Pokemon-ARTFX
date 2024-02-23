#include "Pokemon.h"
#include "Trainers.h"
#include "Abilities.h"
#include "PokemonData.h"

Pokemon::Pokemon()
{
}

Pokemon::Pokemon(std::string name, PokeType type, int level, std::string description, float health) {
	mName = name;
	mType = type;
	mLevel = level;
	mDescription = description;
	mHealth = health;
	mMaxHealth = health;
	mIncapacited = false;
}
Pokemon::~Pokemon() {}

std::string Pokemon::GetName() const { return mName; }
int Pokemon::GetLevel() const { return mLevel; }
std::string Pokemon::GetDescription() const { return mDescription; }
float Pokemon::GetHealth() const { return mHealth; }
PokeType Pokemon::GetType() { return mType; }
bool Pokemon::GetIncapacited() { return mIncapacited; }

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
		std::cout << "la capacit� " << ability.GetAbilityName() << " ne peut plus �tre utilis�e. \n";
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

void Pokemon::LearnAbilities(std::vector<Abilities>& allAbilities) {
	int answer;
	size_t abilitiesAvailableSize = allAbilities.size();

	if (mAbilities.size() < 5) {
		std::cout << "\nVotre pokemon peut apprendre ces abilites, laquelle voulez-vous ?\n";
		for (int i = 0; i < abilitiesAvailableSize; i++) {
			std::cout << i + 1 << ". " << allAbilities[i].GetAbilityName() << ".\n";
		}
		do {
			std::cin >> answer;
		} while (answer <= 0 || answer > abilitiesAvailableSize);
		mAbilities.push_back(allAbilities[answer - 1]);
		std::cout << "Votre pokemon " << mName << " vient d'apprendre l'abilit� : " << allAbilities[answer - 1].GetAbilityName() << ".\n";
	}
	else {
		std::cout << "Votre pokemon " << mName << " ne peut plus apprendre d'abilites.\n";
	}
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