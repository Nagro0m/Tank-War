#pragma once
#include "Logger.h"
#include "CustomException.h"
#include "Utilities.h"
#include "Utilities.h"

#define M_ACTOR ActorManager::GetInstance()
#define M_TIMER(_type) TimerManager<_type>::GetInstance()
#define M_SOUND SoundManager::GetInstance()
#define M_GAME Game::GetInstance()
#define M_(_manager) _manager::GetInstance()
