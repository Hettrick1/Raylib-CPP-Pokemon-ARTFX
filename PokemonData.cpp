#include "PokemonData.h"

Texture2D bulbasaurFrontTexture;
Texture2D bulbasaurBackTexture;

Texture2D squirtleFrontTexture;
Texture2D squirtleBackTexture;

Texture2D charmanderFrontTexture;
Texture2D charmanderBackTexture;

Texture2D abraFrontTexture;
Texture2D abraBackTexture;

Texture2D caterpieFrontTexture;
Texture2D caterpieBackTexture;

Texture2D geodudeFrontTexture;
Texture2D geodudeBackTexture;

Texture2D jigglypuffFrontTexture;
Texture2D jigglypuffBackTexture;

Texture2D pidgeyFrontTexture;
Texture2D pidgeyBackTexture;

Texture2D pikachuFrontTexture;
Texture2D pikachuBackTexture;

Texture2D psyduckFrontTexture;
Texture2D psyduckBackTexture;

Texture2D rattataFrontTexture;
Texture2D rattataBackTexture;

std::vector<Pokemon> allPokemons;

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

void LoadPokemonDatas()
{
    bulbasaurFrontTexture = LoadTexture("Images/bulbasaur.png");
    bulbasaurBackTexture = LoadTexture("Images/bulbasaurBack.png");

    squirtleFrontTexture = LoadTexture("Images/squirtle.png");
    squirtleBackTexture = LoadTexture("Images/squirtleBack.png");

    charmanderFrontTexture = LoadTexture("Images/charmander.png");
    charmanderBackTexture = LoadTexture("Images/charmanderBack.png");

    abraFrontTexture = LoadTexture("Images/abra.png");
    abraBackTexture = LoadTexture("Images/abraBack.png");

    caterpieFrontTexture = LoadTexture("Images/caterpie.png");
    caterpieBackTexture = LoadTexture("Images/caterpieBack.png");

    geodudeFrontTexture = LoadTexture("Images/geodude.png");
    geodudeBackTexture = LoadTexture("Images/geodudeBack.png");

    jigglypuffFrontTexture = LoadTexture("Images/jigglypuff.png");
    jigglypuffBackTexture = LoadTexture("Images/jigglypuffBack.png");

    pidgeyFrontTexture = LoadTexture("Images/pidgey.png");
    pidgeyBackTexture = LoadTexture("Images/pidgeyBack.png");

    pikachuFrontTexture = LoadTexture("Images/pikachu.png");
    pikachuBackTexture = LoadTexture("Images/pikachuBack.png");

    psyduckFrontTexture = LoadTexture("Images/psyduck.png");
    psyduckBackTexture = LoadTexture("Images/psyduckBack.png");

    rattataFrontTexture = LoadTexture("Images/rattata.png");
    rattataBackTexture = LoadTexture("Images/rattataBack.png");

    allPokemons = {
    Pokemon("Bulbasaur", PokeType::GRASS, 1, "Bulbasaur has a strange seed planted on its back. It grows with him since birth.", 100, bulbasaurFrontTexture, bulbasaurBackTexture),
    Pokemon("Squirtle", PokeType::WATER, 1, "It retreats into its shell and retaliates by splashing the enemy at the first opportunity.", 100, squirtleFrontTexture, squirtleBackTexture),
    Pokemon("Charmander", PokeType::FIRE, 1, "The flame on its tail represents Charmander's life energy. When it's vigorous, it burns stronger.", 100, charmanderFrontTexture, charmanderBackTexture),
    Pokemon("Abra", PokeType::PSYSCHIC, 1, "It sleeps 18 hours a day. It can use many psychic powers, even while asleep.", 100, abraFrontTexture, abraBackTexture),
    Pokemon("Caterpie", PokeType::BUG, 1, "To protect itself, it emits a foul odor from its antennae, which repels its bold enemies.", 100, caterpieFrontTexture, caterpieBackTexture),
    Pokemon("Geodude", PokeType::ROCK, 1, "It lives in plains or mountains. It is often mistaken for a small pebble.", 100, geodudeFrontTexture, geodudeBackTexture),
    Pokemon("Jigglypuff", PokeType::FAIRY, 1, "It hypnotizes its enemies with its big eyes before plunging them into a deep sleep by singing a sweet lullaby.", 100, jigglypuffFrontTexture, jigglypuffBackTexture),
    Pokemon("Pidgey", PokeType::NORMAL, 1, "It is often seen in forests. With its wings, it stirs up the air close to the ground to throw sand.", 100, pidgeyFrontTexture, pidgeyBackTexture),
    Pokemon("Pikachu", PokeType::ELECTRIC, 1, "It raises its tail to monitor its surroundings. It often attracts lightning in this position.", 100, pikachuFrontTexture, pikachuBackTexture),
    Pokemon("Psyduck", PokeType::WATER, 1, "This Pokémon constantly has a headache. When the pain becomes unbearable, it starts using its psychic powers.", 100, psyduckFrontTexture, psyduckBackTexture),
    Pokemon("Rattata", PokeType::NORMAL, 1, "Living wherever food is found, this scavenger spends its days searching for it.", 100, rattataFrontTexture, rattataBackTexture),
    };
}

void UnloadPokemonDatas()
{
    UnloadTexture(bulbasaurFrontTexture);
    UnloadTexture(bulbasaurBackTexture);

    UnloadTexture(squirtleFrontTexture);
    UnloadTexture(squirtleBackTexture);

    UnloadTexture(charmanderFrontTexture);
    UnloadTexture(charmanderBackTexture);

    UnloadTexture(abraFrontTexture);
    UnloadTexture(abraBackTexture);

    UnloadTexture(caterpieFrontTexture);
    UnloadTexture(caterpieBackTexture);

    UnloadTexture(geodudeFrontTexture);
    UnloadTexture(geodudeBackTexture);

    UnloadTexture(jigglypuffFrontTexture);
    UnloadTexture(jigglypuffBackTexture);

    UnloadTexture(pidgeyFrontTexture);
    UnloadTexture(pidgeyBackTexture);

    UnloadTexture(pikachuFrontTexture);
    UnloadTexture(pikachuBackTexture);

    UnloadTexture(psyduckFrontTexture);
    UnloadTexture(psyduckBackTexture);

    UnloadTexture(rattataFrontTexture);
    UnloadTexture(rattataBackTexture);
}

Pokemon GetPokemon(int pokemonIndex) {
    return allPokemons[pokemonIndex];
}

float GetResistance(int attackType, int defenderType) {
    return resistanceMatrix[attackType][defenderType];
}