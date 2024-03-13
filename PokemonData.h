#pragma once

#include <vector>
#include <string>
#include <map>

#include "Pokemon.h"
#include "PokeType.h"


extern Texture2D bulbasaurFrontTexture;
extern Texture2D bulbasaurBackTexture;

extern Texture2D squirtleFrontTexture;
extern Texture2D squirtleBackTexture;

extern Texture2D charmanderFrontTexture;
extern Texture2D charmanderBackTexture;

extern Texture2D abraFrontTexture;
extern Texture2D abraBackTexture;

extern Texture2D caterpieFrontTexture;
extern Texture2D caterpieBackTexture;

extern Texture2D geodudeFrontTexture;
extern Texture2D geodudeBackTexture;

extern Texture2D jigglypuffFrontTexture;
extern Texture2D jigglypuffBackTexture;

extern Texture2D pidgeyFrontTexture;
extern Texture2D pidgeyBackTexture;

extern Texture2D pikachuFrontTexture;
extern Texture2D pikachuBackTexture;

extern Texture2D psyduckFrontTexture;
extern Texture2D psyduckBackTexture;

extern Texture2D rattataFrontTexture;
extern Texture2D rattataBackTexture;

extern std::vector<Pokemon> allPokemons;

void LoadPokemonDatas();
void UnloadPokemonDatas();

Pokemon GetPokemon(int pokemonIndex);

float GetResistance(int attackType, int defenderType);

