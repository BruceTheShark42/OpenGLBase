#pragma once

#include "glm/glm.hpp"

namespace gbc
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform (const std::string& name, float              value) = 0;
		virtual void SetUniform (const std::string& name, const glm::vec2&   value) = 0;
		virtual void SetUniform (const std::string& name, const glm::vec3&   value) = 0;
		virtual void SetUniform (const std::string& name, const glm::vec4&   value) = 0;
		virtual void SetUniform (const std::string& name, int                value) = 0;
		virtual void SetUniform (const std::string& name, const glm::ivec2&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::ivec3&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::ivec4&  value) = 0;
		virtual void SetUniform (const std::string& name, unsigned int       value) = 0;
		virtual void SetUniform (const std::string& name, const glm::uvec2&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::uvec3&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::uvec4&  value) = 0;
		virtual void SetUniform (const std::string& name, bool               value) = 0;
		virtual void SetUniform (const std::string& name, const glm::bvec2&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::bvec3&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::bvec4&  value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat2&   value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat2x3& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat2x4& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat3x2& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat3&   value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat3x4& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat4x2& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat4x3& value) = 0;
		virtual void SetUniform (const std::string& name, const glm::mat4&   value) = 0;
		virtual void SetUniforms(const std::string& name, const int*          values, int count) = 0;
		virtual void SetUniforms(const std::string& name, const unsigned int* values, int count) = 0;

		static Ref<Shader> CreateRef(const std::string& filepath);
		static Scope<Shader> CreateScope(const std::string& filepath);
	};
}
