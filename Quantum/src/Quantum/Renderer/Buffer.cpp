#include"qtpch.h"
#include"Buffer.h"
#include"Renderer.h"
#include"Quantum/Platform/OpenGL/OpenGLBuffer.h"
namespace Quantum {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None: QT_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL :
			return new OpenGLVertexBuffer(vertices, size);
		}
		QT_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::create(uint32_t* indecies, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None: QT_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indecies, size);
		}
		QT_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}