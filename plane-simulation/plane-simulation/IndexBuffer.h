#pragma once
class IndexBuffer
{
private:
	unsigned int m_rendererId;
	unsigned int m_count; //sa stim cati indici are
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	unsigned int GetCount() const;
	void Bind() const;
	void UnBind() const;
};

