#include <string>

#include <GL/glew.h>

namespace Tools
{
	void VSync(bool enabled);
	int PrepareTexture(std::string path, GLenum wrapMode = GL_CLAMP_TO_EDGE,
		GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum magFilter = GL_LINEAR_MIPMAP_LINEAR);
}
