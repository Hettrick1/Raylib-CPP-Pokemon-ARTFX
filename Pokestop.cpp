#include "Pokestop.h"

bool justEntered, quitPokestop, showAbilities, showHealBtn = true;

bool mouseOnQuitPokestop, mouseOnHeal, mouseOnLearnAbility, hasClickedOnPokemon, hasClickedOnAbility, showValidationBtn, mouseOnValidate, mouseOnRefuse, error;

int pokestopIndex = 0, buttonPokemonIndexRef = 0, buttonAbilityIndexRef = 0;

Color chooseAbilityBtnColor = WHITE;

Rectangle quitPokestopRectangle = { 600, 400, 150, 50 };
Rectangle healPokemonRectangle = { 450, 130, 300, 50 } ;
Rectangle learnAbilityRectangle = { 50, 130, 300, 50 };
Rectangle acceptBtn = { 550, 250, 50, 50};
Rectangle refuseBtn = { 650, 250, 50, 50};

std::vector<Rectangle> pokemonBtn = { {50 , 180, 180, 48}, {50 , 228, 180, 48}, {50 , 276, 180, 48}, {50 , 324, 180, 48}, {50 , 372, 180, 48}, {50 , 420, 180, 48} };
std::vector<Rectangle> abilityBtn = { {230 , 180, 120, 48}, {230 , 228, 120, 48}, {230 , 276, 120, 48}, {230 , 324, 120, 48}, {230 , 372, 120, 48}, {230 , 420, 120, 48}, {350 , 180, 120, 48}, {350 , 228, 120, 48}, {350 , 276, 120, 48} };
std::vector<Color> pokemonBtnColor = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };
std::vector<Color> abilityBtnColor = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };
std::vector<Abilities> abilitiesAvailable;

std::vector<bool> pokeBtn = {false, false, false, false, false, false};
std::vector<bool> abiBtn = {false, false, false, false, false, false, false, false, false};

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
		chooseAbilityBtnColor = WHITE;
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
		if (CheckCollisionPointRec(GetMousePosition(), healPokemonRectangle) && showHealBtn) {
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
					chooseAbilityBtnColor = GRAY;
					showAbilities = true;
					showHealBtn = false;
				}
				else if (showAbilities) {
					chooseAbilityBtnColor = WHITE;
					showAbilities = false;
					hasClickedOnPokemon = false;
					pokemonBtnColor[buttonPokemonIndexRef] = WHITE;
					error = false;
					showValidationBtn = false;
					showHealBtn = true;
				}
			}
		}
		if (!mouseOnQuitPokestop && !mouseOnHeal && !mouseOnLearnAbility && ResetPokemonMouseCursor() && ResetAbilityMouseCursor() && !mouseOnValidate && ! mouseOnRefuse) {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}
		if (showValidationBtn) {
			if (CheckCollisionPointRec(GetMousePosition(), acceptBtn)) {
				mouseOnValidate = true;
				SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					OnButtonClickAccept(player);
				}
			}
			if (CheckCollisionPointRec(GetMousePosition(), refuseBtn)) {
				mouseOnRefuse = true;
				SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					OnButtonClickRefuse(player);
				}
			}
		}
		else
		{
			mouseOnQuitPokestop = false;
			mouseOnHeal = false;
			mouseOnLearnAbility = false;
			mouseOnValidate = false;
			mouseOnRefuse = false;
		}
		if (showAbilities) {
			int pokeNumber = player.GetTeam().size();
			for (int i = 0; i < pokeNumber; i++) {
				if (CheckCollisionPointRec(GetMousePosition(), pokemonBtn[i])) {
					SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
					pokeBtn[i] = true;
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						OnButtonClickPokemon(i, player);
					}
				}
				else if (!CheckCollisionPointRec(GetMousePosition(), pokemonBtn[i])){
					pokeBtn[i] = false;
				}
			}
			if (hasClickedOnPokemon) {
				int abiNumber = abilitiesAvailable.size();
				for (int i = 0; i < abiNumber; i++) {
					if (CheckCollisionPointRec(GetMousePosition(), abilityBtn[i])) {
						SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
						abiBtn[i] = true;
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							OnButtonClickAbility(i, player);
						}
					}
					else if (!CheckCollisionPointRec(GetMousePosition(), abilityBtn[i])) {
						abiBtn[i] = false;
					}
				}
			}
		}
	}
}

void Pokestop::Draw(Trainers& player)
{
	if (!quitPokestop) {
		DrawText(TextFormat("%i", player.GetMoney()), 600 - 50 - MeasureText(TextFormat("%i", player.GetMoney()), 30), 410, 30, ORANGE);
		DrawText("Welcome in the Pokestop, trainer !", 400 - MeasureText("Welcome in the Pokestop, trainer !", 40) / 2, 50, 40, BLACK);
		DrawRectangleLines(600, 400, 150, 50, DARKBLUE);
		DrawText("Return", 600 + (150 - MeasureText("Return", 30)) / 2, 410, 30, BLACK);
		DrawRectangle(50, 130, 300, 50, chooseAbilityBtnColor);
		DrawRectangleLines(50, 130, 300, 50, DARKBLUE);
		DrawText("Learn Ability", 50 + (300 - MeasureText("Learn Ability", 30)) / 2, 140, 30, BLACK);
		if (showHealBtn) {
			DrawRectangleLines(450, 130, 300, 50, DARKBLUE);
			DrawText("Heal Pokemons", 450 + (300 - MeasureText("Heal Pokemons", 30)) / 2, 140, 30, BLACK);
		}
		if (showAbilities) {
			int pokeNumber = player.GetTeam().size();
			int abilityNumber = abilitiesAvailable.size();
			if (hasClickedOnPokemon) {
				for (int i = 0; i < pokeNumber; i++) {
					if (i != buttonPokemonIndexRef) {
						pokemonBtnColor[i] = WHITE;
					}
					else
					{
						pokemonBtnColor[buttonPokemonIndexRef] = GRAY;
					}
				}
				if (hasClickedOnAbility) {
					hasClickedOnAbility = false;
					for (int i = 0; i < abilityNumber; i++) {
						if (i != buttonAbilityIndexRef) {
							abilityBtnColor[i] = WHITE;
						}
						else
						{
							abilityBtnColor[buttonAbilityIndexRef] = GRAY;
						}
					}
				}
				for (int i = 0; i < abilityNumber; i++) {
					DrawRectangle(abilityBtn[i].x, abilityBtn[i].y, abilityBtn[i].width, abilityBtn[i].height, abilityBtnColor[i]);
					DrawRectangleLines(abilityBtn[i].x, abilityBtn[i].y, abilityBtn[i].width, abilityBtn[i].height, DARKBLUE);
					DrawText(abilitiesAvailable[i].GetAbilityName().c_str(), abilityBtn[i].x + 60 - MeasureText(abilitiesAvailable[i].GetAbilityName().c_str(), 20) / 2, abilityBtn[i].y + 15, 20, BLACK);
				}
			}
			for (int i = 0; i < pokeNumber; i++) {
				DrawRectangle(pokemonBtn[i].x, pokemonBtn[i].y, pokemonBtn[i].width, pokemonBtn[i].height, pokemonBtnColor[i]);
				DrawRectangleLines(pokemonBtn[i].x, pokemonBtn[i].y, pokemonBtn[i].width, pokemonBtn[i].height, DARKBLUE);
				DrawTextureEx(player.GetTeam()[i].GetFrontSprite(), Vector2{ pokemonBtn[i].x, pokemonBtn[i].y}, 0, 0.75, WHITE);
				DrawText(player.GetTeam()[i].GetName().c_str(), pokemonBtn[i].x + 110 - MeasureText(player.GetTeam()[i].GetName().c_str(), 20)/2, pokemonBtn[i].y + 15, 20, BLACK);
				DrawText(TextFormat("%i/4", player.GetTeam()[i].GetAbilities().size()), pokemonBtn[i].x - 5 - MeasureText(TextFormat("%i/4", player.GetTeam()[i].GetAbilities().size()), 20), pokemonBtn[i].y + 15, 20, RED);
			}
		}
		if (showValidationBtn) {
			
			DrawText(TextFormat("Spend %i gold?", abilitiesAvailable[buttonAbilityIndexRef].GetPrice()), 625 - MeasureText(TextFormat("Spend %i gold?", abilitiesAvailable[buttonAbilityIndexRef].GetPrice()), 30) / 2, 200, 30, BLACK);
			DrawRectangleLines(acceptBtn.x, acceptBtn.y, acceptBtn.width, acceptBtn.height, GREEN);
			DrawText("Y", acceptBtn.x + (acceptBtn.width - MeasureText("Y", 40)) / 2, acceptBtn.y + 10, 40, GREEN);
			DrawRectangleLines(refuseBtn.x, refuseBtn.y, refuseBtn.width, refuseBtn.height, RED);
			DrawText("N", refuseBtn.x + (refuseBtn.width - MeasureText("N", 40)) / 2, refuseBtn.y + 10, 40, RED);
		}
		if(error && showAbilities) {
			DrawText("You can't do that", 625 - MeasureText("You can't do that", 30) / 2, 200, 30, RED);
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
		chooseAbilityBtnColor = WHITE;
		showAbilities = false;
		hasClickedOnPokemon = false;
		pokemonBtnColor[buttonPokemonIndexRef] = WHITE;
		showValidationBtn = false;
		error = false;
		quitPokestop = true;
	}
}

bool Pokestop::GetQuitPokestop()
{
	return quitPokestop;
}

bool Pokestop::ResetPokemonMouseCursor()
{
	for (bool i : pokeBtn) {
		if (i == true) {
			return false;
		}
	}
	return true;
}
bool Pokestop::ResetAbilityMouseCursor()
{
	for (bool i : abiBtn) {
		if (i == true) {
			return false;
		}
	}
	return true;
}

void Pokestop::OnButtonClickPokemon(int buttonIndex, Trainers& player) {
	hasClickedOnPokemon = true;
	showValidationBtn = false;
	error = false;
	buttonAbilityIndexRef = 0;
	buttonPokemonIndexRef = buttonIndex;
	abilitiesAvailable.clear();
	for (int i = 0; i < 9; i++) {
		bool found = false;
		for (Abilities ability : player.GetTeam()[buttonIndex].GetAbilities()) {
			if (ability.GetAbilityName() == GetAbility(i).GetAbilityName()) {
				found = true;
				break;
			}
		}
		if (!found) {
			abilitiesAvailable.push_back(GetAbility(i));
		}
	}
	int abilityNumber = abilitiesAvailable.size();
	for (int i = 0; i < abilityNumber; i++) {
		abilityBtnColor[i] = WHITE;
	}
}
void Pokestop::OnButtonClickAbility(int buttonIndex, Trainers& player) {
	hasClickedOnAbility = true;
	buttonAbilityIndexRef = buttonIndex;
	showValidationBtn = true;
}
void Pokestop::OnButtonClickAccept(Trainers& player)
{
	if (player.GetMoney() >= abilitiesAvailable[buttonAbilityIndexRef].GetPrice() && player.GetTeam()[buttonPokemonIndexRef].GetAbilities().size() < 4) {
		player.EarnMoney(-abilitiesAvailable[buttonAbilityIndexRef].GetPrice());
		player.GetTeam()[buttonPokemonIndexRef].LearnAbilities(abilitiesAvailable[buttonAbilityIndexRef]);
		hasClickedOnPokemon = false;
		pokemonBtnColor[buttonPokemonIndexRef] = WHITE;
	}
	else {
		error = true;
		hasClickedOnPokemon = false;
		pokemonBtnColor[buttonPokemonIndexRef] = WHITE;
	}
	showValidationBtn = false;
}
void Pokestop::OnButtonClickRefuse(Trainers& player)
{
	hasClickedOnPokemon = false;
	pokemonBtnColor[buttonPokemonIndexRef] = WHITE;
	showValidationBtn = false;
	error = false;
}
