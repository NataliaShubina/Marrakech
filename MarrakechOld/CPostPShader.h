#pragma once
#include "CBaseShader.h"

class CPass;

class CPostPShader: public CBaseShader
{
public:
	void Draw(CPass * pass);
	void DrawBox(int index, unsigned short sourceId);
	GLuint GetPositionAttrib() { return m_positionAttribute; }
	void LocateParams();

private:

	GLint m_blurStep;
	GLint m_bloomLimit;
	GLint m_near;
	GLint m_far;
	GLint m_fade;
	GLint m_clarity;
	GLint m_afterDOF;
	GLint m_height;
	GLint m_width;
};
