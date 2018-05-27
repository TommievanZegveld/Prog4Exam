#pragma once
#include "Scene.h"
#include "GameTypes.h"

class InputManager;
class Font;
class SelectionScene final : public Scene
{
public:
	SelectionScene();
	~SelectionScene();

	void Update(float deltaTime) override;

	void Initialize() override;

private:
	std::vector<std::string> mOptions{ "NONE","GHOST","PACMAN" };
	std::vector<std::string> mControllerOptions{ "Keyboard","Controller" };

	static const int MAX_PLAYERS = 4;
	std::pair<std::shared_ptr<GameObject>, Settings> mPlayerAndSettings[MAX_PLAYERS];
	std::shared_ptr<GameObject> mCurrentlyActiveObject = mPlayerAndSettings[0].first;
	const int mOptionChoices = 3;
	const int mControllerChoices = 2;
	int mCurrentChoice = 0;
	InputManager& mInputManager;

	std::string PlayerToString(Player p);
	std::string ControllerToString(Controller c);

	std::shared_ptr<Font> mBigFont, mSmallFont;


};

