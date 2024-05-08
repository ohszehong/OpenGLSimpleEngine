#pragma once

#include "DebugUtilities.h"

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer
{
private:

public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, Material& material, int TextureSlot = 0) const;

	void Draw(const IndexBuffer& ib, const int offset = 0) const;

	void DrawWithCount(const IndexBuffer& ib, unsigned int count, const int offset = 0) const;

	void Clear() const;
};