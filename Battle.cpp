#include "Battle.h"


bool justEnteredBattle, chooseOpponent, againstTrainer, againstPokemon, hasBattleLoaded, abilityHovered;

bool mouseOnQuitBattleButton, mouseOnChangePokemonButton, mouseOnThrowPokeballButton;

int randomNumber;
int randomIndex;
int timer = 0;
int abilityHoveredIndex = 0;

Rectangle infosTextBox = { 397, 554, 350, 120 };

Rectangle ChangePokemonBtn = { 695, 430, 155, 30 };
Rectangle ThrowPokeballBtn = { 695, 460, 155, 30 };
Rectangle QuitBattleBtn = { 695, 490, 155, 30 };

std::vector<Rectangle> abilityButtons = { {230,430, 155, 45}, {230, 475, 155, 45}, {385,430, 155, 45}, {385, 475, 155, 45} };

std::vector<Color> pokeAbilityBtnColor = { BLANK, BLANK, BLANK, BLANK };
std::vector<bool> abilityBtnBool = { false, false, false, false };

Pokemon opponentPokemon;

Battle::Battle()
{
}

Battle::~Battle()
{
}

void Battle::Update(Trainers& player, bool isInHighGrass)
{
	if (justEnteredBattle) {
		justEnteredBattle = false;
		stopBattle = false;
		hasBattleLoaded = false;
		timer = 0;
		chooseOpponent = false;
	}
	if (isInHighGrass) {
		if (!chooseOpponent) {
			randomNumber = ChooseInt(0, 100);
		}
		if (randomNumber <= 100) { // changer le nombre --> juste pour debug
			if (!chooseOpponent) {
				randomIndex = ChooseInt(0, 10);
				opponentPokemon = GetPokemon(randomIndex);
				chooseOpponent = true;
			}
			AgainstPokemon(player, opponentPokemon);		
		}
		else{

		}
	}
	else { // lakeShore -> il ne pourra trouver que certains type de pokémon mais proba de tomber contre un autre dresseur + élevée
		if (!chooseOpponent) {
			randomNumber = ChooseInt(0, 100);
		}
		if (randomNumber <= 100) { // changer le nombre --> juste pour debug
			if (!chooseOpponent) {
				randomIndex = ChooseInt(0, 10);
				opponentPokemon = GetPokemon(randomIndex);
				chooseOpponent = true;
			}
			AgainstPokemon(player, opponentPokemon);
		}
		else {

		}
	}
	if (ResetAbilityMouseCursor() && !mouseOnChangePokemonButton && !mouseOnQuitBattleButton && !mouseOnThrowPokeballButton) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		abilityHovered = false;
	}
	if (hasBattleLoaded) {
		int abiNumber = player.GetTeam()[player.GetCurrentPokemonIndex()].GetAbilities().size();
		for (int i = 0; i < abiNumber; i++) {
			if (CheckCollisionPointRec(GetMousePosition(), abilityButtons[i])) {
				SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
				OnAbilityHovered(i);
				abilityBtnBool[i] = true;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

				}
			}
			else if (!CheckCollisionPointRec(GetMousePosition(), abilityButtons[i])) {
				abilityBtnBool[i] = false;
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), QuitBattleBtn)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnQuitBattleButton = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				QuitBattle();
			}
		}
		else {
			mouseOnQuitBattleButton = false;
			mouseOnChangePokemonButton = false;
			mouseOnThrowPokeballButton = false;
		}
	}
}

void Battle::Draw(Trainers& player, bool isInHighGrass, Texture2D& battleBackGround, Texture2D& pokeball, Texture2D& gold, Texture2D& enemyPokemonInfos, Texture2D& playerPokemonInfos)
{
	if (againstPokemon) {
		if (timer <= 180) {
			timer += 1;
			DrawTypewriterTextEx(Vector2{(float) 540,(float) 180 }, 40, BLACK, 0.05, "Un %s sauvage apparait", opponentPokemon.GetName().c_str());
			DrawTextureEx(opponentPokemon.GetFrontSprite(), Vector2{ (float)540 - opponentPokemon.GetFrontSprite().width *2, (float)200 }, 0, 5, WHITE);
		}
		else {
			hasBattleLoaded = true;
		}
	}
	if (againstTrainer) {

	}
	if (hasBattleLoaded) {
		Color enemylifeBarColor;
		Color playerlifeBarColor;
		if (player.GetTeam()[player.GetCurrentPokemonIndex()].GetHealth() < (player.GetTeam()[player.GetCurrentPokemonIndex()].GetMaxHealth() * 0.75) && player.GetTeam()[player.GetCurrentPokemonIndex()].GetHealth() >= (player.GetTeam()[player.GetCurrentPokemonIndex()].GetMaxHealth() * 0.4)) {
			playerlifeBarColor = ORANGE;
		}
		else if (player.GetTeam()[player.GetCurrentPokemonIndex()].GetHealth() < (player.GetTeam()[player.GetCurrentPokemonIndex()].GetMaxHealth() * 0.4)) {
			playerlifeBarColor = RED;
		}
		else {
			playerlifeBarColor = GREEN;
		}
		if (opponentPokemon.GetHealth() < (opponentPokemon.GetMaxHealth() * 0.75) && opponentPokemon.GetHealth() >= (opponentPokemon.GetMaxHealth() * 0.4)) {
			enemylifeBarColor = ORANGE;
		}
		else if (opponentPokemon.GetHealth() < (opponentPokemon.GetMaxHealth() * 0.4)) {
			enemylifeBarColor = RED;
		}
		else {
			enemylifeBarColor = GREEN;
		}

		if (isInHighGrass) {
			ClearBackground(Color{ 206,252,186,200 });
		}
		else {
			ClearBackground(Color{ 201,255,229,200 });
		}
		DrawRectangleLinesEx(infosTextBox, 3, BLACK);
		DrawRectangleLinesEx(Rectangle{ 230, 430, 620, 90 }, 2, BLACK);
		DrawRectangle(539, 430, 2, 90, BLACK);
		DrawRectangle(385, 430, 2, 90, BLACK);
		DrawRectangle(695, 430, 2, 90, BLACK);
		DrawRectangle(230, 474, 309, 2, BLACK);
		DrawRectangle(695, 459, 155, 2, BLACK);
		DrawRectangle(695, 489, 155, 2, BLACK);
		DrawTextureEx(battleBackGround, Vector2{ 205, 110 }, 0, 2.8, WHITE);
		DrawTextureEx(player.GetTeam()[player.GetCurrentPokemonIndex()].GetBackSprite(), Vector2{ 265, 203 }, 0, 3.4, WHITE);
		DrawTextureEx(opponentPokemon.GetFrontSprite(), Vector2{ 600, 70 }, 0, 3.4, WHITE);
		DrawRectangle(386, 168, 192, 12, GRAY);
		DrawRectangle(386, 168, 192, 12, enemylifeBarColor);
		DrawTextureEx(enemyPokemonInfos, Vector2{ 230, 100 }, 0, 4, WHITE);
		DrawText(opponentPokemon.GetName().c_str(), 260, 120, 30, BLACK);
		DrawRectangle(692, 368, 192, 12, GRAY);
		DrawRectangle(692, 368, 192, 12, playerlifeBarColor);
		DrawTextureEx(playerPokemonInfos, Vector2{ 500, 300 }, 0, 4, WHITE);
		DrawText(player.GetTeam()[player.GetCurrentPokemonIndex()].GetName().c_str(), 565, 320, 30, BLACK);
		DrawText(TextFormat("%i", player.GetMoney()), 605, 480, 30, ORANGE);
		DrawText(TextFormat("%i", player.GetPokeballs()), 605, 440, 30, RED);
		DrawTextureEx(pokeball, Vector2{ static_cast<float>(550),  static_cast<float>(430) }, 0, 2, WHITE);
		DrawTextureEx(gold, Vector2{ static_cast<float>(550),  static_cast<float>(470) }, 0, 2, WHITE);
		for (int i = 0; i < player.GetTeam()[player.GetCurrentPokemonIndex()].GetAbilities().size(); i++) {
			DrawText(player.GetTeam()[player.GetCurrentPokemonIndex()].GetAbilities()[i].GetAbilityName().c_str(), abilityButtons[i].x + (155 - MeasureText(player.GetTeam()[player.GetCurrentPokemonIndex()].GetAbilities()[i].GetAbilityName().c_str(), 30)) / 2, abilityButtons[i].y + 10, 30, BLACK);
		}
		if (abilityHovered) {
			if (isInHighGrass) {
				DrawRectangle(230, 400, 309, 30, Color{ 206,252,186,220 });
			}
			else {
				DrawRectangle(230, 400, 309, 30, Color{ 201,255,229,220 });
			}
			DrawRectangle(230, 400, 2, 30, BLACK);
			DrawRectangle(230, 400, 310, 2, BLACK);
			DrawRectangle(539, 400, 2, 30, BLACK);
			Abilities& ability = player.GetTeam()[player.GetCurrentPokemonIndex()].GetAbilities()[abilityHoveredIndex];
			DrawText(TextFormat("Damages : %i - %i Uses : %i", static_cast<int>(ability.GetDamagesMin()), static_cast<int>(ability.GetDamagesMax()), ability.GetUseRemaning()), 385 - MeasureText(TextFormat("Damages : %i - %i Uses : %i", static_cast<int>(ability.GetDamagesMin()), static_cast<int>(ability.GetDamagesMax()), ability.GetUseRemaning()), 20)/2, 405, 20, BLACK);
		}
	}
}

int Battle::ChooseInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}

void Battle::AgainstPokemon(Trainers& player, Pokemon& pokemon)
{
	for (int i = 0; i < 4; i++) {
		int randomAbilityIndex = ChooseInt(0, 8);
		Abilities ability = GetAbility(randomAbilityIndex);
		pokemon.LearnAbilities(ability);
	}
	againstPokemon = true;
}

void Battle::AgainstTrainer(Trainers& player, Trainers& opponent)
{
	againstTrainer = true;
}

void Battle::OnAbilityHovered(int index)
{
	abilityHovered = true;
	abilityHoveredIndex = index;
}

void Battle::EnterBattle()
{
	justEnteredBattle = true;
}

void Battle::QuitBattle()
{
	stopBattle = true;
}

bool Battle::GetQuitBattle()
{
	return false;
}

bool Battle::GetDefeated()
{
	return false;
}

void Battle::DrawTypewriterTextEx(Vector2 position, float fontSize, Color color, float speed, const char* format, ...)
{
	static int index = 0;
	static float timer = 0.0f;
	static std::string text;
	static char formattedText[50];

	timer += GetFrameTime();

	va_list args;
	va_start(args, format);
	vsnprintf(formattedText, sizeof(formattedText), format, args);
	va_end(args);

	text = formattedText;

	if (timer >= speed)
	{
		timer = 0.0f;
		index++;

		if (index > text.length())
		{
			index = text.length();
		}
	}
	Vector2 textSize = MeasureTextEx(GetFontDefault(), text.substr(0, index).c_str(), fontSize, 1);

	float centeredX = (GetScreenWidth() - textSize.x) / 2.0f;

	DrawTextEx(GetFontDefault(), text.substr(0, index).c_str(), { centeredX, position.y }, fontSize, 1, color);
}
bool Battle::ResetAbilityMouseCursor()
{
	for (bool i : abilityBtnBool) {
		if (i == true) {
			return false;
		}
	}
	return true;
}
