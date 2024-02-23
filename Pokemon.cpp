#include "Pokemon.h"
#include "Trainers.h"
#include "Abilities.h"
#include "PokemonData.h"

Pokemon::Pokemon(std::string pName, PokeType pType, int pLevel, std::string pDescription, float pHealth) {
	name = pName;
	type = pType;
	level = pLevel;
	description = pDescription;
	health = pHealth;
	maxHealth = pHealth;
	incapacited = false;
}
Pokemon::~Pokemon() {}

std::string Pokemon::GetName() const { return name; }
int Pokemon::GetLevel() const { return level; }
std::string Pokemon::GetDescription() const { return description; }
float Pokemon::GetHealth() const { return health; }
PokeType Pokemon::GetType() { return type; }
bool Pokemon::GetIncapacited() { return incapacited; }

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
	if (health > damages) {
		health -= damages;
	}
	else {
		incapacited = true;
		health = 0;
	}
}

void Pokemon::LearnAbilities(std::vector<Abilities>& allAbilities) {
	int answer;
	size_t abilitiesAvailableSize = allAbilities.size();

	if (abilities.size() < 5) {
		std::cout << "\nVotre pokemon peut apprendre ces abilites, laquelle voulez-vous ?\n";
		for (int i = 0; i < abilitiesAvailableSize; i++) {
			std::cout << i + 1 << ". " << allAbilities[i].GetAbilityName() << ".\n";
		}
		do {
			std::cin >> answer;
		} while (answer <= 0 || answer > abilitiesAvailableSize);
		abilities.push_back(allAbilities[answer - 1]);
		std::cout << "Votre pokemon " << name << " vient d'apprendre l'abilité : " << allAbilities[answer - 1].GetAbilityName() << ".\n";
	}
	else {
		std::cout << "Votre pokemon " << name << " ne peut plus apprendre d'abilites.\n";
	}
}
void Pokemon::GoOutOfPokeball() {
	std::cout << name << " est sorti de sa pokeball.\n";
}
void Pokemon::GoInAPokeball() {
	std::cout << name << " est entre dans sa pokeball.\n";
}

void Pokemon::Rest() {
	health = maxHealth;
	for (Abilities& ability : abilities) {
		ability.ResetUses();
	}
}

std::vector<Abilities>& Pokemon::GetAbilities() {
	return abilities;
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