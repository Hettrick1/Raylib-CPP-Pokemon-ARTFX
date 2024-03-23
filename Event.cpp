#include "Event.h"

Rectangle highGrassRectangle = { 680, 180, 220, 300};
Rectangle lakeShoresRectangle = {430, 180, 220, 300};
Rectangle pokestopRectangle = { 180, 180, 220, 300 };

Battle battle = Battle();
Pokestop pokestop = Pokestop();

bool mouseOnHighGrass, mouseOnLakeShore, mouseOnPokestop;

bool isChoosingEvent, justStarted, isInFight, isInPokestop;

Texture2D pokeball;
Texture2D gold;

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
		battle.Update();
		if (battle.GetQuitBattle()) {
			isInFight = false;
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
		battle.Draw();
	}
	if (!isInFight && !isChoosingEvent && isInPokestop) {
		pokestop.Draw(player, pokeball, gold);
	}
}

void Event::Unload()
{
	UnloadTexture(pokeball);
	UnloadTexture(gold);
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
	int randomNumber = ChooseInt(0, 100);
	if(randomNumber > 90)
	{
		int randomIndex = ChooseInt(0, 5);
		battle.FightTrainer(player, GetTrainer(randomIndex));
	}
	else
	{
		int randomIndex = ChooseInt(0, 10);
		Pokemon wildPokemon = GetPokemon(randomIndex);
		battle.FightWildPokemon(player, wildPokemon);
	}
}

void Event::LakeShores(Trainers& player)
{
	mouseOnPokestop = false;
	mouseOnHighGrass = false;
	mouseOnLakeShore = false;
	isInFight = true;
	int randomNumber = ChooseInt(0, 100);
	if (randomNumber > 50)
	{
		int randomIndex = ChooseInt(0, 5);
		battle.FightTrainer(player, GetTrainer(randomIndex));
	}
	else
	{
		int randomIndex = ChooseInt(0, 10);
		Pokemon wildPokemon = GetPokemon(randomIndex);
		battle.FightWildPokemon(player, wildPokemon);
	}
}

