#pragma once
#include "../Utilities/utilities.h"


class CFbo
{
public:
	CFbo();
	~CFbo();

	int Init();

	const GLuint GetColorTextureHandler() const { return m_colorTexture; }
	const GLuint GetDepthTextureHandler() const { return m_depthTexture; }

	void BindFBO();
	void UnbindFBO();

private:

	GLuint m_fboId;
	GLuint m_colorTexture;
	GLuint m_depthTexture;
};