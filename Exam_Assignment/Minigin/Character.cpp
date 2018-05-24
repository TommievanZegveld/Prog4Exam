#include "MiniginPCH.h"
#include "Character.h"


Character::Character() : mCurrentDir(Direction::RIGHT)
{
}


Character::~Character()
{
}

void Character::SetDirection(Direction dir)
{
	mCurrentDir = dir;
}

void Character::SetNextDirection(Direction dir)
{
	mNextDir = dir;
}

