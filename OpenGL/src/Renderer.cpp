#include "Renderer.h"

#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Material& material, int TextureSlot) const
{
    va.Bind();
    ib.Bind();

    material.Bind();
    material.ApplyMaterial();

    //material.shader->SetUniform1i("u_Texture", TextureSlot);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const IndexBuffer& ib, const int offset) const
{
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, (void*)offset));
}

void Renderer::DrawWithCount(const IndexBuffer& ib, unsigned int count, const int offset) const
{
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)offset));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
