#pragma once

#include "Trainers.h"
#include "raylib.h"
#include "Pokemon.h"

#include <vector>

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
extern std::vector<Trainers> allTrainers;
extern std::vector<Abilities> allAbilities;

void LoadPokemonDatas();
void UnloadPokemonDatas();

void DrawTextBoxed(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap,
                   Color tint);
void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap,
                             Color tint, int selectStart, int selectLength, Color selectTint,
                             Color selectBackTint);
// Draw text using font inside rectangle limits with support for text selection

Pokemon GetPokemon(int pokemonIndex);
Trainers& GetTrainer(int trainerIndex);

float GetResistance(int attackType, int defenderType);
