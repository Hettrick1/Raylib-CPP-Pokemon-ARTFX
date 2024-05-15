#pragma once
#include "Trainers.h"
#include "Pokemon.h"
#include "PokemonData.h"

#include <random>
#include <vector>


class Battle
{
private :
	bool stopBattle;
	bool enemyDefeated;
public:
	Battle();
	~Battle();
	void Update(Trainers& player, bool isInHighGrass);
	void Draw(Trainers& player, bool isInHighGrass, Texture2D& battleBackGround, Texture2D& pokeball, Texture2D& gold, Texture2D& enemyPokemonInfos, Texture2D& playerPokemonInfos);
	int ChooseInt(int min, int max);
	void AgainstPokemon(Trainers& player, Pokemon& pokemon);
	void AgainstTrainer(Trainers& player, Trainers& opponent);
	void OnAbilityHovered(int index);
	void EnterBattle();
	void QuitBattle();
	bool GetQuitBattle();
	bool GetDefeated();
	void DrawTypewriterTextEx(Vector2 position, float fontSize, Color color, float speed, const char* format, ...);
	bool ResetAbilityMouseCursor();
	void OpponentTurn(Trainers& player);
};

