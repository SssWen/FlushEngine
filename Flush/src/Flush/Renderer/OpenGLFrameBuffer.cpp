#include "flushpch.h"
#include "OpenGLFramebuffer.h"

#include "Flush/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Flush {


	OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height, FramebufferFormat format)
		: m_Width(width), m_Height(height), m_Format(format)
	{
		Resize(width, height);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{		
		glDeleteFramebuffers(1, &this->m_RendererID);		
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (m_Width == width && m_Height == height)
			return;

		m_Width = width;
		m_Height = height;
		
		if (this->m_RendererID)
		{
			glDeleteFramebuffers(1, &this->m_RendererID);
			glDeleteTextures(1, &this->m_ColorAttachment);
			glDeleteTextures(1, &this->m_DepthAttachment);
		}

		glGenFramebuffers(1, &this->m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_RendererID);

		glGenTextures(1, &this->m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, this->m_ColorAttachment);

		// TODO: Create Flush texture object based on format here
		if (this->m_Format == FramebufferFormat::RGBA16F)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->m_Width, this->m_Height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		else if (this->m_Format == FramebufferFormat::RGBA8)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_ColorAttachment, 0);

		glGenTextures(1, &this->m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, this->m_DepthAttachment);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->m_Width, this->m_Height, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_DepthAttachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			FLUSH_CORE_ERROR("Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
	}

	void OpenGLFramebuffer::Bind() const
	{
		
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_RendererID);
		glViewport(0, 0, this->m_Width, this->m_Height);
		
	}

	void OpenGLFramebuffer::Unbind() const
	{		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);		
	}

	void OpenGLFramebuffer::BindTexture(uint32_t slot) const
	{		
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->m_ColorAttachment);
		
	}
}