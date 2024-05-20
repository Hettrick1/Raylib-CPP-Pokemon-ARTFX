#include "Trainers.h"
#include "Pokemon.h"

#include <iostream>


Trainers::Trainers()
{
	mName = "Name";
	mLastName = "LastName";
	mCatchPhrase = "CatchPhrase";
	mMoney = 100;
	mLifePoints = 100;
	mPokeballs = 100;
}

Trainers::Trainers(std::string name, std::string lastName, std::string catchPhrase, int money, int lifePoints, int pokeballs) {
	mName = name;
	mLastName = lastName;
	mCatchPhrase = catchPhrase;
	mMoney = money;
	mLifePoints = lifePoints;
	mPokeballs = pokeballs;
	mCurrentPokemonIndex = 0;
	mTeam.reserve(6);
}
Trainers::Trainers(std::string name) {
	mName = name;
	mMoney = 1000;
	mLifePoints = 100;
	mPokeballs = 10;
	mCurrentPokemonIndex = 0;
	mTeam.reserve(6);
}
Trainers::~Trainers() {}
std::string Trainers::GetName() { return mName; }
std::string Trainers::GetLastName()
{
	return mLastName;
}
std::string Trainers::GetCatchPhrase()
{
	return mCatchPhrase;
}
void Trainers::AddPokemon(Pokemon& pokemon) {
	mTeam.push_back(pokemon);
}
std::vector<Pokemon>& Trainers::GetTeam() { return mTeam; }
void Trainers::ShowTeam() {
	std::cout << "Dresseur : " << mName << "\nTeam : \n";
	for (Pokemon& pokemon : mTeam) {
		std::cout << pokemon.GetName() << " " << pokemon.GetLevel() << "\nDescription : " << pokemon.GetDescription() << "\n";
	}
}
void Trainers::Introduce() { // modifier pour afficher les sprites des trainers et leur faire dire leur catchphrase
	std::cout << "Bonjour, mon nom est " << mName << " " << mLastName << ".\n" << mCatchPhrase << "\n";
}
void Trainers::EarnMoney(int amount) {
	mMoney += amount;
}

void Trainers::EarnPokeballs(int count) {
	mPokeballs += count;
}

void Trainers::ChangeCurrentPokemon() {
	std::vector<Pokemon*> pokemonsAvailable;
	int answer = 0;
	for (Pokemon& pokemon : mTeam) {
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

	mCurrentPokemonIndex = answer - 1;
	std::cout << "Vous avez choisi : " << mTeam[mCurrentPokemonIndex].GetName() << ".\n";
}

int Trainers::GetCurrentPokemonIndex() {
	return mCurrentPokemonIndex;
}

int& Trainers::GetMoney() {
	return mMoney;
}
int& Trainers::GetPokeballs()
{
	return mPokeballs;
}
void Trainers::SetCurrentPokemon(int pokemonIndex)
{
	mCurrentPokemonIndex = pokemonIndex;
}

bool Trainers::GetIfTeamIsIncapacited()
{
	for (int i = 0; i < mTeam.size(); i++) {
		if (!mTeam[i].GetIncapacited()) {
			return false;
		}
	}
	return true;
}