#include "MiniginPCH.h"
#include "LevelLoader.h"
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "Wall.h"
#include "PickUp.h"


LevelLoader::LevelLoader(std::string filename)
{
	std::ifstream myFile;
	myFile.open("../Data/" + filename);
	if (myFile.is_open())
	{
		std::cout << "OPEN" << std::endl;
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
	}
}


LevelLoader::~LevelLoader()
{
}
