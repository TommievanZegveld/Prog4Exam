#pragma once

class Wall;
class PickUp;
class LevelLoader
{
public:
	LevelLoader(std::string filename);
	~LevelLoader();

	std::vector<std::shared_ptr<Wall>> GetWalls() { return mWalls; }
	std::vector<std::shared_ptr<PickUp>> GetPickUps() { return mPickUps; }

private:
	std::vector<std::shared_ptr<Wall>> mWalls;
	std::vector<std::shared_ptr<PickUp>> mPickUps;
};

