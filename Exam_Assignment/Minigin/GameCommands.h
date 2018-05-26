#pragma once
#include "InputManager.h"

class GameObject;

class UpCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};

class DownCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};

class LeftCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};

class RightCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};

class NextCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};
class PreviousCommand : public Command
{
public:
	void execute(std::weak_ptr<GameObject>& gameObj);
};