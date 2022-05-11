#include "VertexBuffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_rendererId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
