#pragma once

enum class Player
{
	NONE,
	GHOST,
	PACMAN
};
enum class Controller
{
	KEYBOARD,
	CONTROLLER
};
struct Settings
{
	Player player;
	Controller controller;
};