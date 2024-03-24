#include "Event.h"

Rectangle highGrassRectangle = { 680, 180, 220, 300};
Rectangle lakeShoresRectangle = {430, 180, 220, 300};
Rectangle pokestopRectangle = { 180, 180, 220, 300 };

Battle battle = Battle();
Pokestop pokestop = Pokestop();

bool mouseOnHighGrass, mouseOnLakeShore, mouseOnPokestop;

bool isChoosingEvent, justStarted, isInFight, isInPokestop, isInHighGrass, isInLakeShores;

Texture2D pokeball;
Texture2D gold;
Texture2D battleBackGroundGrass;
Texture2D battleBackGroundWater;
Texture2D enemyPokemonInfos;
Texture2D playerPokemonInfos;


Event::Event()
{

}

Event::~Event()
{

}

void Event::Load()
{
	pokeball = LoadTexture("Images/poke-ball.png");
	gold = LoadTexture("Images/coin.png");
	battleBackGroundGrass = LoadTexture("Images/BattleBackgroundGrass.png");
	battleBackGroundWater = LoadTexture("Images/BattleBackgroundWater.png");
	enemyPokemonInfos = LoadTexture("Images/EnemyPokemonInfos.png");
	playerPokemonInfos = LoadTexture("Images/PlayerPokemonInfos.png");
}

void Event::Start()
{
	isChoosingEvent = true;
}

void Event::Update(Trainers& player)
{
	if (!justStarted) {
		justStarted = true;
	}
	if (isChoosingEvent && !isInFight && !isInPokestop)
	{
		if (CheckCollisionPointRec(GetMousePosition(), highGrassRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnHighGrass = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				isChoosingEvent = false;
				HighGrass(player);
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), lakeShoresRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnLakeShore = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				isChoosingEvent = false;
				LakeShores(player);
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), pokestopRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnPokestop = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				isChoosingEvent = false;
				Pokestop(player);
			}
		}
		if (!mouseOnPokestop && ! mouseOnHighGrass && !mouseOnLakeShore)
		{
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}
		else
		{
			mouseOnPokestop = false;
			mouseOnHighGrass = false;
			mouseOnLakeShore = false;
		}
	}
	if (isInFight && !isChoosingEvent && !isInPokestop) {
		if (isInHighGrass) {
			battle.Update(player, true);
		}
		else {
			battle.Update(player, false);
		}
		if (battle.GetQuitBattle()) {
			isInFight = false;
			isInHighGrass = false;
			isInLakeShores = false;
			isChoosingEvent = true;
		}
	}
	if (!isInFight && !isChoosingEvent && isInPokestop) {
		pokestop.Update(player);
		if (pokestop.GetQuitPokestop()) {
			isInPokestop = false;
			isChoosingEvent = true;
		}
	}
}

void Event::Draw(Trainers& player)
{
	if (isChoosingEvent && !isInFight)
	{
		DrawText("Where do you want to go ?", 540-(MeasureText("Where do you want to go ?", 40)/2), 100, 40, BLACK);
		DrawRectangleLines(pokestopRectangle.x, pokestopRectangle.y, pokestopRectangle.width, pokestopRectangle.height, DARKBLUE);
		DrawText("Pokestop", pokestopRectangle.x + (pokestopRectangle.width - MeasureText("Pokestop", 30))/2, 200, 30, BLACK);
		DrawRectangleLines(lakeShoresRectangle.x, lakeShoresRectangle.y, lakeShoresRectangle.width, lakeShoresRectangle.height, DARKBLUE);
		DrawText("Lake Shores", lakeShoresRectangle.x + (lakeShoresRectangle.width - MeasureText("Lake Shores", 30))/2, 200, 30, BLACK);
		DrawRectangleLines(highGrassRectangle.x, highGrassRectangle.y, highGrassRectangle.width, highGrassRectangle.height, DARKBLUE);
		DrawText("High Grass", highGrassRectangle.x + (highGrassRectangle.width - MeasureText("High Grass", 30))/2, 200, 30, BLACK);
	}
	if (isInFight && !isChoosingEvent) {
		if (isInHighGrass) {
			battle.Draw(player, true, battleBackGroundGrass, pokeball, gold, enemyPokemonInfos, playerPokemonInfos);
		}
		else {
			battle.Draw(player, false, battleBackGroundWater, pokeball, gold, enemyPokemonInfos, playerPokemonInfos);
		}
	}
	if (!isInFight && !isChoosingEvent && isInPokestop) {
		pokestop.Draw(player, pokeball, gold);
	}
}

void Event::Unload()
{
	UnloadTexture(pokeball);
	UnloadTexture(gold);
	UnloadTexture(battleBackGroundGrass);
	UnloadTexture(battleBackGroundWater);
	UnloadTexture(enemyPokemonInfos);
	UnloadTexture(playerPokemonInfos);
}

int Event::ChooseInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}

void Event::Pokestop(Trainers& player)
{
	mouseOnPokestop = false;
	mouseOnHighGrass = false;
	mouseOnLakeShore = false;
	isInPokestop = true;
	pokestop.EnterPokestop(player);
}

void Event::HighGrass(Trainers& player)
{
	mouseOnPokestop = false;
	mouseOnHighGrass = false;
	mouseOnLakeShore = false;
	isInFight = true;
	isInHighGrass = true;
	battle.EnterBattle();
}

void Event::LakeShores(Trainers& player)
{
	mouseOnPokestop = false;
	mouseOnHighGrass = false;
	mouseOnLakeShore = false;
	isInFight = true;
	isInHighGrass = false;
	battle.EnterBattle();
}

