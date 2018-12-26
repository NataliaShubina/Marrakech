#pragma once
#include "../Utilities/utilities.h"

class CPass
{
public:
	CPass();
	~CPass();

	//void Init();
	void Draw();
	void Load(unsigned short shaderId,	unsigned short textureNum, const char **& id,
		unsigned short dataNum, const float *& data, unsigned short fboId);

	GLuint GetTargetID() const { return m_uFboId; }

	const GLuint * GetTextureIDs() const { return m_pTextureIds; }
	const float * GetData() const { return m_pData; }

	inline unsigned short GetShaderID() const { return m_uShaderId; }
	inline unsigned short GetTextureCount() const { return m_uTextureIdsNum; }
	inline unsigned short GetDataVarNum() const { return m_uDataVarNum; }

private:

	unsigned short m_uShaderId;
	unsigned short m_uTextureIdsNum;
	unsigned short m_uDataVarNum;

	GLuint * m_pTextureIds;
	GLuint m_uFboId;
	float * m_pData;
};