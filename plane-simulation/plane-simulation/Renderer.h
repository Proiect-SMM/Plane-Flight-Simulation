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
	Renderer() = default;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};




