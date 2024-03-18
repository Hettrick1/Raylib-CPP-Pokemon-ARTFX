#pragma once
class Event
{
private:

public:
	Event();
	~Event();
	void Start();
	void Update();
	void Draw();
	void Unload();
	int ChooseInt(int min, int max);
	void Pokestop();
	void HighGrass();
	void LakeShores();
};

