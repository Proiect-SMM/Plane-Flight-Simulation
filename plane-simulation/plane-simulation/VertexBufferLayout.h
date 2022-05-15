#pragma once
#include <vector>
#include <glew.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	VertexBufferElement(unsigned int type, unsigned int count, bool norm) : type(type), count(count), normalized(norm) {}
	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() : m_stride(0) {}

	template<typename T>
	void Push(unsigned int count) {
		//static_assert(false); //previne sa faca build in cazul in care e false
	}

	template<>
	void Push<float>(unsigned int count) {
		VertexBufferElement vbe(GL_FLOAT, count, false);
		m_elements.push_back(vbe);
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT); //float = 4b
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		VertexBufferElement vbe(GL_UNSIGNED_INT, count, GL_FALSE);
		m_elements.push_back(vbe);
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count) {
		VertexBufferElement vbe(GL_UNSIGNED_BYTE, count, GL_TRUE);
		m_elements.push_back(vbe);
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const {
		return m_elements;
	}
	inline unsigned int GetStride() const {
		return m_stride;
	}
};

