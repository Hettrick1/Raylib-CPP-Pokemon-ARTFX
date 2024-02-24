#include "PokemonData.h"

std::vector<std::string> allPokemonNames = {
    "Bulbizarre", "Pikachu", "Salameche", "Carapuce", "Chenipan", "Rattata", "Roucool", "Rondoudou", "Psykokwak", "Abra", "Racaillou"
};

std::map<std::string, std::string> allPokemonDescriptions = {
    { "Bulbizarre", "Il a une etrange graine plantee sur son dos. Elle grandit avec lui depuis sa naissance." },
    { "Pikachu", " Il eleve sa queue pour surveiller les environs. Elle attire souvent la foudre dans cette position." },
    { "Salameche", "La flamme sur sa queue represente l energie vitale de Salameche. Quand il est vigoureux, elle brule plus fort." },
    { "Carapuce", "Il se refugie dans sa carapace et replique en eclaboussant l ennemi a la premiere occasion." },
    { "Chenipan", "Pour se proteger, il emet un gaz puant par ses antennes, qui fait fuir ses ennemis audacieux." },
    { "Rattata", "Vivant la ou se trouve la nourriture, ce charognard passe ses journees a la rechercher." },
    { "Roucool", "On l apercoit souvent dans les forets. Avec ses ailes, il brasse l air près du sol pour projeter du sable." },
    { "Rondoudou", "Il hypnotise ses ennemis grace a ses grands yeux avant de les plonger dans un profond sommeil en chantant une douce melopee." },
    { "Psykokwak", "Ce Pokemon a tout le temps la migraine. Quand la douleur devient insupportable, il se met a utiliser ses pouvoirs psy." },
    { "Abra", "Il dort 18 h par jour. Il peut utiliser de nombreux pouvoirs psy, meme pendant son sommeil." },
    { "Racaillou", "Il vit dans les plaines ou les montagnes. On le confond souvent avec un petit caillou." }
};

std::map<std::string, PokeType> allPokemonTypes = {
    { "Bulbizarre", PokeType::GRASS },
    { "Pikachu", PokeType::ELECTRIC },
    { "Salameche", PokeType::FIRE },
    { "Carapuce", PokeType::WATER },
    { "Chenipan", PokeType::BUG },
    { "Rattata", PokeType::NORMAL },
    { "Roucool", PokeType::NORMAL },
    { "Rondoudou", PokeType::FAIRY },
    { "Psykokwak", PokeType::WATER },
    { "Abra", PokeType::PSYSCHIC },
    { "Racaillou", PokeType::ROCK }
};

float resistanceMatrix[18][18] = {
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0},
    {1.0, 0.5, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0},
    {1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0},
    {1.0, 0.5, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0},
    {1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0},
    {1.0, 0.5, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0},
    {2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5},
    {1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0},
    {1.0, 2.0, 1.0, 0.5, 2.0, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0},
    {1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0},
    {1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5},
    {1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0},
    {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5},
    {1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0},
    {1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0}
};

float GetResistance(int attackType, int defenderType) {
    return resistanceMatrix[attackType][defenderType];
}

std::vector<std::string>& GetAllPokemonNames() {
    return allPokemonNames;
}
std::string GetPokemonDescription(std::string& pokemonName) {
    return allPokemonDescriptions[pokemonName];
}
PokeType GetPokemonType(std::string& pokemonName) {
    return allPokemonTypes[pokemonName];
}