#pragma once
#include "Singleton.h"
#include "GameTypes.h"
#include <vector>

class GameSettings final : public Singleton<GameSettings>
{
public:
	GameSettings(){};
	~GameSettings(){};

	void SaveSettings(Settings p1, Settings p2, Settings p3, Settings p4) { mSettings.resize(4); mSettings[0] = p1; mSettings[1] = p2; mSettings[2] = p3; mSettings[3] = p4; }
	std::vector<Settings> LoadSettings() { return mSettings; }

private:
	std::vector<Settings> mSettings;
};

