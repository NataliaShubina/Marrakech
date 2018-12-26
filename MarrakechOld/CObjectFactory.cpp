#include "stdafx.h"
#include "CObjectFactory.h"
#include "CObject.h"
#include "Globals.h"


CObjectFactory::CObjectFactory() :
	m_uObjectNum(0),
	m_pSceneObjects(nullptr)
{

}
CObjectFactory::~CObjectFactory() 
{ 
	SAFEDELARRSIZE(m_pSceneObjects, m_uObjectNum);
}