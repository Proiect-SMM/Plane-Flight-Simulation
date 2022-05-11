#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_rendererId;
public:
	VertexArray();
	void AttachBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	~VertexArray();
	void Bind() const;
	void UnBind() const;
};

