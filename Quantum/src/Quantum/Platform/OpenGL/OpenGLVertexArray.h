#pragma once
#include"Quantum/Renderer/VertexArray.h"
namespace Quantum {
	class OpenGLVertexArray :public VertexArray
	{
	public :
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unBind() const override;
	
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const  override {
			return m_VertexBuffers;
		}
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override
		{
			return m_IndexBuffers;
		}
	private:
		unsigned int m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffers;

	};
}