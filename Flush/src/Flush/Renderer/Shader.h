#pragma once

#include <string>

namespace Flush 
{
	class Shader
	{
	public:
		
		virtual ~Shader() = default;

		virtual void Bind() const = 0; // pure functions
		virtual void UnBind() const = 0;	
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}


