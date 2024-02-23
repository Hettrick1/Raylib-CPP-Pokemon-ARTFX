#include "Trainers.h"
#include "Pokemon.h"

#include <iostream>

Trainers::Trainers() {
	name = "Player";
	lastName = "Player";
	catchPhrase = "CatchPhrase";
	money = 100;
	lifePoints = 100;
	pokeballs = 10;
}

Trainers::Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, int dMoney, int dLifePoints, int dPokeballs) {
	name = dName;
	lastName = dLastName;
	catchPhrase = dCatchPhrase;
	money = dMoney;
	lifePoints = dLifePoints;
	pokeballs = dPokeballs;
}
Trainers::Trainers(std::string dName, std::string dLastName, std::string dCatchPhrase, Pokemon& dFirstPokemon) {
	name = dName;
	lastName = dLastName;
	catchPhrase = dCatchPhrase;
	money = 100;
	lifePoints = 100;
	pokeballs = 10;
	currentPokemon = &dFirstPokemon;
}
Trainers::~Trainers() {}
std::string Trainers::GetName() { return name; }
void Trainers::AddPokemon(Pokemon& pokemon) {
	team.push_back(pokemon);
}
std::vector<Pokemon>& Trainers::GetTeam() { return team; }
void Trainers::ShowTeam() {
	std::cout << "Dresseur : " << name << "\nTeam : \n";
	for (const Pokemon& pokemon : team) {
		std::cout << pokemon.GetName() << " " << pokemon.GetLevel() << "\nDescription : " << pokemon.GetDescription() << "\n";
	}
}
void Trainers::Introduce() {
	std::cout << "Bonjour, mon nom est " << name << " " << lastName << ".\n" << catchPhrase << "\n";
}
void Trainers::EarnMoney(int amount) {
	money += amount;
	std::cout << "Earned " << amount << " money. Total money: " << money << "\n";
}

void Trainers::EarnPokeballs(int count) {
	pokeballs += count;
	std::cout << "Earned " << count << " pokeballs. Total pokeballs: " << pokeballs << "\n";
}

void Trainers::ChangeCurrentPokemon() {
	std::vector<Pokemon*> pokemonsAvailable;
	int answer = 0;
	for (Pokemon& pokemon : team) {
		if (!pokemon.GetIncapacited()) {
			pokemonsAvailable.push_back(&pokemon);
		}
	}
	std::cout << "\nVous avez tous ces Pokemons de disponibles pour la bataille, lequel voulez vous choisir ?\n";
	size_t pokemonsAvailableSize = pokemonsAvailable.size();
	for (int i = 0; i < pokemonsAvailableSize; i++) {
		std::cout << i + 1 << ". " << pokemonsAvailable[i]->GetName() << "\n";
	}
	do {
		std::cin >> answer;
	} while (answer <= 0 || answer > pokemonsAvailableSize);

	currentPokemon = pokemonsAvailable[answer - 1];
	std::cout << "Vous avez choisi : " << currentPokemon->GetName() << ".\n";
}

Pokemon* Trainers::GetCurrentPokemon() {
	return currentPokemon;
}

int Trainers::GetMoney() {
	return money;
}
void Trainers::SetCurrentPokemon(Pokemon& pokemon) {
	currentPokemon = &pokemon;
}

void Trainers::SetCurrentPokemon(int pokemon)
{
	currentPokemon = &team[pokemon];
}