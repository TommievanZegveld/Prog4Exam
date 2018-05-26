#pragma once

class Wall;
class PickUp;
class SpecialPickUp;
class Teleporter;

class LevelLoader
{
public:
	LevelLoader(std::string filename);
	~LevelLoader();

	std::vector<std::shared_ptr<Wall>>& GetWalls() { return mWalls; }
	std::vector<std::shared_ptr<PickUp>>& GetPickUps() { return mPickUps; }
	std::vector<std::shared_ptr<SpecialPickUp>>& GetSpecials() { return mSpecials; }
	std::vector<std::shared_ptr<Teleporter>>& GetPortals() { return mPortals; }

private:
	std::vector<std::shared_ptr<Wall>> mWalls;
	std::vector<std::shared_ptr<PickUp>> mPickUps;
	std::vector<std::shared_ptr<SpecialPickUp>> mSpecials;
	std::vector<std::shared_ptr<Teleporter>> mPortals;
};

