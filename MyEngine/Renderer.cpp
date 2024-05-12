#include "PreCompile.h"
#include "Renderer.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"


Renderer::Renderer()
{
    VertexBuffer = EngineVertexBuffer::Find("Rectangle");
    IndexBuffer = EngineIndexBuffer::Find("Rectangle");
    InputLayout = EngineInputLayout::Find("EngineVertex");
    
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{

}
