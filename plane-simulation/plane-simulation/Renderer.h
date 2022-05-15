#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

//pentru a desena avem nevoie de :
//  VertexArray
//	IndexBuffer
//	Shader

class Renderer
{
private:
public:
	void TestCod() const;
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawWithoutIb(const VertexBuffer& vb, const VertexArray& va, const Shader& shader, const unsigned int& startIndex, const unsigned int& sizePerVertex);
};




