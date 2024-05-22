#include "CRenderer.h"
#include "DefOpenGL.h"

void CRenderer::Draw(CVertexArray* VertexArray, CIndexBuffer* IndexBuffer, CShader* Shader) const
{
    VertexArray->Bind();
    IndexBuffer->Bind();
    Shader->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}
