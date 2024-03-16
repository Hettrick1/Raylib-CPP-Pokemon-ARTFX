#include "raylib.h"
#include "Event.h"
#include "Pokemon.h"
#include "Trainers.h"
#include "Battle.h"

Rectangle highGrassRectangle = {50, 150, 220, 300};
Rectangle lakeShoresRectangle = {290, 150, 220, 300};
Rectangle pokestopRectangle = { 530, 150, 220, 300};

bool mouseOnHighGrass, mouseOnLakeShore, mouseOnPokestop;

bool isChoosingEvent;

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

void Event::Update()
{
	if (isChoosingEvent)
	{
		if (CheckCollisionPointRec(GetMousePosition(), highGrassRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnHighGrass = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				HighGrass();
				isChoosingEvent = false;
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), lakeShoresRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnLakeShore = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				LakeShores();
				isChoosingEvent = false;
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), pokestopRectangle))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnPokestop = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				Pokestop();
				isChoosingEvent = false;
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
}

void Event::Draw()
{
	if (isChoosingEvent)
	{
		DrawText("Where do you want to go ?", 400-(MeasureText("Where do you want to go ?", 30)/2), 50, 30, BLACK);
		DrawRectangleLines(50, 150, 220, 300, BLACK);
		DrawRectangleLines(290, 150, 220, 300, BLACK);
		DrawRectangleLines(530, 150, 220, 300, BLACK);
	}
}

void Event::Unload()
{
}

void Event::Pokestop()
{
}

void Event::HighGrass()
{
}

void Event::LakeShores()
{
}

