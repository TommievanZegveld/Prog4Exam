#pragma once
#include <ostream>
#include <iostream>
#include "GameObject.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(std::weak_ptr<GameObject>& gameObj) = 0;
};

