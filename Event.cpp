#include "Event.h"

Rectangle highGrassRectangle = {50, 150, 220, 300};
Rectangle lakeShoresRectangle = {290, 150, 220, 300};
Rectangle pokestopRectangle = { 530, 150, 220, 300};

Battle battle = Battle();

bool mouseOnHighGrass, mouseOnLakeShore, mouseOnPokestop;

bool isChoosingEvent, justStarted, isInFight;

Event::Event()
{

}

Event::~Event()
{

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
	if (isChoosingEvent && !isInFight)
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
	if (isInFight && !isChoosingEvent) {
		battle.Update();
		if (battle.GetQuitBattle()) {
			isInFight = false;
		}
	}
}

void Event::Draw()
{
	if (isChoosingEvent && !isInFight)
	{
		DrawText("Where do you want to go ?", 400-(MeasureText("Where do you want to go ?", 30)/2), 50, 30, BLACK);
		DrawRectangleLines(50, 150, 220, 300, DARKBLUE);
		DrawText("High Grass", 50 + (220 - MeasureText("High Grass", 30))/2, 200, 30, BLACK);
		DrawRectangleLines(290, 150, 220, 300, DARKBLUE);
		DrawText("Lake Shores", 290 + (220 - MeasureText("Lake Shores", 30))/2, 200, 30, BLACK);
		DrawRectangleLines(530, 150, 220, 300, DARKBLUE);
		DrawText("Pokestop", 530 + (220 - MeasureText("Pokestop", 30))/2, 200, 30, BLACK);
	}
	if (isInFight && !isChoosingEvent) {
		battle.Draw();
	}
}

void Event::Unload()
{
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

}

void Event::HighGrass(Trainers& player)
{
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
		if (wildPokemon.GetType() == PokeType::GRASS) {
			battle.FightWildPokemon(player, wildPokemon);
			isInFight = true;
		}
		else {
			int randomNumber = ChooseInt(0, 100);
			if (randomNumber >= 100) {
				battle.FightWildPokemon(player, wildPokemon);
				isInFight = true;
			}
			else {
				isChoosingEvent = true;
				mouseOnPokestop = false;
				mouseOnHighGrass = false;
				mouseOnLakeShore = false;
			}
		}
	}
}

void Event::LakeShores(Trainers& player)
{
}

