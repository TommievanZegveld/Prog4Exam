#pragma once
#include <functional>
#include <vector>

enum class Events
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};
class Command;


class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onNotify(Events event) = 0;
};
