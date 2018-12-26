#pragma once

#include "CObjectFactory.h"

class CEnvironmentFactory : public CObjectFactory
{
public:
	int LoadObjects(const char * filepath);
};