#include "Texture.h"
#include "../Utilities/utilities.h"

bool Texture::Init(const char * file, GLint tiling)
{
	glGenTextures(1, &m_textureHandler);
	glBindTexture(GL_TEXTURE_2D, m_textureHandler);

	int width, height, bpp;
	char * bufferTGA = LoadTGA(file, &width, &height, &bpp);

	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}

	delete[] bufferTGA;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (tiling == REPEAT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (tiling == CLAMP_TO_EDGE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	return true;
}

bool Texture::InitCubeTexture(const char * file, GLint tiling)
{
	glGenTextures(1, &m_textureHandler);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureHandler);

	int width, height, bpp;
	char * bufferTGA = LoadTGA(file, &width, &height, &bpp);

	int bufferRowWidth = width * bpp / 8;
	int fragWidth = bufferRowWidth / 4;
	int texelFragWidth = width / 4;
	int fragHeight = height / 3;

	char * faceBuffers[6];
	for (int i = 0; i < 6; i++)
	{
		faceBuffers[i] = new char[fragWidth * fragHeight];
	}

	for (int i = 0; i < fragHeight; i++)
	{
		memcpy_s(&faceBuffers[0][i * fragWidth], fragWidth, (bufferTGA + i * bufferRowWidth + fragWidth), fragWidth * sizeof(char));
		memcpy_s(&faceBuffers[1][i * fragWidth], fragWidth, (bufferTGA + (i + fragHeight) * bufferRowWidth), fragWidth * sizeof(char));
		memcpy_s(&faceBuffers[2][i * fragWidth], fragWidth, (bufferTGA + (i + fragHeight) * bufferRowWidth + fragWidth), fragWidth * sizeof(char));
		memcpy_s(&faceBuffers[3][i * fragWidth], fragWidth, (bufferTGA + (i + fragHeight) * bufferRowWidth + fragWidth * 2), fragWidth * sizeof(char));
		memcpy_s(&faceBuffers[4][i * fragWidth], fragWidth, (bufferTGA + (i + fragHeight) * bufferRowWidth + fragWidth * 3), fragWidth * sizeof(char));
		memcpy_s(&faceBuffers[5][i * fragWidth], fragWidth, (bufferTGA + (i + fragHeight * 2) * bufferRowWidth + fragWidth), fragWidth * sizeof(char));
	}

	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[5]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[1]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[2]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[3]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[4]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, texelFragWidth, fragHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffers[0]);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[5]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[1]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[2]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[3]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[4]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, texelFragWidth, fragHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceBuffers[0]);
	}

	delete[] bufferTGA;
	for (int i = 0; i < 6; i++)
	{
		delete[] faceBuffers[i];
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	if (tiling == REPEAT)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (tiling == CLAMP_TO_EDGE)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	return true;

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureHandler);
}