#include "GameController.h"

GameController& GameController::getIns()
{
	static GameController ins;
	return ins;
}

GameController* GameController::getInstance()
{
	return &getIns();
}