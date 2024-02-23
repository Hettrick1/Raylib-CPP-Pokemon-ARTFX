#include "Initializer.h"

#include "Abilities.h"
#include "Pokemon.h"
#include "PokemonData.h"

#include <vector>

Initializer::Initializer() {
    std::vector<std::string> names = GetAllPokemonNames();

    Trainers dresseur("Ash", "alfn", "afkj", 100, 100, 10);

    for (int i = 0; i < 2; i++)
    {
        Pokemon newPokemon = NewPokemon(names);
        dresseur.AddPokemon(newPokemon);
    }
    AllDresseurs.push_back(dresseur);

    Abilities newAbility("hello", 10, PokeType::ELECTRIC);
    abilitiesAvailable.push_back(newAbility);

    CreatePlayer();
}
Initializer::~Initializer() {}

std::string Initializer::ChooseName(std::vector<std::string>& Allnames) {
    Random random;
    int randomIndex = random.RangeInt(0, static_cast<int>(Allnames.size() - 1));
    return Allnames[randomIndex];
}

int Initializer::ChooseInt(int min, int max) {
    Random random;
    int randomInt = random.RangeInt(min, max);
    return randomInt;
}

Pokemon Initializer::NewPokemon(std::vector<std::string>& AllNames) {
    std::string name = ChooseName(AllNames);
    std::string description = GetPokemonDescription(name);
    PokeType type = GetPokemonType(name);
    int level = ChooseInt(1, 21);
    int health = ChooseInt(20, 51);

    return Pokemon(name, type, level, description, static_cast<float>(health));
}

Trainers& Initializer::GetDresseur(int dresseurIndex) {
    return AllDresseurs[dresseurIndex];
}

std::vector<Abilities>& Initializer::GetAbilitiesAvailable() {
    return abilitiesAvailable;
}

Trainers& Initializer::GetPlayer() {
    return player;
}

void Initialisation::CreatePlayer() {
    std::string playerFirstName, playerLastName, playerCatchphrase;
    int answer;
    Pokemon firstPokemon;

    std::cout << "Bonjour jeune dresseur, quel est ton prénom ?\n";
    std::cin >> playerFirstName;
    std::cout << "Ton nom de famille ?\n";
    std::cin >> playerLastName;
    std::cout << "Qu'elle est ta catchphrase ?\n";
    std::cin >> playerCatchphrase;
    std::cout << "Tu as le choix entre trois pokemons : \n1. Bulbizarre - Herbe\n2. Carapuce - Eau\n3. Salamèche - Feu\n";
    do {
        std::cout << "Avec lequel veux - tu commencer ? \n";
        std::cin >> answer;
    } while (answer <= 0 || answer > 3);
    switch (answer)
    {
    case 1:
        firstPokemon = Pokemon("Bulbizarre", PokeType::GRASS, 1, "Il a une etrange graine plantee sur son dos. Elle grandit avec lui depuis sa naissance.", 100);
        break;
    case 2:
        firstPokemon = Pokemon("Carapuce", PokeType::WATER, 1, "La flamme sur sa queue represente l energie vitale de Salameche. Quand il est vigoureux, elle brule plus fort.", 100);
        break;
    case 3:
        firstPokemon = Pokemon("Salamèche", PokeType::FIRE, 1, "Il se refugie dans sa carapace et replique en eclaboussant l ennemi a la premiere occasion.", 100);
        break;
    }
    Dresseur defaultPlayer(playerFirstName, playerLastName, playerCatchphrase, firstPokemon);
    player = defaultPlayer;
    player.AddPokemon(firstPokemon);
    std::cout << "Vous avez choisi : " << firstPokemon.GetName() << "\n";
}