#include "stdafx.h"
#include "CEffect.h"
#include "CPass.h"
#include "Globals.h"


CEffect::CEffect() :
	m_uNumOfPasses(0),
	m_pPasses(nullptr)
{

}

CEffect::~CEffect()
{
	if (m_pPasses)
	{
		for (size_t i = 0; i < m_uNumOfPasses; i++)
		{
			SAFEDEL(m_pPasses[i]);
		}
		SAFEDELARR(m_pPasses);
	}
}

void CEffect::Draw()
{
	for (size_t i = 0; i < m_uNumOfPasses; i++)
	{
		m_pPasses[i]->Draw();
	}
}

int CEffect::SetPasses(unsigned short numPasses, const CPass **& passes)
{
	m_uNumOfPasses = numPasses;
	m_pPasses = (CPass**)passes;
	return 0;
}