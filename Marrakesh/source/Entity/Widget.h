#pragma once
#include "../Marrakesh/Util/Math.h"
#include "../Marrakesh/Util/include/Defines.h"

class Texture;
class Mesh;
class Shader;

class Widget
{
public:
	Widget();
	virtual ~Widget();

	int Init(float offsetLeft, float offsetTop, float width, float height, short layer);
	void Render();

	void SetTexture(unsigned int textureId);
	void SetShader(unsigned int shaderId);

	virtual void OnKeyPressed();
	virtual void OnKeyReleased();

	math::vec2 GetTopLeft() const { return m_leftTop; }
	math::vec2 GetRightBottom() const { return m_rightBottom; }
	math::vec2 GetCenter() const { return m_center; }

	float GetOffsetLeft() const { return m_offsetLeft; };
	float GetOffsetTop() const { return m_offsetTop; };
	float GetWidth() const { return m_width; };
	float GetHeight() const { return m_height; };

	bool IsVisible() const { return m_isVisible; }
	void SetVisible(bool value);
	short GetLayer() const { return m_layer; }

	bool IsPointerOnWidget(const math::vec2& pointer) const;

private:

	void GenerateRect();

	math::vec2	m_leftTop;
	math::vec2	m_rightBottom;

	math::vec2	m_center;

	float		m_offsetLeft;
	float		m_offsetTop;

	float		m_width;
	float		m_height;
	
	SharedPtr<Mesh>		m_rect;
	SharedPtr<Texture>	m_texture;
	SharedPtr<Shader>	m_shader;

	bool		m_isVisible;
	short		m_layer;
};