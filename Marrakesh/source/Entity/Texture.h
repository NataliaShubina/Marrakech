#pragma once

typedef int GLint;
typedef unsigned int GLuint;

class Texture
{
public:
	~Texture();

	bool			Init(const char * file, GLint tiling);
	bool			InitCubeTexture(const char * file, GLint tiling);

	const GLuint	GetHandler() const { return m_textureHandler; }

	static enum TilingMode
	{
		REPEAT,
		CLAMP_TO_EDGE
	};

private:
	GLuint m_textureHandler;
};