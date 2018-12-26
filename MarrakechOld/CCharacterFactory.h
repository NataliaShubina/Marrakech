#pragma once

#include "CObjectFactory.h"

class CCharacterFactory : public CObjectFactory
{
public:
	int LoadObjects(const char * filepath);
};