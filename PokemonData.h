#pragma once

#include <vector>
#include <string>
#include <map>

#include "PokeType.h"

extern std::vector<std::string> allPokemonNames;
extern std::map<std::string, std::string> allPokemonDescriptions;
extern std::map<std::string, PokeType> allPokemonTypes;
extern float resistanceMatrix[18][18];

float GetResistance(int attackType, int defenderType);
std::vector<std::string>& GetAllPokemonNames();
std::string GetPokemonDescription(std::string& pokemonName);
PokeType GetPokemonType(std::string& pokemonName);
