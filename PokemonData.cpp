#include "PokemonData.h"
#include "Pokemon.h"

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
std::vector<Trainers> allTrainers = {
        Trainers("w", "q", "q", 100, 100, 0),
        Trainers("r", "w", "w", 200, 100, 5),
        Trainers("t", "e", "e", 300, 100, 4),
        Trainers("z", "r", "r", 100, 100, 8),
        Trainers("u", "t", "t", 200, 100, 10),
        Trainers("i", "z", "z", 300, 100, 5),
};
std::vector<Abilities> allAbilities = {
        Abilities("Ability1", 10, 15, 35, PokeType::ELECTRIC),
        Abilities("Ability2", 15, 20, 35, PokeType::ELECTRIC),
        Abilities("Ability3", 12, 16, 35, PokeType::ELECTRIC),
        Abilities("Ability4", 14, 18, 35, PokeType::ELECTRIC),
        Abilities("Ability5", 8, 18, 35, PokeType::ELECTRIC),
        Abilities("Ability6", 10, 12, 35, PokeType::ELECTRIC),
        Abilities("Ability7", 13, 15, 35, PokeType::ELECTRIC),
        Abilities("Ability8", 10, 15, 35, PokeType::ELECTRIC),
        Abilities("Ability9", 7, 16, 35, PokeType::ELECTRIC),
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
        Pokemon("Bulbasaur", PokeType::GRASS, 1,
                "Bulbasaur has a strange seed planted on its back. It grows with him since birth.", 100,
                bulbasaurFrontTexture, bulbasaurBackTexture, allAbilities[0]),
        Pokemon("Squirtle", PokeType::WATER, 1,
                "It retreats into its shell and retaliates by splashing the enemy at the first opportunity.", 100,
                squirtleFrontTexture, squirtleBackTexture, allAbilities[0]),
        Pokemon("Charmander", PokeType::FIRE, 1,
                "The flame on its tail represents Charmander's life energy. When it's vigorous, it burns stronger.",
                100, charmanderFrontTexture, charmanderBackTexture, allAbilities[0]),
        Pokemon("Abra", PokeType::PSYSCHIC, 1,
                "It sleeps 18 hours a day. It can use many psychic powers, even while asleep.", 100, abraFrontTexture,
                abraBackTexture, allAbilities[0]),
        Pokemon("Caterpie", PokeType::BUG, 1,
                "To protect itself, it emits a foul odor from its antennae, which repels its bold enemies.", 100,
                caterpieFrontTexture, caterpieBackTexture, allAbilities[0]),
        Pokemon("Geodude", PokeType::ROCK, 1,
                "It lives in plains or mountains. It is often mistaken for a small pebble.", 100, geodudeFrontTexture,
                geodudeBackTexture, allAbilities[0]),
        Pokemon("Jigglypuff", PokeType::FAIRY, 1,
                "It hypnotizes its enemies with its big eyes before plunging them into a deep sleep by singing a sweet lullaby.",
                100, jigglypuffFrontTexture, jigglypuffBackTexture, allAbilities[0]),
        Pokemon("Pidgey", PokeType::NORMAL, 1,
                "It is often seen in forests. With its wings, it stirs up the air close to the ground to throw sand.",
                100, pidgeyFrontTexture, pidgeyBackTexture, allAbilities[0]),
        Pokemon("Pikachu", PokeType::ELECTRIC, 1,
                "It raises its tail to monitor its surroundings. It often attracts lightning in this position.", 100,
                pikachuFrontTexture, pikachuBackTexture, allAbilities[0]),
        Pokemon("Psyduck", PokeType::WATER, 1,
                "This Pokémon constantly has a headache. When the pain becomes unbearable, it starts using its psychic powers.",
                100, psyduckFrontTexture, psyduckBackTexture, allAbilities[0]),
        Pokemon("Rattata", PokeType::NORMAL, 1,
                "Living wherever food is found, this scavenger spends its days searching for it.", 100,
                rattataFrontTexture, rattataBackTexture, allAbilities[0]),
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

Pokemon GetPokemon(int pokemonIndex)
{
    return allPokemons[pokemonIndex];
}

Trainers& GetTrainer(int trainerIndex)
{
    return allTrainers[trainerIndex];
}
Abilities GetAbility(int abilityIndex)
{
    return allAbilities[abilityIndex];
}

float GetResistance(int attackType, int defenderType)
{
    return resistanceMatrix[attackType][defenderType];
}

// this code allows me to make auto breaks line when I draw a text (function that does not exist directly in raylib)
// it comes from a raylib example (Rectangle bounds) contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)

void DrawTextBoxed(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap,
                             Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text); // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0; // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f; // Offset X to next character to draw

    float scaleFactor = fontSize / static_cast<float>(font.baseSize); // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1; // Index where to begin drawing (where a line begins)
    int endLine = -1; // Index where to stop drawing (where a line ends)
    int lastk = -1; // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0)
                             ? font.recs[index].width * scaleFactor
                             : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        if (state == MEASURE_STATE)
        {
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec(Rectangle{
                                         rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth,
                                         font.baseSize * scaleFactor
                                     }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, Vector2{rec.x + textOffsetX, rec.y + textOffsetY}, fontSize,
                                      isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth; // avoid leading spaces
    }
}
