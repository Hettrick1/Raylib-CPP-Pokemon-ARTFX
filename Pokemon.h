#pragma once

#include "raylib.h"
#include "Poketype.h"
#include "Abilities.h"

#include <vector>
#include <iostream>
#include <string>

class Pokemon
{
private:
	std::string mName;
	PokeType mType;
	int mLevel;
	std::string mDescription;
	float mMaxHealth;
	float mHealth;
	std::vector<Abilities> mAbilities;
	bool mIncapacited;
	Texture2D mFrontSpriteTexture;
	Texture2D mBackSpriteTexture;
public:
	Pokemon();
	Pokemon(std::string name, PokeType type, int level, std::string description, float health, Texture2D frontSpriteTexture, Texture2D backSpriteTexture, Abilities ability);
	~Pokemon();
	std::string GetName();
	PokeType GetType();
	int GetLevel();
	std::string GetDescription();
	float GetHealth();
	float GetMaxHealth();
	bool GetIncapacited();
	Texture2D GetFrontSprite();
	Texture2D GetBackSprite();
	float CalculateDamage(Abilities& ability, Pokemon& defender);
	void TakeDamages(float damage);
	void LearnAbilities(Abilities& ability);
	void GoOutOfPokeball();
	void GoInAPokeball();
	void Rest(float addHealth);
	std::vector<Abilities>& GetAbilities();
	void ChoseAbilities(std::vector<Abilities>& abilities, Pokemon& defender);
};

