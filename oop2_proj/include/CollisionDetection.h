#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "GameObjBase.h"

// search and activate the suitable function for the current collison.
void processCollision(GameObjBase&, GameObjBase&);