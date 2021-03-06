#pragma once

#include "GBC/Rendering/Framebuffer.h"

namespace gbc
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(FramebufferSpecification specification);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void BindColorTexture(unsigned int index = 0, unsigned int slot = 0) override;
		virtual void UnbindColorTexture(unsigned int slot = 0) override;

		virtual void OnViewportResize(int width, int height) override;
		virtual const FramebufferSpecification& GetSpecification() const override { return specification; }

		virtual RendererID GetColorAttachment(unsigned int index = 0) const override { return index < colorAttachments.size() ? colorAttachments[index] : 0; }
		virtual RendererID GetDepthAttachment() const override { return depthAttachment; }

		virtual bool GetColorPixel(void* pixel, int x, int y, unsigned int index = 0) const override;

		virtual void ClearColorAttachment(const void* value, unsigned int index = 0) override;
	private:
		void Recreate();
		void Clear();

		FramebufferSpecification specification;
		RendererID rendererID = 0;

		std::vector<FramebufferTextureSpecification> colorAttachmentSpecifications;
		FramebufferTextureSpecification depthAttachmentSpecification;

		std::vector<RendererID> colorAttachments;
		RendererID depthAttachment = 0;
	};
}
