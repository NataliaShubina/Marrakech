#include "Widget.h"
#include "Texture.h"
#include "Mesh.h"
#include "../Marrakesh/source/Shaders/Shader.h"
#include "../Managers/ShaderLoader.h"
#include "../Managers/TextureLoader.h"

Widget::Widget() :
	m_leftTop(0.f, 0.f),
	m_rightBottom(0.f, 0.f),
	m_center(0.f, 0.f),
	m_offsetLeft(0.f),
	m_offsetTop(0.f),
	m_width(0.f),
	m_height(0.f),
	m_texture(nullptr),
	m_isVisible(true),
	m_layer(0)
{

}

Widget::~Widget()
{

}

int Widget::Init(float offsetLeft, float offsetTop, float width, float height, short layer)
{
	m_offsetLeft = offsetLeft;
	m_offsetTop = offsetTop;
	m_width = width;
	m_height = height;

	m_leftTop.x = (float)WINDOW_WIDTH * m_offsetLeft;
	m_leftTop.y = (float)WINDOW_HEIGHT * m_offsetTop;

	m_rightBottom.x = m_leftTop.x + m_width;
	m_rightBottom.y = m_leftTop.y - m_height;

	m_center.x = m_leftTop.x + m_width / 2.f;
	m_center.y = m_leftTop.y - m_height / 2.f;

	m_layer = layer;

	return 0;
}

void Widget::Render()
{
	if (m_isVisible)
	{
		m_shader->Use();
		m_shader->BindBuffers(m_rect->GetVerttexBuffer(), m_rect->GetIndexBuffer());

		int textureUnit = 0;

		GLuint * texture2dHadlers = new GLuint[1];

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetHandler());
		texture2dHadlers[0] = textureUnit;
		m_shader->SetTextures("u_textures2d", 1, texture2dHadlers);

		delete[] texture2dHadlers;

		m_shader->SetVertexAttributes();
		m_rect->Draw();
	}
}

void Widget::GenerateRect()
{
	PArray<Vertex> vertices;
	PArray<unsigned short> indices;

	Vertex vt1 = Vertex(
		math::vec3(m_leftTop.x, m_leftTop.y, 0.f),
		math::vec3(0.0f, 0.0f, 0.0f),
		math::vec2(0.0f, 1.0f));

	Vertex vt2 = Vertex(
		math::vec3(m_leftTop.x + m_width, m_leftTop.y, 0.f),
		math::vec3(0.0f, 0.0f, 0.0f),
		math::vec2(1.0f, 1.0f));

	Vertex vt3 = Vertex(
		math::vec3(m_rightBottom.x, m_rightBottom.y, 0.f),
		math::vec3(0.0f, 0.0f, 0.0f),
		math::vec2(1.0f, 0.0f));

	Vertex vt4 = Vertex(
		math::vec3(m_leftTop.x, m_leftTop.y - m_height, 0.f),
		math::vec3(0.0f, 0.0f, 0.0f),
		math::vec2(0.0f, 0.0f));

	vertices.push_back(vt1);
	vertices.push_back(vt2);
	vertices.push_back(vt3);
	vertices.push_back(vt4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	m_rect->SetVertexArray(vertices);
	m_rect->SetIndexArray(indices);

	m_rect->BindBuffers();
}

void Widget::SetTexture(unsigned int textureId)
{
	m_texture = TextureLoader::GetInstance()->GetTextureById(textureId);
}

void Widget::SetShader(unsigned int shaderId)
{
	m_shader = ShaderLoader::GetInstance()->GetShaderById(shaderId);
}

void Widget::OnKeyPressed()
{
	//...
}

void Widget::OnKeyReleased()
{
	//...
}
void Widget::SetVisible(bool value)
{
	m_isVisible = value;
}

bool Widget::IsPointerOnWidget(const math::vec2& pointer) const
{
	if (m_isVisible)
	{
		if ((m_leftTop.x <= pointer.x && pointer.x <= m_rightBottom.x) &&
			(m_leftTop.y >= pointer.y && pointer.y <= m_rightBottom.y))
			return true;
	}
	return false;
}
