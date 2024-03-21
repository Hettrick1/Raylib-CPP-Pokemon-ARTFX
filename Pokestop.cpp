#include "Pokestop.h"

bool justEntered, quitPokestop, showAbilities;

bool mouseOnQuitPokestop, mouseOnHeal, mouseOnLearnAbility;

int pokestopIndex = 0;

Color abilityBtnColor = WHITE;

Rectangle quitPokestopRectangle = { 600, 400, 150, 50 };
Rectangle healPokemonRectangle = { 450, 130, 300, 50 } ;
Rectangle learnAbilityRectangle = { 50, 130, 300, 50 };

std::vector<Rectangle> pokemonBtn = { {50 , 180, 180, 48}, {50 , 228, 180, 48}, {50 , 276, 180, 48}, {50 , 324, 180, 48}, {50 , 372, 180, 48}, {50 , 420, 180, 48} };

Pokestop::Pokestop()
{
}

Pokestop::~Pokestop()
{
}

void Pokestop::Update(Trainers& player)
{
	if (justEntered) {
		justEntered = false;
		quitPokestop = false;
		showAbilities = false;
		abilityBtnColor = WHITE;
		pokestopIndex = 0;
		Pokemon poke = GetPokemon(6);
		player.AddPokemon(poke);
	}
	if (!quitPokestop) {

		if (CheckCollisionPointRec(GetMousePosition(), quitPokestopRectangle)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnQuitPokestop = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				QuitPokestop();
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), healPokemonRectangle)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnHeal = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				for (Pokemon& pokemon : player.GetTeam()) {
					pokemon.Rest();
				}
			}
		}
		if (CheckCollisionPointRec(GetMousePosition(), learnAbilityRectangle)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnLearnAbility = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (!showAbilities) {
					abilityBtnColor = GRAY;
					showAbilities = true;
				}
				else if (showAbilities) {
					abilityBtnColor = WHITE;
					showAbilities = false;
				}
			}
		}
		if (!mouseOnQuitPokestop && !mouseOnHeal && !mouseOnLearnAbility) {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}
		else
		{
			mouseOnQuitPokestop = false;
			mouseOnHeal = false;
			mouseOnLearnAbility = false;
		}
		if (showAbilities) {
			int pokeNumber = player.GetTeam().size();
			for ()
		}
	}
}

void Pokestop::Draw(Trainers& player)
{
	if (!quitPokestop) {
		DrawText("Welcome in the Pokestop, trainer !", 400 - MeasureText("Welcome in the Pokestop, trainer !", 40) / 2, 50, 40, BLACK);
		DrawRectangleLines(600, 400, 150, 50, DARKBLUE);
		DrawText("Return", 600 + (150 - MeasureText("Return", 30)) / 2, 410, 30, BLACK);
		DrawRectangle(50, 130, 300, 50, abilityBtnColor);
		DrawRectangleLines(50, 130, 300, 50, DARKBLUE);
		DrawText("Learn Ability", 50 + (300 - MeasureText("Learn Ability", 30)) / 2, 140, 30, BLACK);
		DrawRectangleLines(450, 130, 300, 50, DARKBLUE);
		DrawText("Heal Pokemons", 450 + (300 - MeasureText("Heal Pokemons", 30)) / 2, 140, 30, BLACK);
		if (showAbilities) {
			int pokeNumber = player.GetTeam().size();
			for (int i = 0; i < pokeNumber; i++) {
				DrawRectangleLines(pokemonBtn[i].x, pokemonBtn[i].y, pokemonBtn[i].width, pokemonBtn[i].height, DARKBLUE);
				DrawTextureEx(player.GetTeam()[i].GetFrontSprite(), Vector2{ pokemonBtn[i].x, pokemonBtn[i].y}, 0, 0.75, WHITE);
				DrawText(player.GetTeam()[i].GetName().c_str(), pokemonBtn[i].x + 110 - MeasureText(player.GetTeam()[i].GetName().c_str(), 20)/2, pokemonBtn[i].y + 15, 20, BLACK);
			}
		}
	}
}

void Pokestop::EnterPokestop(Trainers& player)
{
	justEntered = true;
}

void Pokestop::QuitPokestop()
{
	if (!justEntered) {
		abilityBtnColor = WHITE;
		showAbilities = false;
		quitPokestop = true;
	}
}



bool Pokestop::GetQuitPokestop()
{
	return quitPokestop;
}
