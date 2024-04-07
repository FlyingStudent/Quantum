#pragma once
#include"Quantum/Renderer/Buffer.h"
namespace Quantum {
	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unBind() const override;


		virtual const BufferLayout& getLayout() const override {
			return m_Layout;
		}
		virtual void setLayout(const BufferLayout& layout) override {
			m_Layout = layout;
		}

		static VertexBuffer* create(float* vertices, uint32_t size);	 
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indecies, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unBind() const override;

		static VertexBuffer* create(uint32_t* indecies,uint32_t count);
		virtual uint32_t getCount() const {
			return m_Count;
		};
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};
}
