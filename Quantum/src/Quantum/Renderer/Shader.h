#pragma once
#include<string>
namespace Quantum {
	class Shader {
	public:
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();
		void bind() const;
		void unBind() const ;

	private:
	std::uint32_t m_RendererID;
	};
}
