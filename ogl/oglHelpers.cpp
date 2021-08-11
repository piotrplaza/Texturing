#include "oglHelpers.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <stdexcept>
#include <cassert>

#include <GL/glew.h>
#include <Windows.h>

#include <3rdParty/stb_image/stb_image.h>

namespace
{
	int texturesCouner = 0;
}

namespace Tools
{
	void VSync(bool enabled)
	{
		typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char* extensions = (char*)glGetString(GL_EXTENSIONS);

		if (strstr(extensions, "WGL_EXT_swap_control") == 0)
		{
			return;
		}
		else
		{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

			if (wglSwapIntervalEXT)
			{
				wglSwapIntervalEXT(enabled);
			}
		}
	}

	int PrepareTexture(std::string path, GLenum wrapMode, GLenum minFilter, GLenum magFilter)
	{
		assert(texturesCouner < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

		stbi_set_flip_vertically_on_load(true);

		glActiveTexture(GL_TEXTURE0 + texturesCouner);

		unsigned textureObject;
		glGenTextures(1, &textureObject);
		glBindTexture(GL_TEXTURE_2D, textureObject);

		std::unique_ptr<unsigned char[]> textureData;
		glm::ivec2 textureSize{};
		int bitDepth;

		textureData.reset(stbi_load(path.c_str(), &textureSize.x, &textureSize.y, &bitDepth, 0));
		if (!textureData)
		{
			assert(!"Unable to load image.");
			throw std::runtime_error("Unable to load image \"" + path + "\".");
		}

		const GLint format = bitDepth == 4 ? GL_RGBA : bitDepth == 3 ? GL_RGB : bitDepth == 2 ? GL_RG : GL_RED;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, format, textureSize.x, textureSize.y, 0, format, GL_UNSIGNED_BYTE, textureData.get());

		if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
			minFilter == GL_LINEAR_MIPMAP_NEAREST ||
			minFilter == GL_NEAREST_MIPMAP_LINEAR ||
			minFilter == GL_NEAREST_MIPMAP_NEAREST)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		return texturesCouner++;
	}
}
