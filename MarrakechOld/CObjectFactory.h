#pragma once

class CObject;

class CObjectFactory
{
public: 
	CObjectFactory();
	virtual ~CObjectFactory();
	virtual int LoadObjects(const char * filepath) = 0;

	virtual CObject ** GetObjects() const { return m_pSceneObjects; }
	virtual unsigned int GetObjectNum() { return m_uObjectNum; }

protected:
	unsigned int m_uObjectNum;
	CObject ** m_pSceneObjects;
};