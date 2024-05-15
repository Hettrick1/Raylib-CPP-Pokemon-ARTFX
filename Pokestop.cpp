#include "Pokestop.h"

bool justEntered, quitPokestop, showAbilities, showHealBtn = true;

bool mouseOnQuitPokestop, mouseOnHeal, mouseOnLearnAbility, hasClickedOnPokemon, hasClickedOnAbility, showValidationBtn, mouseOnValidate, mouseOnRefuse, error;

int pokestopIndex = 0, buttonPokemonIndexRef = 0, buttonAbilityIndexRef = 0;

Color chooseAbilityBtnColor = BLANK;

Rectangle quitPokestopRectangle = { 590, 630, 150, 35 };
Rectangle healPokemonRectangle = { 580, 180, 300, 50 } ;
Rectangle learnAbilityRectangle = { 200, 130, 300, 50 };
Rectangle acceptBtn = { 465, 540, 50, 50};
Rectangle refuseBtn = { 565, 540, 50, 50};

std::vector<Rectangle> pokemonBtn = { {learnAbilityRectangle.x , 180, 180, 48}, {learnAbilityRectangle.x , 228, 180, 48}, {learnAbilityRectangle.x , 276, 180, 48}, {learnAbilityRectangle.x , 324, 180, 48}, {learnAbilityRectangle.x , 372, 180, 48}, {learnAbilityRectangle.x , 420, 180, 48} };
std::vector<Rectangle> abilityBtn = { {pokemonBtn[0].x + pokemonBtn[0].width , 180, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width  , 228, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width  , 276, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width  , 324, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width  , 372, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width  , 420, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width + 120, 180, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width + 120 , 228, 120, 48}, {pokemonBtn[0].x + pokemonBtn[0].width + 120 , 276, 120, 48}};
std::vector<Color> pokemonBtnColor = { BLANK, BLANK, BLANK, BLANK, BLANK, BLANK };
std::vector<Color> abilityBtnColor = { BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK };
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
		chooseAbilityBtnColor = BLANK;
		pokestopIndex = 0;
		/*Pokemon poke = GetPokemon(6);
		poke.TakeDamages(80);
		player.AddPokemon(poke);*/
	}
	if (!quitPokestop) {
		int pokeNumber = player.GetTeam().size();
		for (int i = 0; i < pokeNumber; i++) {
			player.GetTeam()[i].Rest(0.08f);
		}

		if (CheckCollisionPointRec(GetMousePosition(), quitPokestopRectangle)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnQuitPokestop = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				QuitPokestop();
			}
		}
		/*if (CheckCollisionPointRec(GetMousePosition(), healPokemonRectangle) && showHealBtn) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnHeal = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				for (Pokemon& pokemon : player.GetTeam()) {
					pokemon.Rest();
				}
			}
		}*/
		if (CheckCollisionPointRec(GetMousePosition(), learnAbilityRectangle)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mouseOnLearnAbility = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (!showAbilities) {
					chooseAbilityBtnColor = LIGHTGRAY;
					showAbilities = true;
					showHealBtn = false;
				}
				else if (showAbilities) {
					chooseAbilityBtnColor = BLANK;
					showAbilities = false;
					hasClickedOnPokemon = false;
					pokemonBtnColor[buttonPokemonIndexRef] = BLANK;
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

void Pokestop::Draw(Trainers& player, Texture2D& pokeball, Texture2D& coin)
{
	if (!quitPokestop) {
		DrawText(TextFormat("%i", player.GetMoney()), quitPokestopRectangle.x - 70 - MeasureText(TextFormat("%i", player.GetMoney()), 30), quitPokestopRectangle.y + 30, 30, ORANGE);
		DrawText(TextFormat("%i", player.GetPokeballs()), quitPokestopRectangle.x - 70 - MeasureText(TextFormat("%i", player.GetPokeballs()), 30), quitPokestopRectangle.y - 15, 30, RED);
		DrawTextureEx(pokeball, Vector2{ static_cast<float>(quitPokestopRectangle.x - 60),  static_cast<float>(quitPokestopRectangle.y - 25) }, 0, 2, WHITE);
		DrawTextureEx(coin, Vector2{ static_cast<float>(quitPokestopRectangle.x - 60),  static_cast<float>(quitPokestopRectangle.y + 20) }, 0, 2, WHITE);
		DrawText("Welcome in the Pokecenter", 540 - MeasureText("Welcome in the Pokecenter", 40) / 2, 70, 40, BLACK);
		DrawRectangleLines(quitPokestopRectangle.x, quitPokestopRectangle.y, quitPokestopRectangle.width, quitPokestopRectangle.height, BLACK);
		DrawText("Return", quitPokestopRectangle.x + (quitPokestopRectangle.width - MeasureText("Return", 20)) / 2, quitPokestopRectangle.y + 8, 20, BLACK);
		DrawRectangle(learnAbilityRectangle.x, learnAbilityRectangle.y, learnAbilityRectangle.width, learnAbilityRectangle.height, chooseAbilityBtnColor);
		DrawRectangleLines(learnAbilityRectangle.x, learnAbilityRectangle.y, learnAbilityRectangle.width, learnAbilityRectangle.height, BLACK);
		DrawText("Learn Ability", learnAbilityRectangle.x + (learnAbilityRectangle.width - MeasureText("Learn Ability", 30)) / 2, learnAbilityRectangle.y + 10, 30, BLACK);
		if (showAbilities) {
			int pokeNumber = player.GetTeam().size();
			int abilityNumber = abilitiesAvailable.size();
			if (hasClickedOnPokemon) {
				for (int i = 0; i < pokeNumber; i++) {
					if (i != buttonPokemonIndexRef) {
						pokemonBtnColor[i] = BLANK;
					}
					else
					{
						pokemonBtnColor[buttonPokemonIndexRef] = LIGHTGRAY;
					}
				}
				if (hasClickedOnAbility) {
					hasClickedOnAbility = false;
					for (int i = 0; i < abilityNumber; i++) {
						if (i != buttonAbilityIndexRef) {
							abilityBtnColor[i] = BLANK;
						}
						else
						{
							abilityBtnColor[buttonAbilityIndexRef] = LIGHTGRAY;
						}
					}
				}
				for (int i = 0; i < abilityNumber; i++) {
					DrawRectangle(abilityBtn[i].x, abilityBtn[i].y, abilityBtn[i].width, abilityBtn[i].height, abilityBtnColor[i]);
					DrawRectangleLines(abilityBtn[i].x, abilityBtn[i].y, abilityBtn[i].width, abilityBtn[i].height, BLACK);
					DrawText(abilitiesAvailable[i].GetAbilityName().c_str(), abilityBtn[i].x + 60 - MeasureText(abilitiesAvailable[i].GetAbilityName().c_str(), 20) / 2, abilityBtn[i].y + 15, 20, BLACK);
				}
			}
			for (int i = 0; i < pokeNumber; i++) {
				Color abilityCountColor;
				if (player.GetTeam()[i].GetAbilities().size() < 4) {
					abilityCountColor = GRAY;
				}
				else {
					abilityCountColor = RED;
				}
				DrawRectangle(pokemonBtn[i].x, pokemonBtn[i].y, pokemonBtn[i].width, pokemonBtn[i].height, pokemonBtnColor[i]);
				DrawRectangleLines(pokemonBtn[i].x, pokemonBtn[i].y, pokemonBtn[i].width, pokemonBtn[i].height, BLACK);
				DrawTextureEx(player.GetTeam()[i].GetFrontSprite(), Vector2{ pokemonBtn[i].x, pokemonBtn[i].y}, 0, 0.75, WHITE);
				DrawText(player.GetTeam()[i].GetName().c_str(), pokemonBtn[i].x + 110 - MeasureText(player.GetTeam()[i].GetName().c_str(), 20)/2, pokemonBtn[i].y + 15, 20, BLACK);
				DrawText(TextFormat("%i/4", player.GetTeam()[i].GetAbilities().size()), pokemonBtn[i].x - 5 - MeasureText(TextFormat("%i/4", player.GetTeam()[i].GetAbilities().size()), 20), pokemonBtn[i].y + 15, 20, abilityCountColor);
			}
		}
		if (showValidationBtn) {
			
			DrawText(TextFormat("Spend %i gold?", abilitiesAvailable[buttonAbilityIndexRef].GetPrice()), 540 - MeasureText(TextFormat("Spend %i gold?", abilitiesAvailable[buttonAbilityIndexRef].GetPrice()), 30) / 2, 490, 30, BLACK);
			DrawRectangleLines(acceptBtn.x, acceptBtn.y, acceptBtn.width, acceptBtn.height, GREEN);
			DrawText("Y", acceptBtn.x + (acceptBtn.width - MeasureText("Y", 40)) / 2, acceptBtn.y + 10, 40, GREEN);
			DrawRectangleLines(refuseBtn.x, refuseBtn.y, refuseBtn.width, refuseBtn.height, RED);
			DrawText("N", refuseBtn.x + (refuseBtn.width - MeasureText("N", 40)) / 2, refuseBtn.y + 10, 40, RED);
		}
		if(error && showAbilities) {
			DrawText("You can't do that", 540 - MeasureText("You can't do that", 30) / 2, 490, 30, RED);
		}
		if(showHealBtn){
			int pokeNumber = player.GetTeam().size();
			Color lifeBarColor;
			for (int i = 0; i < pokeNumber; i++) {
				if (player.GetTeam()[i].GetHealth() < (player.GetTeam()[i].GetMaxHealth() * 0.75) && player.GetTeam()[i].GetHealth() >= (player.GetTeam()[i].GetMaxHealth() * 0.4)) {
					lifeBarColor = ORANGE;
				}
				else if (player.GetTeam()[i].GetHealth() < (player.GetTeam()[i].GetMaxHealth() * 0.4)) {
					lifeBarColor = RED;
				}
				else {
					lifeBarColor = GREEN;
				}
				DrawTextureEx(player.GetTeam()[i].GetFrontSprite(), Vector2{ 750, static_cast<float> (120 + i * 70) }, 0, 1.3, WHITE);
				DrawText(player.GetTeam()[i].GetName().c_str(), 750 - 120, 145 + i * 70, 25,BLACK);
				DrawRectangle(750 - 120, 175 + i * 70, 120, 5, GRAY);
				DrawRectangle(750 - 120, 175 + i * 70, (player.GetTeam()[i].GetHealth() / player.GetTeam()[i].GetMaxHealth()) * 120, 5, lifeBarColor);
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
		chooseAbilityBtnColor = BLANK;
		showAbilities = false;
		hasClickedOnPokemon = false;
		pokemonBtnColor[buttonPokemonIndexRef] = BLANK;
		showValidationBtn = false;
		showHealBtn = true;
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
		abilityBtnColor[i] = BLANK;
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
		pokemonBtnColor[buttonPokemonIndexRef] = BLANK;
	}
	else {
		error = true;
		hasClickedOnPokemon = false;
		pokemonBtnColor[buttonPokemonIndexRef] = BLANK;
	}
	showValidationBtn = false;
}
void Pokestop::OnButtonClickRefuse(Trainers& player)
{
	hasClickedOnPokemon = false;
	pokemonBtnColor[buttonPokemonIndexRef] = BLANK;
	showValidationBtn = false;
	error = false;
}
