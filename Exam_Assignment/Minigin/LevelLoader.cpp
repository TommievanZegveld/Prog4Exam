#include "MiniginPCH.h"
#include "LevelLoader.h"
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "Wall.h"
#include "PickUp.h"
#include "SpecialPickUp.h"
#include "Teleporter.h"
#include "Character.h"

LevelLoader::LevelLoader(std::string filename)
{
	std::ifstream myFile;
	myFile.open("../Data/" + filename);
	if (!myFile.is_open())
	{
		std::cout << "Could not open " << filename << std::endl;
	}
	aria::csv::CsvParser parser(myFile);
	for (auto& row : parser)
	{
		if(row[0] == "wall")
		{
			auto wall = std::make_shared<Wall>(glm::vec2(std::stoi(row[1]), std::stoi(row[2])), std::stoi(row[3]), std::stoi(row[4]));
			mWalls.push_back(wall);
		}
		if (row[0] == "pickup")
		{
			auto pickup = std::make_shared<PickUp>(glm::vec2(std::stoi(row[1]), std::stoi(row[2])));
			mPickUps.push_back(pickup);
		}
		if(row[0] == "special")
		{
			auto pickup = std::make_shared<SpecialPickUp>(glm::vec2(std::stoi(row[1]), std::stoi(row[2])));
			mSpecials.push_back(pickup);
		}
		if(row[0] == "portal")
		{
			Direction dir1, dir2;
			if (row[3] == "left")
				dir1 = Direction::LEFT;
			else if(row[3] == "right")
				dir1 = Direction::RIGHT;

			if (row[6] == "left")
				dir2 = Direction::LEFT;
			else if (row[6] == "right")
				dir2 = Direction::RIGHT;
			auto portal = std::make_shared<Teleporter>(
				glm::vec2(std::stoi(row[1]), std::stoi(row[2])),
				dir1,
				glm::vec2(std::stoi(row[4]), std::stoi(row[5])),
				dir2);
			mPortals.push_back(portal);
		}
	}
}


LevelLoader::~LevelLoader()
{
}
