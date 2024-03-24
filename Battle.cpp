#include "Battle.h"


bool justEnteredBattle, chooseOpponent, againstTrainer, againstPokemon, hasBattleLoaded;

int randomNumber;
int randomIndex;
int timer = 0;

Rectangle infosTextBox = { 397, 554, 350, 120 };

std::vector<Rectangle> abilityButtons = { {230,430, 155, 45}, {230, 475, 155, 45}, {385,430, 155, 45}, {385, 475, 155, 45} };

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
}

void Battle::Draw(Trainers& player, bool isInHighGrass, Texture2D& battleBackGround, Texture2D& pokeball, Texture2D& gold, Texture2D& enemyPokemonInfos, Texture2D& playerPokemonInfos)
{
	if (againstPokemon) {
		if (timer <= 180) {
			timer += 1;
			DrawText(TextFormat("Un %s sauvage apparait", opponentPokemon.GetName().c_str()), 540 - MeasureText(TextFormat("Un %s sauvage apparait", opponentPokemon.GetName().c_str()), 40) / 2, 180, 40, BLACK);
			DrawTextureEx(opponentPokemon.GetFrontSprite(), Vector2{ (float)530 - opponentPokemon.GetFrontSprite().width * 2, (float)200 }, 0, 5, WHITE);
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
		DrawRectangle(406, 168, 192, 12, GRAY);
		DrawRectangle(406, 168, 192, 12, enemylifeBarColor);
		DrawTextureEx(enemyPokemonInfos, Vector2{ 250, 100 }, 0, 4, WHITE);
		DrawText(opponentPokemon.GetName().c_str(), 280, 120, 30, BLACK);
		DrawRectangle(692, 368, 192, 12, GRAY);
		DrawRectangle(692, 368, 192, 12, playerlifeBarColor);
		DrawTextureEx(playerPokemonInfos, Vector2{ 500, 300 }, 0, 4, WHITE);
		DrawText(player.GetTeam()[player.GetCurrentPokemonIndex()].GetName().c_str(), 565, 320, 30, BLACK);
		DrawText(TextFormat("%i", player.GetMoney()), 605, 480, 30, ORANGE);
		DrawText(TextFormat("%i", player.GetPokeballs()), 605, 440, 30, RED);
		DrawTextureEx(pokeball, Vector2{ static_cast<float>(550),  static_cast<float>(430) }, 0, 2, WHITE);
		DrawTextureEx(gold, Vector2{ static_cast<float>(550),  static_cast<float>(470) }, 0, 2, WHITE);
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
