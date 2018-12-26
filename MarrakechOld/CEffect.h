#pragma once

class CPass;

class CEffect
{
public:
	CEffect();
	~CEffect();

	void Draw();

	int SetPasses(unsigned short numPasses, const CPass **& passes);

private:

	unsigned short m_uNumOfPasses;
	CPass ** m_pPasses;
};